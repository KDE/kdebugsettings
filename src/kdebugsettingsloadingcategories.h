/*
  Copyright (c) 2019 Montel Laurent <montel@kde.org>

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

#ifndef KDEBUGSETTINGSLOADINGCATEGORIES_H
#define KDEBUGSETTINGSLOADINGCATEGORIES_H

#include <QString>
#include "kdeloggingcategory.h"
#include "renamecategory.h"
#include "loggingcategory.h"
#include "kdebugsettingsprivate_export.h"

class KDEBUGSETTINGSPRIVATE_EXPORT KDebugSettingsLoadingCategories
{
public:
    KDebugSettingsLoadingCategories();
    ~KDebugSettingsLoadingCategories();

    void readQtLoggingFile();

    Q_REQUIRED_RESULT QString environmentrules() const;
    Q_REQUIRED_RESULT RenameCategory::List renameCategoriesList() const;
    Q_REQUIRED_RESULT KdeLoggingCategory::List categoriesList() const;
    Q_REQUIRED_RESULT LoggingCategory::List customCategories() const;
    Q_REQUIRED_RESULT LoggingCategory::List qtKdeCategories() const;
    Q_REQUIRED_RESULT bool foundOverrideRule() const;

private:
    void readCategoriesFiles(const QString &path);
    KdeLoggingCategory::List mCategoriesList;
    RenameCategory::List mRenameCategoriesList;
    QString mEnvironmentrules;

    LoggingCategory::List mCustomCategories;
    LoggingCategory::List mQtKdeCategories;
    bool mFoundOverrideRule = false;
};

#endif // KDEBUGSETTINGSLOADINGCATEGORIES_H
