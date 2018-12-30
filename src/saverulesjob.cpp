/*
  Copyright (c) 2017-2019 Montel Laurent <montel@kde.org>

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

#include "saverulesjob.h"

#include <QFile>
#include <QTextStream>

SaveRulesJob::SaveRulesJob()
{
}

void SaveRulesJob::setListKde(const LoggingCategory::List &listKde)
{
    mListKde = listKde;
}

void SaveRulesJob::setListCustom(const LoggingCategory::List &listCustom)
{
    mListCustom = listCustom;
}

void SaveRulesJob::setFileName(const QString &fileName)
{
    mFileName = fileName;
}

bool SaveRulesJob::start()
{
    QFile qtlogging(mFileName);
    if (!qtlogging.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        return false;
    }
    //Save Rules
    QTextStream out(&qtlogging);
    out << QLatin1String("[Rules]\n");
    for (LoggingCategory cat : mListKde) {
        out << cat.createRule() + QLatin1Char('\n');
    }
    for (LoggingCategory cat : mListCustom) {
        out << cat.createCustomRule() + QLatin1Char('\n');
    }
    return true;
}
