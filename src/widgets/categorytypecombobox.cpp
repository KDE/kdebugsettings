/*
    SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "categorytypecombobox.h"
using namespace Qt::Literals::StringLiterals;

#include "loggingmanager.h"
#include "model/categorytypemodel.h"
#include "model/categorytypeproxymodel.h"
#include <KLocalizedString>

CategoryTypeComboBox::CategoryTypeComboBox(bool customType, QWidget *parent)
    : QComboBox(parent)
{
    auto proxy = new CategoryTypeProxyModel(this);
    proxy->setObjectName("proxy"_L1);
    proxy->setSourceModel(LoggingManager::self().categoryTypeModel());
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

#include "moc_categorytypecombobox.cpp"
