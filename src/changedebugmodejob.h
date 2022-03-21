/*
    SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "libkdebugsettings_export.h"
#include "loggingcategory.h"
#include <QString>
#include <QStringList>

class LIBKDEBUGSETTINGS_EXPORT ChangeDebugModeJob
{
public:
    ChangeDebugModeJob();
    ~ChangeDebugModeJob();

    Q_REQUIRED_RESULT bool start();

    void setDebugMode(const QString &mode);
    Q_REQUIRED_RESULT QString debugMode() const;

    Q_REQUIRED_RESULT QStringList loggingCategoriesName() const;
    void setLoggingCategoriesName(const QStringList &loggingCategoriesName);

    Q_REQUIRED_RESULT bool canStart() const;
    Q_REQUIRED_RESULT bool debugModeIsValid(const QString &value) const;
    Q_REQUIRED_RESULT LoggingCategory::LoggingType convertDebugModeToLoggingType(const QString &value);
    void setWithoutArguments(bool b);
    Q_REQUIRED_RESULT bool withoutArguments() const;

private:
    QString mDebugMode;
    QStringList mLoggingCategoriesName;
    bool mWithoutArguments = false;
};
