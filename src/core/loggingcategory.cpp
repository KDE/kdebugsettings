/*
    SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loggingcategory.h"
#include "kdebugsettingsutil.h"
#include <KLocalizedString>

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

QString LoggingCategory::generateDisplayRule() const
{
    return KDebugSettingsUtil::generateDisplayRule(categoryName, enabled, loggingType);
}

QString LoggingCategory::createRule() const
{
    QString str;
    switch (loggingType) {
    case Undefined:
        break;
    case All:
        str = categoryName + QLatin1StringView("=true\n");
        break;
    case Info:
        str = categoryName + QLatin1StringView(".info=true\n");
        str += categoryName + QLatin1StringView(".warning=true\n");
        str += categoryName + QLatin1StringView(".critical=true\n");
        str += categoryName + QLatin1StringView(".debug=false\n");
        break;
    case Warning:
        str = categoryName + QLatin1StringView(".info=false\n");
        str += categoryName + QLatin1StringView(".debug=false\n");
        str += categoryName + QLatin1StringView(".warning=true\n");
        str += categoryName + QLatin1StringView(".critical=true\n");
        break;
    case Debug:
        str = categoryName + QLatin1StringView(".info=false\n");
        str += categoryName + QLatin1StringView(".debug=true\n");
        str += categoryName + QLatin1StringView(".warning=true\n");
        str += categoryName + QLatin1StringView(".critical=true\n");
        break;
    case Critical:
        str = categoryName + QLatin1StringView(".info=false\n");
        str += categoryName + QLatin1StringView(".debug=false\n");
        str += categoryName + QLatin1StringView(".warning=false\n");
        str += categoryName + QLatin1StringView(".critical=true\n");
        break;
    case Off:
        str = categoryName + QLatin1StringView(".info=false\n");
        str += categoryName + QLatin1StringView(".debug=false\n");
        str += categoryName + QLatin1StringView(".warning=false\n");
        str += categoryName + QLatin1StringView(".critical=false\n");
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

QString LoggingCategory::generateToolTip() const
{
    QString toopTip = i18n("Category name: %1", categoryName);
    if (!identifierName.isEmpty()) {
        toopTip += QLatin1Char('\n') + i18n("Identifier: %1", identifierName);
    }
    toopTip += QLatin1Char('\n') + i18n("Default Severity: %1", convertCategoryTypeToString(defaultSeverityType));
    return toopTip;
}

QString LoggingCategory::convertCategoryTypeToString(LoggingCategory::LoggingType type) const
{
    QString str;
    switch (type) {
    case LoggingCategory::All:
        str = i18n("All Debug Messages");
        break;
    case LoggingCategory::Info:
        str = i18n("Info Messages");
        break;
    case LoggingCategory::Warning:
        str = i18n("Warning Messages");
        break;
    case LoggingCategory::Debug:
        str = i18n("Debug Messages");
        break;
    case LoggingCategory::Critical:
        str = i18n("Critical Messages");
        break;
    case LoggingCategory::Off:
        str = i18n("No Debug Messages");
        break;
    case LoggingCategory::Undefined:
        str = i18n("Undefined");
        break;
    }
    return str;
}
