/*
    SPDX-FileCopyrightText: 2017-2022 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "libkdebugsettings_export.h"
#include "loggingcategory.h"
class LIBKDEBUGSETTINGS_EXPORT SaveRulesJob
{
public:
    SaveRulesJob();
    ~SaveRulesJob() = default;

    void setListKde(const LoggingCategory::List &listKde);
    void setListCustom(const LoggingCategory::List &listCustom);

    void setFileName(const QString &fileName);

    Q_REQUIRED_RESULT bool start();

    Q_REQUIRED_RESULT QString fileName() const;

private:
    LoggingCategory::List mListKde;
    LoggingCategory::List mListCustom;
    QString mFileName;
};

