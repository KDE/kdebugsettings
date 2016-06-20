/*
  Copyright (c) 2015 Montel Laurent <montel@kde.org>

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

#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>
#include <KMessageBox>

#include <QFileDialog>
#include <QDialogButtonBox>
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
    readCategoriesFiles(envPath);
}

void KDebugSettingsDialog::readCategoriesFiles(const QString &path)
{
    // KDE debug categories area
    const QString confAreasFile = QStandardPaths::locate(QStandardPaths::ConfigLocation, QStringLiteral("kde.categories"));
    KDebugSettingsUtil::readLoggingCategories(confAreasFile, mCategories, false);

    // Load *.categories file in QStandardPaths::ConfigLocation for kde apps.
    QStringList dirs = QStandardPaths::locateAll(QStandardPaths::ConfigLocation, QString(), QStandardPaths::LocateDirectory);
    Q_FOREACH (const QString &dir, dirs) {
        const QStringList fileNames = QDir(dir).entryList(QStringList() << QStringLiteral("*.categories"));
        Q_FOREACH (const QString &file, fileNames) {
            if (file != QStringLiteral("kde.categories")) {
                KDebugSettingsUtil::readLoggingCategories(dir + file, mCategories);
            }
        }
    }

    // Load *.categories files. in qdebug.categories for external kde apps.
    dirs = QStandardPaths::locateAll(QStandardPaths::GenericConfigLocation, QStringLiteral("qdebug.categories/"), QStandardPaths::LocateDirectory);
    Q_FOREACH (const QString &dir, dirs) {
        const QStringList fileNames = QDir(dir).entryList(QStringList() << QStringLiteral("*.categories"));
        Q_FOREACH (const QString &file, fileNames) {
            KDebugSettingsUtil::readLoggingCategories(dir + QLatin1Char('/') + file, mCategories);
        }
    }
    const QByteArray rulesFilePath = qgetenv("QT_LOGGING_CONF");
    if (!rulesFilePath.isEmpty()) {
        const LoggingCategory::List envCategories = KDebugSettingsUtil::readLoggingQtCategories(QString::fromLatin1(rulesFilePath));
        //TODO
    }

    const QString environmentrules = QString::fromLatin1(qgetenv("QT_LOGGING_RULES"));
    if (!environmentrules.isEmpty()) {
        mEnvironmentSettingsRulesPage->setRules(environmentrules);
    }
    // qt logging.ini
    const QString envPath = path;
    LoggingCategory::List customCategories;
    bool foundOverrideRule = false;
    if (!envPath.isEmpty()) {
        const LoggingCategory::List qtCategories = KDebugSettingsUtil::readLoggingQtCategories(envPath);
#if 0 //FIXME
        Q_FOREACH (const LoggingCategory &cat, qtCategories) {
            bool foundkde = false;
            for (int i = 0; i < mCategories.count(); ++i) {
                LoggingCategory kdeCat = mCategories.at(i);
                if (cat.logName == kdeCat.logName) {
                    kdeCat.enabled = cat.enabled;
                    kdeCat.type = cat.type;
                    mCategories.replace(i, kdeCat);
                    foundkde = true;
                    break;
                }
            }
            if (!foundkde) {
                customCategories.append(cat);
            }
            if (cat.logName == QLatin1String("*")) {
                foundOverrideRule = true;
            }
        }
#endif
    }

    //FIXME mKdeApplicationSettingsPage->fillList(mCategories);
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
    Q_FOREACH (LoggingCategory cat, lstKde) {
        out << cat.createRule() + QLatin1Char('\n');
    }
    Q_FOREACH (LoggingCategory cat, lstCustom) {
        out << cat.createRule() + QLatin1Char('\n');
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

QString LoggingCategory::createRule()
{
    QString str = logName;
    if (!type.isEmpty()) {
        str += QLatin1Char('.') + type;
    }
    str += QLatin1String("=") + (enabled ? QLatin1Literal("true") : QLatin1Literal("false"));
    return str;
}

void KDebugSettingsDialog::slotApply()
{
    saveInQtLogging();
}

void KDebugSettingsDialog::slotInsertCategories()
{
    const QString path = QFileDialog::getOpenFileName(this, i18n("Insert Categories"));
    if (!path.isEmpty()) {
        const KdeLoggingCategory::List insertCategoriesList = KDebugSettingsUtil::readLoggingCategoriesForInserting(path, mCategories);
        //FIXME mKdeApplicationSettingsPage->insertCategories(insertCategoriesList);
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
    const QString path = QFileDialog::getOpenFileName(this, i18n("Load"));
    if (!path.isEmpty()) {
        readCategoriesFiles(path);
    }
}
