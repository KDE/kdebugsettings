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

void LoggingManager::updateLoggingCategories()
{
#if 0
    if (!mLoggings.environmentrules().isEmpty()) {
        mEnvironmentSettingsRulesPage->setRules(mLoggings.environmentrules());
    }
#endif
    const LoggingCategory::List customCategories = mLoggings.customCategories();
    const LoggingCategory::List qtKdeCategories = mLoggings.qtKdeCategories();
    const bool foundOverrideRule = mLoggings.foundOverrideRule();
    mCustomCategoryModel->setLoggingCategories(customCategories);
    mQtKdeCategoryModel->setLoggingCategories(qtKdeCategories);
#if 0
    if (foundOverrideRule) {
        mCategoryWarning->animatedShow();
    }
    mCategoriesList = mLoggings.categoriesList();
#endif
}
