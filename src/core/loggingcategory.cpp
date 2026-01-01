/*
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loggingcategory.h"
using namespace Qt::Literals::StringLiterals;

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
        str = categoryName + (enabled ? u"=true\n"_s : u"=false\n"_s);
        break;
    case Info:
        str = categoryName + u".info=%1\n"_s.arg(enabled ? u"true"_s : u"false"_s);
        break;
    case Warning:
        str = categoryName + u".warning=%1\n"_s.arg(enabled ? u"true"_s : u"false"_s);
        break;
    case Debug:
        str = categoryName + u".debug=%1\n"_s.arg(enabled ? u"true"_s : u"false"_s);
        break;
    case Critical:
        str = categoryName + u".critical=%1\n"_s.arg(enabled ? u"true"_s : u"false"_s);
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
        str = categoryName + "=true\n"_L1;
        break;
    case Info:
        str = categoryName + ".info=true\n"_L1;
        str += categoryName + ".warning=true\n"_L1;
        str += categoryName + ".critical=true\n"_L1;
        str += categoryName + ".debug=false\n"_L1;
        break;
    case Warning:
        str = categoryName + ".info=false\n"_L1;
        str += categoryName + ".debug=false\n"_L1;
        str += categoryName + ".warning=true\n"_L1;
        str += categoryName + ".critical=true\n"_L1;
        break;
    case Debug:
        str = categoryName + ".info=false\n"_L1;
        str += categoryName + ".debug=true\n"_L1;
        str += categoryName + ".warning=true\n"_L1;
        str += categoryName + ".critical=true\n"_L1;
        break;
    case Critical:
        str = categoryName + ".info=false\n"_L1;
        str += categoryName + ".debug=false\n"_L1;
        str += categoryName + ".warning=false\n"_L1;
        str += categoryName + ".critical=true\n"_L1;
        break;
    case Off:
        str = categoryName + ".info=false\n"_L1;
        str += categoryName + ".debug=false\n"_L1;
        str += categoryName + ".warning=false\n"_L1;
        str += categoryName + ".critical=false\n"_L1;
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
