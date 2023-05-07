/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loggingmanager.h"
#include "model/loggingcategorymodel.h"

LoggingManager::LoggingManager(QObject *parent)
    : QObject{parent}
    , mCustomCategoryModel(new LoggingCategoryModel(this))
{
}

LoggingManager::~LoggingManager() = default;

LoggingCategoryModel *LoggingManager::customCategoryModel() const
{
    return mCustomCategoryModel;
}
