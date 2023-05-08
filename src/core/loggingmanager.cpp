/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loggingmanager.h"

LoggingManager::LoggingManager(QObject *parent)
    : QObject{parent}
    , mCustomCategoryModel(new LoggingCategoryModel(this))
    , mQtKdeCategoryModel(new LoggingCategoryModel(this))
{
    mLoggings.readQtLoggingFile();
}

LoggingManager::~LoggingManager() = default;

LoggingCategoryModel *LoggingManager::customCategoryModel() const
{
    return mCustomCategoryModel;
}

LoggingCategoryModel *LoggingManager::qtKdeCategoryModel() const
{
    return mQtKdeCategoryModel;
}
