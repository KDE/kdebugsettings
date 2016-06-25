/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

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
    : loggingType(Info),
      enabled(true)
{

}

bool LoggingCategory::operator ==(const LoggingCategory &other) const
{
    return (description == other.description) &&
           (logName == other.logName) &&
           (enabled == other.enabled) &&
           (loggingType == other.loggingType);
}

bool LoggingCategory::isValid() const
{
    return !logName.isEmpty();
}

QString LoggingCategory::createCustomRule()
{
    QString str;
    switch (loggingType) {
    case All: {
        str = logName + QLatin1String("=true\n");
        break;
    }
    case Info: {
        str = logName + QStringLiteral(".info=%1\n").arg(enabled ? QStringLiteral("true") : QStringLiteral("false"));
        break;
    }
    case Warning: {
        str = logName + QStringLiteral(".warning=%1\n").arg(enabled ? QStringLiteral("true") : QStringLiteral("false"));
        break;
    }
    case Debug: {
        str = logName + QStringLiteral(".debug=%1\n").arg(enabled ? QStringLiteral("true") : QStringLiteral("false"));
        break;
    }
    case Critical:  {
        str = logName + QStringLiteral(".critical=%1\n").arg(enabled ? QStringLiteral("true") : QStringLiteral("false"));
        break;
    }
    case Undefined:
    case Off: {
        str = QString();
        break;
    }
    }
    return str;

}

QString LoggingCategory::createRule()
{
    QString str;
    switch (loggingType) {
    case Undefined: {
        break;
    }
    case All: {
        str = logName + QLatin1String("=true\n");
        break;
    }
    case Info: {
        str = logName + QLatin1String(".info=true\n");
        str += logName + QLatin1String(".warning=true\n");
        str += logName + QLatin1String(".critical=true\n");
        str += logName + QLatin1String(".debug=false\n");
        break;
    }
    case Warning: {
        str = logName + QLatin1String(".info=false\n");
        str += logName + QLatin1String(".debug=false\n");
        str += logName + QLatin1String(".warning=true\n");
        str += logName + QLatin1String(".critical=true\n");
        break;
    }
    case Debug: {
        str = logName + QLatin1String(".info=false\n");
        str += logName + QLatin1String(".debug=true\n");
        str += logName + QLatin1String(".warning=true\n");
        str += logName + QLatin1String(".critical=true\n");
        break;
    }
    case Critical:  {
        str = logName + QLatin1String(".info=false\n");
        str += logName + QLatin1String(".debug=false\n");
        str += logName + QLatin1String(".warning=false\n");
        str += logName + QLatin1String(".critical=true\n");
        break;
    }
    case Off: {
        str = logName + QLatin1String(".info=false\n");
        str += logName + QLatin1String(".debug=false\n");
        str += logName + QLatin1String(".warning=false\n");
        str += logName + QLatin1String(".critical=false\n");
        break;
    }
    }
    return str;
}
