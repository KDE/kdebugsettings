/*
    SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdebugsettingsdialog.h"
using namespace Qt::Literals::StringLiterals;

#include "categorywarning.h"
#include "customdebugsettingspage.h"
#include "environmentsettingsrulespage.h"
#include "groupmanagementdialog.h"
#include "jobs/saverulesjob.h"
#include "kdeapplicationdebugsettingpage.h"
#include "kdebugsettings_debug.h"
#include "kdebugsettingsutil.h"
#include "loadtoolbutton.h"
#include "loggingmanager.h"
#include "savetoolbutton.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KMessageBox>
#include <KSharedConfig>
#include <KWindowConfig>

#include <QDialogButtonBox>
#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWindow>

#include <KAboutData>
#include <KHelpMenu>

namespace
{
constexpr char KDebugSettingsDialogGroupName[] = "KDebugSettingsDialog";
}
KDebugSettingsDialog::KDebugSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , mTabWidget(new QTabWidget(this))
    , mKdeApplicationSettingsPage(new KDEApplicationDebugSettingPage(this))
    , mCustomSettingsPage(new CustomDebugSettingsPage(this))
    , mEnvironmentSettingsRulesPage(new EnvironmentSettingsRulesPage(this))
    , mCategoryWarning(new CategoryWarning(this))
    , mLoadToolButton(new LoadToolButton(this))
{
    auto mainLayout = new QVBoxLayout(this);

    mCategoryWarning->setObjectName("categorywarning"_L1);
    mainLayout->addWidget(mCategoryWarning);

    mTabWidget->setObjectName("tabwidget"_L1);
    mainLayout->addWidget(mTabWidget);

    mKdeApplicationSettingsPage->setObjectName("kdeapplicationsettingspage"_L1);
    mCustomSettingsPage->setObjectName("customsettingspage"_L1);
    mEnvironmentSettingsRulesPage->setObjectName("environmentsettingsrulespage"_L1);
    mTabWidget->addTab(mKdeApplicationSettingsPage, i18n("KDE Application"));
    mTabWidget->addTab(mCustomSettingsPage, i18n("Custom Rules"));
    mTabWidget->addTab(mEnvironmentSettingsRulesPage, i18n("Rules Settings With Environment Variable"));
    mTabWidget->setFocusPolicy(Qt::NoFocus);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::RestoreDefaults | QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Help
                                              | QDialogButtonBox::Apply,
                                          this);
    buttonBox->setObjectName("buttonbox"_L1);

    auto saveAs = new SaveToolButton(this);
    saveAs->setText(i18n("Save As…"));
    saveAs->setObjectName("saveas_button"_L1);
    buttonBox->addButton(saveAs, QDialogButtonBox::ActionRole);
    connect(saveAs, &SaveToolButton::saveAsFile, this, &KDebugSettingsDialog::slotSaveAs);
    connect(saveAs, &SaveToolButton::saveAsGroup, this, &KDebugSettingsDialog::slotSaveAsGroup);

    mLoadToolButton->setObjectName("load_button"_L1);
    buttonBox->addButton(mLoadToolButton, QDialogButtonBox::ActionRole);
    connect(mLoadToolButton, &LoadToolButton::loadFromFile, this, &KDebugSettingsDialog::slotLoad);
    connect(mLoadToolButton, &LoadToolButton::loadGroupRequested, this, &KDebugSettingsDialog::slotLoadGroup);
    connect(mLoadToolButton, &LoadToolButton::manageGroupRequested, this, &KDebugSettingsDialog::slotManageGroup);
    connect(this, &KDebugSettingsDialog::updateLoadGroupMenu, mLoadToolButton, &LoadToolButton::updateLoadGroupMenu);

    auto insertCategories = new QPushButton(i18nc("@action:button", "Insert…"), this);
    insertCategories->setObjectName("insert_button"_L1);
    buttonBox->addButton(insertCategories, QDialogButtonBox::ActionRole);
    connect(insertCategories, &QPushButton::clicked, this, &KDebugSettingsDialog::slotInsertCategories);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &KDebugSettingsDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

#if KXMLGUI_VERSION >= QT_VERSION_CHECK(6, 9, 0)
    auto helpMenu = new KHelpMenu(this, KAboutData::applicationData());
    helpMenu->setShowWhatsThis(false);
#else
    auto helpMenu = new KHelpMenu(this, KAboutData::applicationData(), false);
#endif
    buttonBox->button(QDialogButtonBox::Help)->setMenu(helpMenu->menu());

    connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this, &KDebugSettingsDialog::slotApply);
    connect(buttonBox->button(QDialogButtonBox::RestoreDefaults), &QPushButton::clicked, this, &KDebugSettingsDialog::slotRestoreDefault);
    mainLayout->addWidget(buttonBox);
    readConfig();
    updateLoggingCategories();
    mKdeApplicationSettingsPage->forceFocus();
}

KDebugSettingsDialog::~KDebugSettingsDialog()
{
    saveConfig();
}

void KDebugSettingsDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(600, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(KDebugSettingsDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void KDebugSettingsDialog::saveConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(QLatin1StringView(KDebugSettingsDialogGroupName)));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void KDebugSettingsDialog::slotLoadGroup(const QString &fullPath)
{
    if (!fullPath.isEmpty()) {
        LoggingManager::self().readCategoriesFiles(fullPath);
        updateLoggingCategories();
    }
}

void KDebugSettingsDialog::updateLoggingCategories()
{
    if (!LoggingManager::self().environmentrules().isEmpty()) {
        mEnvironmentSettingsRulesPage->setRules(LoggingManager::self().environmentrules());
    }
    const bool foundOverrideRule = LoggingManager::self().foundOverrideRule();

    if (foundOverrideRule) {
        mCategoryWarning->animatedShow();
    }
    LoggingManager::self().updateLoggingCategories();
    mCategoriesList = LoggingManager::self().categoriesList();
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

void KDebugSettingsDialog::slotApply()
{
    saveInQtLogging();
}

void KDebugSettingsDialog::slotInsertCategories()
{
    const QString path = QFileDialog::getOpenFileName(this, i18n("Insert Categories"), QString(), u"%1 (*.categories)"_s.arg(i18n("Categories Files")));
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
        KMessageBox::information(this, i18n("Categories from file \'%1\' inserted.", path), i18nc("@title:window", "Insert Categories"));
    }
}

void KDebugSettingsDialog::slotSaveAsGroup()
{
    const QString groupPath = KDebugSettingsUtil::defaultWritableGroupPath();
    bool ok = false;
    const QString name = QInputDialog::getText(this, i18nc("@title:window", "Group Name"), i18n("Name:"), QLineEdit::Normal, QString(), &ok);
    if (ok) {
        const QString trimmedName = name.trimmed();
        if (!trimmedName.isEmpty()) {
            if (mLoadToolButton->groupNames().contains(trimmedName)) {
                KMessageBox::error(this, i18n("<b>\'%1\'</b> is already used as a group name.\nPlease save as another name.", trimmedName));
            } else {
                if (!QDir().mkpath(groupPath)) {
                    qCWarning(KDEBUGSETTINGS_LOG) << "Unable to create folder: " << groupPath;
                }
                saveRules(groupPath + u'/' + trimmedName, true);
                Q_EMIT updateLoadGroupMenu();
            }
        } else {
            KMessageBox::error(this, i18n("Can not save as empty name. Please use a new one."));
        }
    }
}

void KDebugSettingsDialog::slotSaveAs()
{
    const QString path = QFileDialog::getSaveFileName(this, i18nc("@title:window", "Save As"), QString(), i18n("KDebugSettings File (*.kdebugsettingsrules)"));
    if (!path.isEmpty()) {
        saveRules(path, true);
    }
}

void KDebugSettingsDialog::slotLoad()
{
    const QString path =
        QFileDialog::getOpenFileName(this, i18nc("@title:window", "Load Debug Settings Files"), QString(), i18n("KDebugSettings File (*.kdebugsettingsrules)"));
    if (!path.isEmpty()) {
        LoggingManager::self().readCategoriesFiles(path);
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

#include "moc_kdebugsettingsdialog.cpp"
