/*
  Copyright (c) 2015-2019 Montel Laurent <montel@kde.org>

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
#include "kdeloggingcategory.h"
#include "renamecategory.h"
class QTabWidget;
class KDEApplicationDebugSettingPage;
class CustomDebugSettingsPage;
class EnvironmentSettingsRulesPage;
class CategoryWarning;

class KDebugSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit KDebugSettingsDialog(QWidget *parent = nullptr);
    ~KDebugSettingsDialog();

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
    void readCategoriesFiles(const QString &path);
    void saveConfig();
    void readConfig();
    KdeLoggingCategory::List mCategoriesList;
    RenameCategory::List mRenameCategoriesList;
    QTabWidget *mTabWidget = nullptr;
    KDEApplicationDebugSettingPage *mKdeApplicationSettingsPage = nullptr;
    CustomDebugSettingsPage *mCustomSettingsPage = nullptr;
    EnvironmentSettingsRulesPage *mEnvironmentSettingsRulesPage = nullptr;
    CategoryWarning *mCategoryWarning = nullptr;
};

#endif // KDEBUGSETTINGSDIALOG_H
