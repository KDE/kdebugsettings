/*
  Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

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
#include <QTextStream>
#include "kdebugsettings_debug.h"

KDebugSettingsDialog::KDebugSettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    mCategoryWarning = new CategoryWarning(this);
    mCategoryWarning->setObjectName(QStringLiteral("categorywarning"));
    mainLayout->addWidget(mCategoryWarning);

    mTabWidget = new QTabWidget;
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

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Help | QDialogButtonBox::Apply);
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
    mainLayout->addWidget(buttonBox);
    readConfig();
    readQtLoggingFile();
}

KDebugSettingsDialog::~KDebugSettingsDialog()
{
    saveConfig();
}

void KDebugSettingsDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "KDebugSettingsDialog");
    const QSize size = group.readEntry("Size", QSize(600, 400));
    if (size.isValid()) {
        resize(size);
    }
}

void KDebugSettingsDialog::saveConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "KDebugSettingsDialog");
    group.writeEntry("Size", size());
    group.sync();
}

void KDebugSettingsDialog::readQtLoggingFile()
{
    const QString envPath = QStandardPaths::locate(QStandardPaths::GenericConfigLocation, QStringLiteral("QtProject/qtlogging.ini"));
    if (!envPath.isEmpty()) {
        readCategoriesFiles(envPath);
    } else {
        const QString dataPath = QDir(QLibraryInfo::location(QLibraryInfo::DataPath)).absoluteFilePath(QStringLiteral("qtlogging.ini"));
        readCategoriesFiles(dataPath);
    }
}

void KDebugSettingsDialog::readCategoriesFiles(const QString &path)
{
    // KDE debug categories area
    const QString confAreasFile = QStandardPaths::locate(QStandardPaths::ConfigLocation, QStringLiteral("kde.categories"));
    KDebugSettingsUtil::readLoggingCategories(confAreasFile, mCategoriesList, false);

    mRenameCategoriesList.clear();
    // Load *.renamecategories file in QStandardPaths::ConfigLocation for kde apps.
    const QStringList dirs = QStandardPaths::locateAll(QStandardPaths::ConfigLocation, QString(), QStandardPaths::LocateDirectory);
    for (const QString &dir : dirs) {
        const QStringList fileNames = QDir(dir).entryList(QStringList() << QStringLiteral("*.renamecategories"));
        for (const QString &file : fileNames) {
            mRenameCategoriesList.append(KDebugSettingsUtil::readRenameCategories(dir + file));
        }
    }
    //TODO add load rename file from external kde apps.
    const QStringList dirs2 = QStandardPaths::locateAll(QStandardPaths::GenericConfigLocation, QStringLiteral("qdebug.categories/"), QStandardPaths::LocateDirectory);
    for (const QString &dir : dirs2) {
        const QStringList fileNames = QDir(dir).entryList(QStringList() << QStringLiteral("*.renamecategories"));
        for (const QString &file : fileNames) {
            mRenameCategoriesList.append(KDebugSettingsUtil::readRenameCategories(dir + file));
        }
    }

    // Load *.categories file in QStandardPaths::ConfigLocation for kde apps.
    const QStringList dirs3 = QStandardPaths::locateAll(QStandardPaths::ConfigLocation, QString(), QStandardPaths::LocateDirectory);
    for (const QString &dir : dirs3) {
        const QStringList fileNames = QDir(dir).entryList(QStringList() << QStringLiteral("*.categories"));
        for (const QString &file : fileNames) {
            if (file != QStringLiteral("kde.categories")) {
                KDebugSettingsUtil::readLoggingCategories(dir + file, mCategoriesList, true);
            }
        }
    }

    // Load *.categories files. in qdebug.categories for external kde apps.
    const QStringList dirs4 = QStandardPaths::locateAll(QStandardPaths::GenericConfigLocation, QStringLiteral("qdebug.categories/"), QStandardPaths::LocateDirectory);
    for (const QString &dir : dirs4) {
        const QStringList fileNames = QDir(dir).entryList(QStringList() << QStringLiteral("*.categories"));
        for (const QString &file : fileNames) {
            KDebugSettingsUtil::readLoggingCategories(dir + QLatin1Char('/') + file, mCategoriesList, true);
        }
    }


    const QByteArray rulesFilePath = qgetenv("QT_LOGGING_CONF");
    if (!rulesFilePath.isEmpty()) {
        const QList<KDebugSettingsUtil::LoadLoggingCategory> envCategories = KDebugSettingsUtil::readLoggingQtCategories(QString::fromLatin1(rulesFilePath));
        //TODO
    }

    const QString environmentrules = QString::fromLatin1(qgetenv("QT_LOGGING_RULES"));
    if (!environmentrules.isEmpty()) {
        mEnvironmentSettingsRulesPage->setRules(environmentrules);
    }
    // qt logging.ini
    LoadCategoriesJob job;
    job.setFileName(path);
    job.setCategories(mCategoriesList);
    job.setRenamedCategories(mRenameCategoriesList);
    job.start();

    const LoggingCategory::List customCategories = job.customCategories();
    const LoggingCategory::List qtKdeCategories = job.qtKdeCategories();
    const bool foundOverrideRule = job.foundOverrideRule();

    mKdeApplicationSettingsPage->fillList(qtKdeCategories);
    mCustomSettingsPage->fillList(customCategories);
    if (foundOverrideRule) {
        mCategoryWarning->animatedShow();
    }
}

bool KDebugSettingsDialog::saveRules(const QString &path)
{
    QFile qtlogging(path);
    if (!qtlogging.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        KMessageBox::error(this, i18n("\'%1\' cannot be opened. Please verify it.", path));
        return false;
    }
    //Save Rules
    const LoggingCategory::List lstKde = mKdeApplicationSettingsPage->rules();
    const LoggingCategory::List lstCustom = mCustomSettingsPage->rules();
    QTextStream out(&qtlogging);
    out << QLatin1String("[Rules]\n");
    for (LoggingCategory cat : lstKde) {
        out << cat.createRule() + QLatin1Char('\n');
    }
    for (LoggingCategory cat : lstCustom) {
        out << cat.createCustomRule() + QLatin1Char('\n');
    }
    return true;
}

bool KDebugSettingsDialog::saveInQtLogging()
{
    const QString envPath = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + QLatin1String("/QtProject");
    QDir().mkpath(envPath);
    return saveRules(envPath + QStringLiteral("/qtlogging.ini"));
}

void KDebugSettingsDialog::slotAccepted()
{
    if (saveInQtLogging()) {
        accept();
    }
}

void KDebugSettingsDialog::slotHelpRequested()
{
    QDesktopServices::openUrl(QUrl(QStringLiteral("http://doc.qt.io/qt-5/qloggingcategory.html#details")));
}

void KDebugSettingsDialog::slotApply()
{
    saveInQtLogging();
}

void KDebugSettingsDialog::slotInsertCategories()
{
    const QString path = QFileDialog::getOpenFileName(this, i18n("Insert Categories"));
    if (!path.isEmpty()) {
        const KdeLoggingCategory::List insertCategoriesList = KDebugSettingsUtil::readLoggingCategoriesForInserting(path, mCategoriesList);
        LoggingCategory::List newCategories;
        for (const KdeLoggingCategory &cat : qAsConst(insertCategoriesList)) {
            LoggingCategory loggingCat;
            loggingCat.description = cat.description;
            loggingCat.logName = cat.logName;
            if (loggingCat.isValid()) {
                newCategories.append(loggingCat);
            }
        }
        mKdeApplicationSettingsPage->insertCategories(newCategories);
    }
}

void KDebugSettingsDialog::slotSaveAs()
{
    const QString path = QFileDialog::getSaveFileName(this, i18n("Save As"));
    if (!path.isEmpty()) {
        saveRules(path);
    }
}

void KDebugSettingsDialog::slotLoad()
{
    const QString path = QFileDialog::getOpenFileName(this, i18n("Load Debug Settings Files"));
    if (!path.isEmpty()) {
        readCategoriesFiles(path);
    }
}
