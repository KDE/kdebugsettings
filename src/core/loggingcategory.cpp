/*
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loggingcategory.h"

#include "kdebugsettingsutil.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
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
    const QString enableState = enabled ? u"=true\n"_s : u"=false\n"_s;
    switch (loggingType) {
    case All:
        str = categoryName + enableState;
        break;
    case Info:
        str = categoryName + u".info"_s + enableState;
        break;
    case Warning:
        str = categoryName + u".warning"_s + enableState;
        break;
    case Debug:
        str = categoryName + u".debug"_s + enableState;
        break;
    case Critical:
        str = categoryName + u".critical"_s + enableState;
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
        str = categoryName + u"=true\n"_s;
        break;
    case Info:
        str = categoryName + u".info=true\n"_s;
        str += categoryName + u".warning=true\n"_s;
        str += categoryName + u".critical=true\n"_s;
        str += categoryName + u".debug=false\n"_s;
        break;
    case Warning:
        str = categoryName + u".info=false\n"_s;
        str += categoryName + u".debug=false\n"_s;
        str += categoryName + u".warning=true\n"_s;
        str += categoryName + u".critical=true\n"_s;
        break;
    case Debug:
        str = categoryName + u".info=false\n"_s;
        str += categoryName + u".debug=true\n"_s;
        str += categoryName + u".warning=true\n"_s;
        str += categoryName + u".critical=true\n"_s;
        break;
    case Critical:
        str = categoryName + u".info=false\n"_s;
        str += categoryName + u".debug=false\n"_s;
        str += categoryName + u".warning=false\n"_s;
        str += categoryName + u".critical=true\n"_s;
        break;
    case Off:
        str = categoryName + u".info=false\n"_s;
        str += categoryName + u".debug=false\n"_s;
        str += categoryName + u".warning=false\n"_s;
        str += categoryName + u".critical=false\n"_s;
        break;
    }
    return str;
}

QDebug operator<<(QDebug d, const LoggingCategory &cat)
{
    d.space() << "customcategories cat: " << cat.description;
    d.space() << "logname: " << cat.categoryName;
    d.space() << "enabled: " << cat.enabled;
    d.space() << "type: " << cat.loggingType;
    d.space() << "identifier: " << cat.identifierName;
    d.space() << "default category: " << cat.defaultSeverityType;
    return d;
}

QString LoggingCategory::generateToolTip() const
{
    QString tooltip = i18n("Category name: %1", categoryName);
    if (!identifierName.isEmpty()) {
        tooltip += u'\n' + i18n("Identifier: %1", identifierName);
    }
    tooltip += u'\n' + i18n("Default Severity: %1", convertCategoryTypeToString(defaultSeverityType));
    return tooltip;
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
