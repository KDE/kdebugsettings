/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "kdebugsettingsloadingcategories.h"
#include "kdeloggingcategory.h"
#include "libkdebugsettings_export.h"
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
    LIBKDEBUGSETTINGS_NO_EXPORT void slotAccepted();
    LIBKDEBUGSETTINGS_NO_EXPORT void slotApply();
    LIBKDEBUGSETTINGS_NO_EXPORT void slotSaveAs();
    LIBKDEBUGSETTINGS_NO_EXPORT void slotLoad();
    LIBKDEBUGSETTINGS_NO_EXPORT void slotInsertCategories();
    LIBKDEBUGSETTINGS_NO_EXPORT void slotRestoreDefault();

    LIBKDEBUGSETTINGS_NO_EXPORT void readQtLoggingFile();
    LIBKDEBUGSETTINGS_NO_EXPORT bool saveRules(const QString &path, bool forceSavingAllRules = false);
    LIBKDEBUGSETTINGS_NO_EXPORT bool saveInQtLogging();
    LIBKDEBUGSETTINGS_NO_EXPORT void saveConfig();
    LIBKDEBUGSETTINGS_NO_EXPORT void readConfig();
    LIBKDEBUGSETTINGS_NO_EXPORT void updateLoggingCategories();
    LIBKDEBUGSETTINGS_NO_EXPORT void slotLoadGroup(const QString &fullPath);
    LIBKDEBUGSETTINGS_NO_EXPORT void slotSaveAsGroup();
    LIBKDEBUGSETTINGS_NO_EXPORT void slotManageGroup();
    KdeLoggingCategory::List mCategoriesList;
    KDebugSettingsLoadingCategories mLoggings;
    QTabWidget *const mTabWidget;
    KDEApplicationDebugSettingPage *const mKdeApplicationSettingsPage;
    CustomDebugSettingsPage *const mCustomSettingsPage;
    EnvironmentSettingsRulesPage *const mEnvironmentSettingsRulesPage;
    CategoryWarning *const mCategoryWarning;
    LoadToolButton *const mLoadToolButton;
};
