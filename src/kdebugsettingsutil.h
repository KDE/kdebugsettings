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

#ifndef KDEBUGSETTINGSUTIL_H
#define KDEBUGSETTINGSUTIL_H

#include <QString>
#include <QDebug>
#include "kdeloggingcategory.h"
#include "loggingcategory.h"
#include "renamecategory.h"
#include "libkdebugsettings_export.h"

namespace KDebugSettingsUtil {
struct LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT LineLoggingQtCategory {
    LineLoggingQtCategory()
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

    Q_REQUIRED_RESULT bool isValid() const
    {
        return !logName.isEmpty();
    }

    Q_REQUIRED_RESULT bool operator ==(const LineLoggingQtCategory &other) const
    {
        return (enabled == other.enabled)
               && (type == other.type)
               && (logName == other.logName);
    }

    bool enabled = true;
    LoggingType type = Unknown;
    QString logName;
};

struct LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT LoadLoggingCategory {
    enum Status {
        Enabled = 0,
        Disabled = 1,
        UnknownStatus = 2
    };

    enum LogType {
        Unknown = 0,
        Off,
        Info,
        Warning,
        Debug,
        Critical,
        All
    };

    LoadLoggingCategory()
    {
        for (int i = LoadLoggingCategory::Unknown; i <= LoadLoggingCategory::All; ++i) {
            loggingTypes.insert(static_cast<LoadLoggingCategory::LogType>(i), UnknownStatus);
        }
    }

    using List = QVector<LoadLoggingCategory>;

    bool isValid() const
    {
        return !logName.isEmpty();
    }

    Q_REQUIRED_RESULT bool operator ==(const LoadLoggingCategory &other) const
    {
        //qDebug() << " logname " << logName << " other.logName :" << other.logName;
        return (logName == other.logName)
               && (loggingTypes == other.loggingTypes);
    }

    QString logName;
    QMap<LoadLoggingCategory::LogType, LoadLoggingCategory::Status> loggingTypes;
};

LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT void readLoggingCategories(const QString &filename, KdeLoggingCategory::List &categoriesList, bool checkCategoryList = false);

LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT Q_REQUIRED_RESULT KdeLoggingCategory parseLineKdeLoggingCategory(QString line, const QString &filename);
LIBKDEBUGSETTINGS_EXPORT Q_REQUIRED_RESULT KdeLoggingCategory::List readLoggingCategoriesForInserting(const QString &filename, KdeLoggingCategory::List &categoriesList);

LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT Q_REQUIRED_RESULT QList<LoadLoggingCategory> readLoggingQtCategories(const QString &filename);
LIBKDEBUGSETTINGS_EXPORT Q_REQUIRED_RESULT KDebugSettingsUtil::LineLoggingQtCategory parseLineLoggingQtCategory(const QString &line);
LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT Q_REQUIRED_RESULT RenameCategory parseRenameCategory(QString line, const QString &filename);
LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT Q_REQUIRED_RESULT RenameCategory::List readRenameCategories(const QString &filename);
LIBKDEBUGSETTINGS_EXPORT Q_REQUIRED_RESULT LoggingCategory::LoggingType convertCategoryTypeFromString(const QString &str);
LIBKDEBUGSETTINGS_EXPORT Q_REQUIRED_RESULT QString convertCategoryTypeToString(LoggingCategory::LoggingType type);
LIBKDEBUGSETTINGS_EXPORT Q_REQUIRED_RESULT QString qtFileName();
}

Q_DECLARE_METATYPE(KDebugSettingsUtil::LoadLoggingCategory::LogType)

Q_DECLARE_METATYPE(KDebugSettingsUtil::LineLoggingQtCategory::LoggingType)

#endif // KDEBUGSETTINGSUTIL_H
