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

#ifndef KDEBUGSETTINGSDIALOG_H
#define KDEBUGSETTINGSDIALOG_H

#include <QDialog>
#include "kdebugsettingsloadingcategories.h"
#include "kdeloggingcategory.h"
#include "renamecategory.h"
#include "libkdebugsettings_export.h"
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

#endif // KDEBUGSETTINGSDIALOG_H
