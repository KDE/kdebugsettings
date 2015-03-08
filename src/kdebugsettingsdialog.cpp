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

#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>

#include <QDialogButtonBox>
#include <QSettings>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QDebug>
#include <QDir>

KDebugSettingsDialog::KDebugSettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

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

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &KDebugSettingsDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox);
    readConfig();
    readCategoriesFiles();
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

void KDebugSettingsDialog::readCategoriesFiles()
{
    // KDE debug categories area
    const QString confAreasFile = QStandardPaths::locate(QStandardPaths::ConfigLocation, QLatin1Literal("kde.categories"));
    Category::List categories = KDebugSettingsUtil::readLoggingCategories(confAreasFile);

    // TODO Load *.categories files.
    const QStringList dirs = QStandardPaths::locateAll(QStandardPaths::GenericConfigLocation, QStringLiteral("qdebug.categories/"), QStandardPaths::LocateDirectory);
    Q_FOREACH (const QString &dir, dirs) {
        const QStringList fileNames = QDir(dir).entryList(QStringList() << QStringLiteral("*.categories"));
        Q_FOREACH (const QString &file, fileNames) {
            Category::List categoriesLocal = KDebugSettingsUtil::readLoggingCategories(dir + QLatin1Char('/') + file);
            categories << categoriesLocal;
        }

    }
    const QByteArray rulesFilePath = qgetenv("QT_LOGGING_CONF");
    if (!rulesFilePath.isEmpty()) {
        const Category::List envCategories = KDebugSettingsUtil::readLoggingQtCategories(QString::fromLatin1(rulesFilePath));
        //TODO
    }

    const QString environmentrules = QString::fromLatin1(qgetenv("QT_LOGGING_RULES"));
    if (!environmentrules.isEmpty()) {
        mEnvironmentSettingsRulesPage->setRules(environmentrules);
    }
    // qt logging.ini
    const QString envPath = QStandardPaths::locate(QStandardPaths::GenericConfigLocation, QStringLiteral("QtProject/qtlogging.ini"));
    Category::List customCategories;
    if (!envPath.isEmpty()) {
        const Category::List qtCategories = KDebugSettingsUtil::readLoggingQtCategories(envPath);
        Q_FOREACH (const Category &cat, qtCategories) {
            bool foundkde = false;
            for (int i = 0; i < categories.count(); ++i) {
                Category kdeCat = categories.at(i);
                if (cat.logName == kdeCat.logName) {
                    kdeCat.enabled = cat.enabled;
                    kdeCat.type = cat.type;
                    categories.replace(i, kdeCat);
                    foundkde = true;
                    break;
                }
            }
            if (!foundkde) {
                customCategories.append(cat);
            }
        }
    }

    mKdeApplicationSettingsPage->fillList(categories);
    mCustomSettingsPage->fillList(customCategories);
}

void KDebugSettingsDialog::slotAccepted()
{
    //Save Rules
    const Category::List lstKde = mKdeApplicationSettingsPage->rules();
    const Category::List lstCustom = mCustomSettingsPage->rules();
    //Save in files.
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, QStringLiteral("QtProject"), QStringLiteral("qtlogging"));
    //Clean Rules
    settings.beginGroup(QStringLiteral("Rules"));
    settings.remove(QStringLiteral(""));
    Q_FOREACH (const Category &cat, lstKde) {
        QString str = cat.logName;
        if (!cat.type.isEmpty()) {
            str += QLatin1Char('.') + cat.type;
        }
        settings.setValue(str, cat.enabled);
    }
    Q_FOREACH (const Category &cat, lstCustom) {
        QString str = cat.logName;
        if (!cat.type.isEmpty()) {
            str += QLatin1Char('.') + cat.type;
        }
        settings.setValue(str, cat.enabled);
    }

    settings.endGroup();
    accept();
}
