/*
  Copyright (c) 2015-2020 Laurent Montel <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

*/

#include "kdebugsettingsdialog.h"
#include "customdebugsettingspage.h"
#include "kdeapplicationdebugsettingpage.h"
#include "environmentsettingsrulespage.h"
#include "kdebugsettingsutil.h"
#include "categorywarning.h"
#include "loadcategoriesjob.h"
#include "saverulesjob.h"

#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>
#include <KMessageBox>

#include <QFileDialog>
#include <QDialogButtonBox>
#include <QLibraryInfo>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include "kdebugsettings_debug.h"
namespace {
constexpr char KDebugSettingsDialogGroupName[] = "KDebugSettingsDialog";
}
KDebugSettingsDialog::KDebugSettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    auto *mainLayout = new QVBoxLayout(this);

    mCategoryWarning = new CategoryWarning(this);
    mCategoryWarning->setObjectName(QStringLiteral("categorywarning"));
    mainLayout->addWidget(mCategoryWarning);

    mTabWidget = new QTabWidget(this);
    mTabWidget->setObjectName(QStringLiteral("tabwidget"));
    mainLayout->addWidget(mTabWidget);

    mKdeApplicationSettingsPage = new KDEApplicationDebugSettingPage(this);
    mKdeApplicationSettingsPage->setObjectName(QStringLiteral("kdeapplicationsettingspage"));
    mCustomSettingsPage = new CustomDebugSettingsPage(this);
    mCustomSettingsPage->setObjectName(QStringLiteral("customsettingspage"));
    mEnvironmentSettingsRulesPage = new EnvironmentSettingsRulesPage(this);
    mEnvironmentSettingsRulesPage->setObjectName(QStringLiteral("environmentsettingsrulespage"));
    mTabWidget->addTab(mKdeApplicationSettingsPage, i18n("KDE Application"));
    mTabWidget->addTab(mCustomSettingsPage, i18n("Custom Rules"));
    mTabWidget->addTab(mEnvironmentSettingsRulesPage, i18n("Rules Settings With Environment Variable"));
    mTabWidget->setFocusPolicy(Qt::NoFocus);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::RestoreDefaults | QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Help | QDialogButtonBox::Apply, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));

    QPushButton *saveAs = new QPushButton(i18n("Save As..."), this);
    saveAs->setObjectName(QStringLiteral("saveas_button"));
    buttonBox->addButton(saveAs, QDialogButtonBox::ActionRole);
    connect(saveAs, &QPushButton::clicked, this, &KDebugSettingsDialog::slotSaveAs);

    QPushButton *load = new QPushButton(i18n("Load..."), this);
    load->setObjectName(QStringLiteral("load_button"));
    buttonBox->addButton(load, QDialogButtonBox::ActionRole);
    connect(load, &QPushButton::clicked, this, &KDebugSettingsDialog::slotLoad);

    QPushButton *insertCategories = new QPushButton(i18n("Insert..."), this);
    insertCategories->setObjectName(QStringLiteral("insert_button"));
    buttonBox->addButton(insertCategories, QDialogButtonBox::ActionRole);
    connect(insertCategories, &QPushButton::clicked, this, &KDebugSettingsDialog::slotInsertCategories);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &KDebugSettingsDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(buttonBox, &QDialogButtonBox::helpRequested, this, &KDebugSettingsDialog::slotHelpRequested);
    connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this, &KDebugSettingsDialog::slotApply);
    connect(buttonBox->button(QDialogButtonBox::RestoreDefaults), &QPushButton::clicked, this, &KDebugSettingsDialog::slotRestoreDefault);
    mainLayout->addWidget(buttonBox);
    readConfig();
    readQtLoggingFile();
    mKdeApplicationSettingsPage->forceFocus();
}

KDebugSettingsDialog::~KDebugSettingsDialog()
{
    saveConfig();
}

void KDebugSettingsDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), QLatin1String(KDebugSettingsDialogGroupName));
    const QSize size = group.readEntry("Size", QSize(600, 400));
    if (size.isValid()) {
        resize(size);
    }
}

void KDebugSettingsDialog::saveConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), QLatin1String(KDebugSettingsDialogGroupName));
    group.writeEntry("Size", size());
    group.sync();
}

void KDebugSettingsDialog::readQtLoggingFile()
{
    mLoggings.readQtLoggingFile();
    updateLogginsCategories();
}

void KDebugSettingsDialog::updateLogginsCategories()
{
    if (!mLoggings.environmentrules().isEmpty()) {
        mEnvironmentSettingsRulesPage->setRules(mLoggings.environmentrules());
    }
    const LoggingCategory::List customCategories = mLoggings.customCategories();
    const LoggingCategory::List qtKdeCategories = mLoggings.qtKdeCategories();
    const bool foundOverrideRule = mLoggings.foundOverrideRule();

    mKdeApplicationSettingsPage->fillList(qtKdeCategories);
    mCustomSettingsPage->fillList(customCategories);
    if (foundOverrideRule) {
        mCategoryWarning->animatedShow();
    }
    mCategoriesList = mLoggings.categoriesList();
}

bool KDebugSettingsDialog::saveRules(const QString &path, bool forceSavingAllRules)
{
    SaveRulesJob job;
    job.setFileName(path);
    job.setListCustom(mCustomSettingsPage->rules());
    job.setListKde(mKdeApplicationSettingsPage->rules(forceSavingAllRules));
    if (!job.start()) {
        KMessageBox::error(this, i18n("\'%1\' cannot be opened. Please verify it.", path));
        return false;
    }
    return true;
}

bool KDebugSettingsDialog::saveInQtLogging()
{
    return saveRules(KDebugSettingsUtil::qtFileName());
}

void KDebugSettingsDialog::slotAccepted()
{
    if (saveInQtLogging()) {
        accept();
    }
}

void KDebugSettingsDialog::slotHelpRequested()
{
    QDesktopServices::openUrl(QUrl(QStringLiteral("https://doc.qt.io/qt-5/qloggingcategory.html#details")));
}

void KDebugSettingsDialog::slotApply()
{
    saveInQtLogging();
}

void KDebugSettingsDialog::slotInsertCategories()
{
    const QString path = QFileDialog::getOpenFileName(this, i18n("Insert Categories"), QString(), QStringLiteral("%1 (*.categories)").arg(i18n("Categories Files")));
    if (!path.isEmpty()) {
        const KdeLoggingCategory::List insertCategoriesList = KDebugSettingsUtil::readLoggingCategoriesForInserting(path, mCategoriesList);
        LoggingCategory::List newCategories;
        for (const KdeLoggingCategory &cat : qAsConst(insertCategoriesList)) {
            LoggingCategory loggingCat;
            loggingCat.description = cat.description;
            loggingCat.categoryName = cat.categoryName;
            loggingCat.defaultSeverityType = KDebugSettingsUtil::convertCategoryTypeFromString(cat.defaultSeverity);
            if (loggingCat.isValid()) {
                newCategories.append(loggingCat);
            }
        }
        mKdeApplicationSettingsPage->insertCategories(newCategories);
    }
}

void KDebugSettingsDialog::slotSaveAs()
{
    const QString path = QFileDialog::getSaveFileName(this, i18n("Save As"), QString(), i18n("KDebugSettings File (*.kdebugsettingsrules)"));
    if (!path.isEmpty()) {
        saveRules(path, true);
    }
}

void KDebugSettingsDialog::slotLoad()
{
    const QString path = QFileDialog::getOpenFileName(this, i18n("Load Debug Settings Files"), QString(), i18n("KDebugSettings File (*.kdebugsettingsrules)"));
    if (!path.isEmpty()) {
        mLoggings.readCategoriesFiles(path);
        updateLogginsCategories();
    }
}

void KDebugSettingsDialog::slotRestoreDefault()
{
    mKdeApplicationSettingsPage->restoreToDefault();
}
