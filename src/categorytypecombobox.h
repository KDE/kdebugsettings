/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef CATEGORYTYPECOMBOBOX_H
#define CATEGORYTYPECOMBOBOX_H

#include "libkdebugsettings_export.h"
#include "loggingcategory.h"
#include <QComboBox>

class LIBKDEBUGSETTINGS_EXPORT CategoryTypeComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit CategoryTypeComboBox(bool customType, QWidget *parent = nullptr);
    ~CategoryTypeComboBox() override;

    Q_REQUIRED_RESULT LoggingCategory::LoggingType type() const;
    void setType(LoggingCategory::LoggingType type);
    Q_REQUIRED_RESULT bool loggingCategoryIsNotDefault() const;
    void setDefaultCategories(LoggingCategory::LoggingType defaultCategories);
    Q_REQUIRED_RESULT LoggingCategory::LoggingType defaultCategories() const;

    void restoreToDefault();

private:
    LoggingCategory::LoggingType mDefaultCategories = LoggingCategory::Info;
};

#endif // CATEGORYTYPECOMBOBOX_H
