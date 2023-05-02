/*
    SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "saverulesjob.h"

#include <QFile>
#include <QTextStream>

SaveRulesJob::SaveRulesJob() = default;

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
    // Save Rules
    QTextStream out(&qtlogging);
    out << QLatin1String("[Rules]\n");
    for (const LoggingCategory &cat : std::as_const(mListKde)) {
        out << cat.createRule() + QLatin1Char('\n');
    }
    for (const LoggingCategory &cat : std::as_const(mListCustom)) {
        out << cat.createCustomRule() + QLatin1Char('\n');
    }
    return true;
}

QString SaveRulesJob::fileName() const
{
    return mFileName;
}
