/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "kdeloggingcategory.h"
#include "libkdebugsettingscore_export.h"
#include "loggingcategory.h"
#include "renamecategory.h"
#include <QDebug>
#include <QString>

namespace KDebugSettingsUtil
{
struct LIBKDEBUGSETTINGSCORE_EXPORT LineLoggingQtCategory {
    LineLoggingQtCategory() = default;

    enum LoggingType {
        Unknown = 0,
        Info,
        Warning,
        Debug,
        Critical,
        All,
    };

    Q_REQUIRED_RESULT bool isValid() const
    {
        return !logName.isEmpty();
    }

    Q_REQUIRED_RESULT bool operator==(const LineLoggingQtCategory &other) const
    {
        return (enabled == other.enabled) && (type == other.type) && (logName == other.logName);
    }

    bool enabled = true;
    LoggingType type = Unknown;
    QString logName;
};

struct LIBKDEBUGSETTINGSCORE_EXPORT LoadLoggingCategory {
    enum Status {
        Enabled = 0,
        Disabled = 1,
        UnknownStatus = 2,
    };

    enum LogType {
        Unknown = 0,
        Off,
        Info,
        Warning,
        Debug,
        Critical,
        All,
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

    Q_REQUIRED_RESULT bool operator==(const LoadLoggingCategory &other) const
    {
        // qDebug() << " logname " << logName << " other.logName :" << other.logName;
        return (logName == other.logName) && (loggingTypes == other.loggingTypes);
    }

    QString logName;
    QMap<LoadLoggingCategory::LogType, LoadLoggingCategory::Status> loggingTypes;
};

LIBKDEBUGSETTINGSCORE_EXPORT void readLoggingCategories(const QString &filename, KdeLoggingCategory::List &categoriesList, bool checkCategoryList = false);

Q_REQUIRED_RESULT LIBKDEBUGSETTINGSCORE_EXPORT KdeLoggingCategory parseLineKdeLoggingCategory(QString line, const QString &filename);
Q_REQUIRED_RESULT LIBKDEBUGSETTINGSCORE_EXPORT KdeLoggingCategory::List readLoggingCategoriesForInserting(const QString &filename,
                                                                                                          KdeLoggingCategory::List &categoriesList);

Q_REQUIRED_RESULT LIBKDEBUGSETTINGSCORE_EXPORT QList<LoadLoggingCategory> readLoggingQtCategories(const QString &filename);
Q_REQUIRED_RESULT LIBKDEBUGSETTINGSCORE_EXPORT KDebugSettingsUtil::LineLoggingQtCategory parseLineLoggingQtCategory(const QString &line);
Q_REQUIRED_RESULT LIBKDEBUGSETTINGSCORE_EXPORT RenameCategory parseRenameCategory(QString line, const QString &filename);
Q_REQUIRED_RESULT LIBKDEBUGSETTINGSCORE_EXPORT RenameCategory::List readRenameCategories(const QString &filename);
Q_REQUIRED_RESULT LIBKDEBUGSETTINGSCORE_EXPORT LoggingCategory::LoggingType convertCategoryTypeFromString(const QString &str);
Q_REQUIRED_RESULT LIBKDEBUGSETTINGSCORE_EXPORT QString convertCategoryTypeToString(LoggingCategory::LoggingType type);
Q_REQUIRED_RESULT LIBKDEBUGSETTINGSCORE_EXPORT QString qtFileName();
Q_REQUIRED_RESULT LIBKDEBUGSETTINGSCORE_EXPORT bool hasWritableGroups();
Q_REQUIRED_RESULT LIBKDEBUGSETTINGSCORE_EXPORT QString defaultWritableGroupPath();
Q_REQUIRED_RESULT LIBKDEBUGSETTINGSCORE_EXPORT QStringList groupFileList();
Q_REQUIRED_RESULT LIBKDEBUGSETTINGSCORE_EXPORT LoggingCategory convertRuleStrToLoggingCategory(const QString &ruleStr);
}

Q_DECLARE_METATYPE(KDebugSettingsUtil::LoadLoggingCategory::LogType)

Q_DECLARE_METATYPE(KDebugSettingsUtil::LineLoggingQtCategory::LoggingType)
