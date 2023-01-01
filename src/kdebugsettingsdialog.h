/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "kdebugsettingsloadingcategories.h"
#include "kdeloggingcategory.h"
#include "libkdebugsettings_export.h"
#include "renamecategory.h"
#include <QDialog>
class QTabWidget;
class KDEApplicationDebugSettingPage;
class CustomDebugSettingsPage;
class EnvironmentSettingsRulesPage;
class CategoryWarning;
class LoadToolButton;

class LIBKDEBUGSETTINGS_EXPORT KDebugSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit KDebugSettingsDialog(QWidget *parent = nullptr);
    ~KDebugSettingsDialog() override;

Q_SIGNALS:
    void updateLoadGroupMenu();

private:
    void slotAccepted();
    void slotHelpRequested();
    void slotApply();
    void slotSaveAs();
    void slotLoad();
    void slotInsertCategories();
    void slotRestoreDefault();

    void readQtLoggingFile();
    bool saveRules(const QString &path, bool forceSavingAllRules = false);
    bool saveInQtLogging();
    void saveConfig();
    void readConfig();
    void updateLoggingCategories();
    void slotLoadGroup(const QString &fullPath);
    void slotSaveAsGroup();
    void slotManageGroup();
    KdeLoggingCategory::List mCategoriesList;
    KDebugSettingsLoadingCategories mLoggings;
    QTabWidget *mTabWidget = nullptr;
    KDEApplicationDebugSettingPage *mKdeApplicationSettingsPage = nullptr;
    CustomDebugSettingsPage *mCustomSettingsPage = nullptr;
    EnvironmentSettingsRulesPage *mEnvironmentSettingsRulesPage = nullptr;
    CategoryWarning *mCategoryWarning = nullptr;
    LoadToolButton *mLoadToolButton = nullptr;
};
