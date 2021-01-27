/*
    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#ifndef LOGGINGCATEGORY_H
#define LOGGINGCATEGORY_H

#include "libkdebugsettings_export.h"
#include <QDebug>
#include <QString>
#include <QVector>

struct LIBKDEBUGSETTINGS_EXPORT LoggingCategory {
    enum LoggingType { All = 0, Info, Warning, Debug, Critical, Off, Undefined };

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

    QString description;
    QString categoryName;
    QString identifierName;
    LoggingType loggingType = Info;
    LoggingType defaultSeverityType = Info;
    bool enabled = true;
};
LIBKDEBUGSETTINGS_EXPORT QDebug operator<<(QDebug debug, const LoggingCategory &cat);

Q_DECLARE_TYPEINFO(LoggingCategory, Q_MOVABLE_TYPE);
Q_DECLARE_METATYPE(LoggingCategory)
Q_DECLARE_METATYPE(LoggingCategory::LoggingType)

#endif // LOGGINGCATEGORY_H
