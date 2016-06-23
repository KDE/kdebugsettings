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
#include <QObject>
#include <QDebug>
#include "kdeloggingcategory.h"
#include "loggingcategory.h"
namespace KDebugSettingsUtil
{

struct LineLoggingQtCategory {
    LineLoggingQtCategory()
        : enabled(true),
          type(Unknown)
    {

    }
    enum LoggingType {
        Unknown = 0,
        Info,
        Warning,
        Debug,
        Critical,
        All
    };

    bool isValid() const {
        return !logName.isEmpty();
    }
    bool operator ==(const LineLoggingQtCategory &other) const
    {
        return (enabled == other.enabled) &&
               (type == other.type) &&
               (logName == other.logName);
    }
    bool enabled;
    LoggingType type;
    QString logName;
};

struct LoadLoggingCategory {
    LoadLoggingCategory()
    {

    }
    typedef QVector<LoadLoggingCategory> List;
    enum LogType {
        Unknown = 0,
        Off,
        Info,
        Warning,
        Debug,
        Critical,
        All
    };

    bool isValid() const
    {
        return !logName.isEmpty();
    }

    bool operator ==(const LoadLoggingCategory &other) const
    {
        qDebug() << " logname " << logName << " other.logName :" << other.logName;
        return (logName == other.logName) &&
               (loggingTypes == other.loggingTypes);
    }
    QString logName;
    QHash<LoadLoggingCategory::LogType, bool> loggingTypes;
};

void readLoggingCategories(const QString &filename, KdeLoggingCategory::List &categoriesList, bool checkCategoryList = false);

KdeLoggingCategory parseLineKdeLoggingCategory(QString line);
KdeLoggingCategory::List readLoggingCategoriesForInserting(const QString &filename, KdeLoggingCategory::List &categoriesList);

QList<LoadLoggingCategory> readLoggingQtCategories(const QString &filename);
KDebugSettingsUtil::LineLoggingQtCategory parseLineLoggingQtCategory(const QString &line);
}

Q_DECLARE_METATYPE(KDebugSettingsUtil::LoadLoggingCategory::LogType)

Q_DECLARE_METATYPE(KDebugSettingsUtil::LineLoggingQtCategory::LoggingType)

#endif // KDEBUGSETTINGSUTIL_H
