/*
    SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "libkdebugsettingscore_export.h"
#include "loggingcategory.h"
class LIBKDEBUGSETTINGSCORE_EXPORT SaveRulesJob
{
public:
    SaveRulesJob();
    ~SaveRulesJob() = default;

    void setListKde(const LoggingCategory::List &listKde);
    void setListCustom(const LoggingCategory::List &listCustom);

    void setFileName(const QString &fileName);

    [[nodiscard]] bool start();

    [[nodiscard]] QString fileName() const;

private:
    LoggingCategory::List mListKde;
    LoggingCategory::List mListCustom;
    QString mFileName;
};
