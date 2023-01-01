/*
    SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loggingcategory.h"

LoggingCategory::LoggingCategory() = default;

bool LoggingCategory::operator==(const LoggingCategory &other) const
{
    return (description == other.description) && (categoryName == other.categoryName) && (enabled == other.enabled) && (loggingType == other.loggingType)
        && (defaultSeverityType == other.defaultSeverityType) && (identifierName == other.identifierName);
}

bool LoggingCategory::isValid() const
{
    return !categoryName.isEmpty() && (loggingType != Undefined);
}

QString LoggingCategory::createCustomRule() const
{
    QString str;
    switch (loggingType) {
    case All:
        str = categoryName + (enabled ? QStringLiteral("=true\n") : QStringLiteral("=false\n"));
        break;
    case Info:
        str = categoryName + QStringLiteral(".info=%1\n").arg(enabled ? QStringLiteral("true") : QStringLiteral("false"));
        break;
    case Warning:
        str = categoryName + QStringLiteral(".warning=%1\n").arg(enabled ? QStringLiteral("true") : QStringLiteral("false"));
        break;
    case Debug:
        str = categoryName + QStringLiteral(".debug=%1\n").arg(enabled ? QStringLiteral("true") : QStringLiteral("false"));
        break;
    case Critical:
        str = categoryName + QStringLiteral(".critical=%1\n").arg(enabled ? QStringLiteral("true") : QStringLiteral("false"));
        break;
    case Undefined:
    case Off:
        str = QString();
        break;
    }
    return str;
}

QString LoggingCategory::createRule() const
{
    QString str;
    switch (loggingType) {
    case Undefined:
        break;
    case All:
        str = categoryName + QLatin1String("=true\n");
        break;
    case Info:
        str = categoryName + QLatin1String(".info=true\n");
        str += categoryName + QLatin1String(".warning=true\n");
        str += categoryName + QLatin1String(".critical=true\n");
        str += categoryName + QLatin1String(".debug=false\n");
        break;
    case Warning:
        str = categoryName + QLatin1String(".info=false\n");
        str += categoryName + QLatin1String(".debug=false\n");
        str += categoryName + QLatin1String(".warning=true\n");
        str += categoryName + QLatin1String(".critical=true\n");
        break;
    case Debug:
        str = categoryName + QLatin1String(".info=false\n");
        str += categoryName + QLatin1String(".debug=true\n");
        str += categoryName + QLatin1String(".warning=true\n");
        str += categoryName + QLatin1String(".critical=true\n");
        break;
    case Critical:
        str = categoryName + QLatin1String(".info=false\n");
        str += categoryName + QLatin1String(".debug=false\n");
        str += categoryName + QLatin1String(".warning=false\n");
        str += categoryName + QLatin1String(".critical=true\n");
        break;
    case Off:
        str = categoryName + QLatin1String(".info=false\n");
        str += categoryName + QLatin1String(".debug=false\n");
        str += categoryName + QLatin1String(".warning=false\n");
        str += categoryName + QLatin1String(".critical=false\n");
        break;
    }
    return str;
}

QDebug operator<<(QDebug d, const LoggingCategory &cat)
{
    d << "customcategories cat: " << cat.description;
    d << "logname: " << cat.categoryName;
    d << "enabled: " << cat.enabled;
    d << "type: " << cat.loggingType;
    d << "identifier: " << cat.identifierName;
    d << "default category: " << cat.defaultSeverityType;
    return d;
}
