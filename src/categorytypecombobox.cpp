/*
  Copyright (c) 2015-2018 Montel Laurent <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

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

CategoryTypeComboBox::~CategoryTypeComboBox()
{
}

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
        //Default;
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

void CategoryTypeComboBox::setDefaultCategories(const LoggingCategory::LoggingType &defaultCategories)
{
    mDefaultCategories = defaultCategories;
}

LoggingCategory::LoggingType CategoryTypeComboBox::defaultCategories() const
{
    return mDefaultCategories;
}
