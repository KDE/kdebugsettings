/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "categorytypecombobox.h"
#include "model/categorytypemodel.h"
#include "model/categorytypeproxymodel.h"
#include <KLocalizedString>

CategoryTypeComboBox::CategoryTypeComboBox(bool customType, QWidget *parent)
    : QComboBox(parent)
    , mCategoryTypeModel(new CategoryTypeModel(this))
{
    auto proxy = new CategoryTypeProxyModel(this);
    proxy->setObjectName(QStringLiteral("proxy"));
    mCategoryTypeModel->setObjectName(QStringLiteral("mCategoryTypeModel"));
    proxy->setSourceModel(mCategoryTypeModel);
    proxy->setShowOffType(!customType);
    setModel(proxy);
}

CategoryTypeComboBox::~CategoryTypeComboBox() = default;

void CategoryTypeComboBox::restoreToDefault()
{
    setType(mDefaultCategories);
}

void CategoryTypeComboBox::setType(LoggingCategory::LoggingType type)
{
    const int pos = findData(QVariant::fromValue(type), CategoryTypeModel::LoggingCategoryTypeRole);
    if (pos != -1) {
        setCurrentIndex(pos);
    } else {
        // Default;
        setCurrentIndex(0);
    }
}

LoggingCategory::LoggingType CategoryTypeComboBox::type() const
{
    return currentData(CategoryTypeModel::LoggingCategoryTypeRole).value<LoggingCategory::LoggingType>();
}

bool CategoryTypeComboBox::loggingCategoryIsNotDefault() const
{
    return type() != mDefaultCategories;
}

void CategoryTypeComboBox::setDefaultCategories(LoggingCategory::LoggingType defaultCategories)
{
    mDefaultCategories = defaultCategories;
}

LoggingCategory::LoggingType CategoryTypeComboBox::defaultCategories() const
{
    return mDefaultCategories;
}
