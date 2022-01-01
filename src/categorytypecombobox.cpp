/*
    SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "categorytypecombobox.h"

#include <KLocalizedString>

CategoryTypeComboBox::CategoryTypeComboBox(bool customType, QWidget *parent)
    : QComboBox(parent)
{
    addItem(i18n("Full Debug"), QVariant::fromValue(LoggingCategory::All));
    addItem(i18n("Info"), QVariant::fromValue(LoggingCategory::Info));
    addItem(i18n("Warning"), QVariant::fromValue(LoggingCategory::Warning));
    addItem(i18n("Critical"), QVariant::fromValue(LoggingCategory::Critical));
    if (!customType) {
        addItem(i18n("Off"), QVariant::fromValue(LoggingCategory::Off));
    }
}

CategoryTypeComboBox::~CategoryTypeComboBox() = default;

void CategoryTypeComboBox::restoreToDefault()
{
    setType(mDefaultCategories);
}

void CategoryTypeComboBox::setType(LoggingCategory::LoggingType type)
{
    const int pos = findData(QVariant::fromValue(type));
    if (pos != -1) {
        setCurrentIndex(pos);
    } else {
        // Default;
        setCurrentIndex(0);
    }
}

LoggingCategory::LoggingType CategoryTypeComboBox::type() const
{
    return currentData().value<LoggingCategory::LoggingType>();
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
