/*
  Copyright (c) 2016-2018 Montel Laurent <montel@kde.org>

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

#include "loggingcategory.h"

LoggingCategory::LoggingCategory()
{
}

bool LoggingCategory::operator ==(const LoggingCategory &other) const
{
    return (description == other.description)
           && (categoryName == other.categoryName)
           && (enabled == other.enabled)
           && (loggingType == other.loggingType)
           && (defaultCategoryType == other.defaultCategoryType)
           && (identifierName == other.identifierName);
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
    d << "default category: " << cat.defaultCategoryType;
    return d;
}
