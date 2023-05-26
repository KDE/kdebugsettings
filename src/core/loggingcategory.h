/*
    SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#pragma once

#include "libkdebugsettingscore_export.h"
#include <QDebug>
#include <QString>
#include <QVector>

struct LIBKDEBUGSETTINGSCORE_EXPORT LoggingCategory {
    enum LoggingType : char {
        All = 0,
        Info,
        Warning,
        Debug,
        Critical,
        Off,
        Undefined,
    };

    LoggingCategory();
    explicit LoggingCategory(const QString &description, const QString &logName, LoggingType loggingType, const QString &identifier, bool enabled)
        : description(description)
        , categoryName(logName)
        , identifierName(identifier)
        , loggingType(loggingType)
        , enabled(enabled)
    {
    }

    using List = QVector<LoggingCategory>;
    Q_REQUIRED_RESULT bool operator==(const LoggingCategory &other) const;
    Q_REQUIRED_RESULT bool isValid() const;

    Q_REQUIRED_RESULT QString createRule() const;
    Q_REQUIRED_RESULT QString createCustomRule() const;
    Q_REQUIRED_RESULT QString generateToolTip() const;
    Q_REQUIRED_RESULT QString generateDisplayRule() const;

    QString description;
    QString categoryName;
    QString identifierName;
    LoggingType loggingType = Info;
    LoggingType defaultSeverityType = Info;
    bool enabled = true;

private:
    Q_REQUIRED_RESULT QString convertCategoryTypeToString(LoggingCategory::LoggingType type) const;
};
LIBKDEBUGSETTINGSCORE_EXPORT QDebug operator<<(QDebug debug, const LoggingCategory &cat);

Q_DECLARE_TYPEINFO(LoggingCategory, Q_MOVABLE_TYPE);
Q_DECLARE_METATYPE(LoggingCategory)
Q_DECLARE_METATYPE(LoggingCategory::LoggingType)
