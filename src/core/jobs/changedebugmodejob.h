/*
    SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "libkdebugsettingscore_export.h"
#include "loggingcategory.h"
#include <QString>
#include <QStringList>

class LIBKDEBUGSETTINGSCORE_EXPORT ChangeDebugModeJob
{
public:
    ChangeDebugModeJob();
    ~ChangeDebugModeJob();

    [[nodiscard]] bool start();

    void setDebugMode(const QString &mode);
    [[nodiscard]] QString debugMode() const;

    [[nodiscard]] QStringList loggingCategoriesName() const;
    void setLoggingCategoriesName(const QStringList &loggingCategoriesName);

    [[nodiscard]] bool canStart() const;
    [[nodiscard]] bool debugModeIsValid(const QString &value) const;
    [[nodiscard]] LoggingCategory::LoggingType convertDebugModeToLoggingType(const QString &value) const;
    void setWithoutArguments(bool b);
    [[nodiscard]] bool withoutArguments() const;

private:
    QString mDebugMode;
    QStringList mLoggingCategoriesName;
    bool mWithoutArguments = false;
};
