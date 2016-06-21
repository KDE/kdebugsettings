/*
  Copyright (c) 2015-2016 Montel Laurent <montel@kde.org>

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

#ifndef KDEBUGSETTINGSUTIL_H
#define KDEBUGSETTINGSUTIL_H

#include <QString>
#include "kdeloggingcategory.h"
#include "loggingcategory.h"
namespace KDebugSettingsUtil
{

struct LoadLoggingCategory
{
    LoadLoggingCategory()
        : enabled(true),
          type(Unknown)
    {

    }

    enum LogType {
        Unknown = 0,
        Info = 1,
        Warning = 2,
        Debug = 4,
        Critical = 8,
        All = 16
    };
    Q_FLAGS(LogTypes)
    Q_DECLARE_FLAGS(LogTypes, LogType)

    bool isValid() const {
        return (type != Unknown);
    }

    bool enabled;
    LogTypes type;
    QString logName;
};


void readLoggingCategories(const QString &filename, KdeLoggingCategory::List &categoriesList, bool checkCategoryList = false);

KdeLoggingCategory parseLineKdeLoggingCategory(QString line);
KdeLoggingCategory::List readLoggingCategoriesForInserting(const QString &filename, KdeLoggingCategory::List &categoriesList);

LoggingCategory::List readLoggingQtCategories(const QString &filename);
KDebugSettingsUtil::LoadLoggingCategory parseLineLoggingQtCategory(const QString &line);
}

#endif // KDEBUGSETTINGSUTIL_H
