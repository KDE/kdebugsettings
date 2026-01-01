/*
    SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "saverulesjob.h"
using namespace Qt::Literals::StringLiterals;

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
    out << "[Rules]\n"_L1;

    // Universal custom rules (with a category of "*" and no specific
    // type) are dangerous because they will override all other rules.
    // The user is warned in the GUI, but they are output here first so
    // that they do not override all others.  If the user really does
    // want to create a universal rule that overrides all others then
    // they can set a custom rule "*.*=true" or "*.*=false".
    QStringList listExcludeRules;
    for (const LoggingCategory &cat : std::as_const(mListCustom)) {
        const QString rule = cat.createCustomRule();
        if (rule.startsWith("*="_L1)) {
            out << rule + u'\n';
        } else {
            listExcludeRules << rule + u'\n';
        }
    }

    // Then the configured KDE rules.
    for (const LoggingCategory &cat : std::as_const(mListKde)) {
        out << cat.createRule() + u'\n';
    }

    // Finally the user's custom rules which will not override
    // all others.
    for (const QString &str : std::as_const(listExcludeRules)) {
        out << str;
    }
    return true;
}

QString SaveRulesJob::fileName() const
{
    return mFileName;
}
