/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#pragma once
#include "libkdebugsettingscore_export.h"
#include <QObject>
class LoggingCategoryModel;
class LIBKDEBUGSETTINGSCORE_EXPORT LoggingManager : public QObject
{
    Q_OBJECT
public:
    explicit LoggingManager(QObject *parent = nullptr);
    ~LoggingManager() override;

private:
    LoggingCategoryModel *mCustomCategoryModel = nullptr;
};
