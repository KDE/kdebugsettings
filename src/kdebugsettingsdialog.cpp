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

#include "customdebugsettingspage.h"
#include "kdeapplicationdebugsettingpage.h"
#include "kdebugsettingsdialog.h"
#include "kdebugsettingsutil.h"

#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>

#include <QDialogButtonBox>
#include <QSettings>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QDebug>

KDebugSettingsDialog::KDebugSettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    mTabWidget = new QTabWidget;
    mTabWidget->setObjectName(QStringLiteral("tabwidget"));
    mainLayout->addWidget(mTabWidget);

    mKdeApplicationSettingsPage = new KDeApplicationDebugSettingPage(this);
    mKdeApplicationSettingsPage->setObjectName(QStringLiteral("kdeapplicationsettingspage"));
    mCustomSettingsPage = new CustomDebugSettingsPage(this);
    mCustomSettingsPage->setObjectName(QStringLiteral("customsettingspage"));
    mTabWidget->addTab(mKdeApplicationSettingsPage, i18n("KDE Application"));
    mTabWidget->addTab(mCustomSettingsPage, i18n("Custom Rules"));

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

    // qt logging.ini
    const QString envPath = QStandardPaths::locate(QStandardPaths::GenericConfigLocation, QStringLiteral("QtProject/qtlogging.ini"));
    Category::List customCategories;
    if (!envPath.isEmpty()) {
        const Category::List qtCategories = KDebugSettingsUtil::readLoggingQtCategories(envPath);
        Q_FOREACH(const Category &cat, qtCategories) {
            bool foundkde = false;
            for(int i = 0; i < categories.count(); ++i) {
                Category kdeCat = categories.at(i);
                if (cat.logName == kdeCat.logName) {
                    kdeCat.enabled = cat.enabled;
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
    const QStringList lstKde = mKdeApplicationSettingsPage->rules();
    const QStringList lstCustom = mCustomSettingsPage->rules();
    //Save in files.
#if 0
    QSettings settings("QtProject", "qtlogging");
    settings.beginGroup("Rules");
    settings.setValue();
    settings.endGroup();
#endif
    accept();
}
