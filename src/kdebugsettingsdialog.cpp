/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdebugsettingsdialog.h"
#include "categorywarning.h"
#include "customdebugsettingspage.h"
#include "environmentsettingsrulespage.h"
#include "groupmanagementdialog.h"
#include "kdeapplicationdebugsettingpage.h"
#include "kdebugsettings_debug.h"
#include "kdebugsettingsutil.h"
#include "loadcategoriesjob.h"
#include "loadgroupmenu.h"
#include "loadtoolbutton.h"
#include "saverulesjob.h"
#include "savetoolbutton.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KMessageBox>
#include <KSharedConfig>

#include <QDesktopServices>
#include <QDialogButtonBox>
#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QPushButton>
#include <QTabWidget>
#include <QUrl>
#include <QVBoxLayout>
namespace
{
constexpr char KDebugSettingsDialogGroupName[] = "KDebugSettingsDialog";
}
KDebugSettingsDialog::KDebugSettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    auto mainLayout = new QVBoxLayout(this);

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

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::RestoreDefaults | QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Help
                                              | QDialogButtonBox::Apply,
                                          this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));

    auto saveAs = new SaveToolButton(this);
    saveAs->setText(i18n("Save As..."));
    saveAs->setObjectName(QStringLiteral("saveas_button"));
    buttonBox->addButton(saveAs, QDialogButtonBox::ActionRole);
    connect(saveAs, &SaveToolButton::saveAsFile, this, &KDebugSettingsDialog::slotSaveAs);
    connect(saveAs, &SaveToolButton::saveAsGroup, this, &KDebugSettingsDialog::slotSaveAsGroup);

    mLoadToolButton = new LoadToolButton(this);
    mLoadToolButton->setObjectName(QStringLiteral("load_button"));
    buttonBox->addButton(mLoadToolButton, QDialogButtonBox::ActionRole);
    connect(mLoadToolButton, &LoadToolButton::loadFromFile, this, &KDebugSettingsDialog::slotLoad);
    connect(mLoadToolButton, &LoadToolButton::loadGroupRequested, this, &KDebugSettingsDialog::slotLoadGroup);
    connect(mLoadToolButton, &LoadToolButton::manageGroupRequested, this, &KDebugSettingsDialog::slotManageGroup);
    connect(this, &KDebugSettingsDialog::updateLoadGroupMenu, mLoadToolButton, &LoadToolButton::updateLoadGroupMenu);

    auto insertCategories = new QPushButton(i18n("Insert..."), this);
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
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(KDebugSettingsDialogGroupName));
    const QSize size = group.readEntry("Size", QSize(600, 400));
    if (size.isValid()) {
        resize(size);
    }
}

void KDebugSettingsDialog::saveConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(KDebugSettingsDialogGroupName));
    group.writeEntry("Size", size());
    group.sync();
}

void KDebugSettingsDialog::slotLoadGroup(const QString &fullPath)
{
    if (!fullPath.isEmpty()) {
        mLoggings.readCategoriesFiles(fullPath);
        updateLoggingCategories();
    }
}

void KDebugSettingsDialog::readQtLoggingFile()
{
    mLoggings.readQtLoggingFile();
    updateLoggingCategories();
}

void KDebugSettingsDialog::updateLoggingCategories()
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
    const QString path =
        QFileDialog::getOpenFileName(this, i18n("Insert Categories"), QString(), QStringLiteral("%1 (*.categories)").arg(i18n("Categories Files")));
    if (!path.isEmpty()) {
        const KdeLoggingCategory::List insertCategoriesList = KDebugSettingsUtil::readLoggingCategoriesForInserting(path, mCategoriesList);
        LoggingCategory::List newCategories;
        for (const KdeLoggingCategory &cat : std::as_const(insertCategoriesList)) {
            LoggingCategory loggingCat;
            loggingCat.description = cat.description;
            loggingCat.categoryName = cat.categoryName;
            loggingCat.defaultSeverityType = KDebugSettingsUtil::convertCategoryTypeFromString(cat.defaultSeverity);
            if (loggingCat.isValid()) {
                newCategories.append(loggingCat);
            }
        }
        mKdeApplicationSettingsPage->insertCategories(newCategories);
        KMessageBox::information(this, i18n("Categories from file \'%1\' inserted.", path), i18n("Insert Categories"));
    }
}

void KDebugSettingsDialog::slotSaveAsGroup()
{
    const QString groupPath = LoadGroupMenu::defaultWritableGroupPath();
    bool ok = false;
    const QString name = QInputDialog::getText(this, i18n("Group Name"), i18n("Name:"), QLineEdit::Normal, QString(), &ok);
    if (ok) {
        const QString trimmedName = name.trimmed();
        if (!trimmedName.isEmpty()) {
            if (mLoadToolButton->groupNames().contains(trimmedName)) {
                KMessageBox::error(this, i18n("\'%1\' is already used as a group name.\nPlease save as another name.", trimmedName));
            } else {
                if (!QDir().mkpath(groupPath)) {
                    qCWarning(KDEBUGSETTINGS_LOG) << "Unable to create folder: " << groupPath;
                }
                saveRules(groupPath + QLatin1Char('/') + trimmedName, true);
                Q_EMIT updateLoadGroupMenu();
            }
        } else {
            KMessageBox::error(this, i18n("Can not save as empty name. Please use a new one."));
        }
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
        updateLoggingCategories();
    }
}

void KDebugSettingsDialog::slotRestoreDefault()
{
    mKdeApplicationSettingsPage->restoreToDefault();
}

void KDebugSettingsDialog::slotManageGroup()
{
    auto groupManagementDialog = new GroupManagementDialog(this);
    connect(groupManagementDialog, &GroupManagementDialog::groupsChanged, this, &KDebugSettingsDialog::updateLoadGroupMenu);
    groupManagementDialog->exec();
    delete groupManagementDialog;
}
