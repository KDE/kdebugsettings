/*
    SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] bool isValid() const
    {
        return !logName.isEmpty();
    }

    [[nodiscard]] bool operator==(const LineLoggingQtCategory &other) const
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

    using List = QList<LoadLoggingCategory>;

    bool isValid() const
    {
        return !logName.isEmpty();
    }

    [[nodiscard]] bool operator==(const LoadLoggingCategory &other) const
    {
        // qDebug() << " logname " << logName << " other.logName :" << other.logName;
        return (logName == other.logName) && (loggingTypes == other.loggingTypes);
    }

    QString logName;
    QMap<LoadLoggingCategory::LogType, LoadLoggingCategory::Status> loggingTypes;
};

LIBKDEBUGSETTINGSCORE_EXPORT void readLoggingCategories(const QString &filename, KdeLoggingCategory::List &categoriesList, bool checkCategoryList = false);

[[nodiscard]] LIBKDEBUGSETTINGSCORE_EXPORT KdeLoggingCategory parseLineKdeLoggingCategory(QString line, const QString &filename);
[[nodiscard]] LIBKDEBUGSETTINGSCORE_EXPORT KdeLoggingCategory::List readLoggingCategoriesForInserting(const QString &filename,
                                                                                                      KdeLoggingCategory::List &categoriesList);

[[nodiscard]] LIBKDEBUGSETTINGSCORE_EXPORT QList<LoadLoggingCategory> readLoggingQtCategories(const QString &filename);
[[nodiscard]] LIBKDEBUGSETTINGSCORE_EXPORT KDebugSettingsUtil::LineLoggingQtCategory parseLineLoggingQtCategory(const QString &line);
[[nodiscard]] LIBKDEBUGSETTINGSCORE_EXPORT RenameCategory parseRenameCategory(QString line, const QString &filename);
[[nodiscard]] LIBKDEBUGSETTINGSCORE_EXPORT RenameCategory::List readRenameCategories(const QString &filename);
[[nodiscard]] LIBKDEBUGSETTINGSCORE_EXPORT LoggingCategory::LoggingType convertCategoryTypeFromString(const QString &str);
[[nodiscard]] LIBKDEBUGSETTINGSCORE_EXPORT QString convertCategoryTypeToString(LoggingCategory::LoggingType type);
[[nodiscard]] LIBKDEBUGSETTINGSCORE_EXPORT QString qtFileName();
[[nodiscard]] LIBKDEBUGSETTINGSCORE_EXPORT bool hasWritableGroups();
[[nodiscard]] LIBKDEBUGSETTINGSCORE_EXPORT QString defaultWritableGroupPath();
[[nodiscard]] LIBKDEBUGSETTINGSCORE_EXPORT QStringList groupFileList();
[[nodiscard]] LIBKDEBUGSETTINGSCORE_EXPORT LoggingCategory convertRuleStrToLoggingCategory(const QString &ruleStr);
[[nodiscard]] LIBKDEBUGSETTINGSCORE_EXPORT QString generateDisplayRule(const QString &categoryName, bool state, LoggingCategory::LoggingType type);
}

Q_DECLARE_METATYPE(KDebugSettingsUtil::LoadLoggingCategory::LogType)

Q_DECLARE_METATYPE(KDebugSettingsUtil::LineLoggingQtCategory::LoggingType)
