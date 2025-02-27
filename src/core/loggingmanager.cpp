/*
    SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loggingmanager.h"

LoggingManager::LoggingManager(QObject *parent)
    : QObject{parent}
    , mCustomCategoryModel(new CustomLoggingCategoryModel(this))
    , mQtKdeCategoryModel(new KDEApplicationLoggingCategoryModel(this))
    , mCategoryTypeModel(new CategoryTypeModel(this))
{
    mLoggings.readQtLoggingFile();
    updateLoggingCategories();
}

LoggingManager &LoggingManager::self()
{
    static LoggingManager c;
    return c;
}

LoggingManager::~LoggingManager() = default;

CustomLoggingCategoryModel *LoggingManager::customCategoryModel() const
{
    return mCustomCategoryModel;
}

KDEApplicationLoggingCategoryModel *LoggingManager::qtKdeCategoryModel() const
{
    return mQtKdeCategoryModel;
}

CategoryTypeModel *LoggingManager::categoryTypeModel() const
{
    return mCategoryTypeModel;
}

QString LoggingManager::environmentrules() const
{
    return mLoggings.environmentrules();
}

bool LoggingManager::foundOverrideRule() const
{
    return mLoggings.foundOverrideRule();
}

void LoggingManager::updateLoggingCategories()
{
    const LoggingCategory::List customCategories = mLoggings.customCategories();
    const LoggingCategory::List qtKdeCategories = mLoggings.qtKdeCategories();
    mCustomCategoryModel->setLoggingCategories(customCategories);
    mQtKdeCategoryModel->setLoggingCategories(qtKdeCategories);
}

KDebugSettingsLoadingCategories LoggingManager::loggings() const
{
    return mLoggings;
}

void LoggingManager::readCategoriesFiles(const QString &path)
{
    mLoggings.readCategoriesFiles(path);
}

KdeLoggingCategory::List LoggingManager::categoriesList() const
{
    return mLoggings.categoriesList();
}

void LoggingManager::readQtLoggingFile()
{
    mLoggings.readQtLoggingFile();
}

#include "moc_loggingmanager.cpp"
