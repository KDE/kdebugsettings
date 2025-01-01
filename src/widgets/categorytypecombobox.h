/*
    SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "libkdebugsettings_export.h"
#include "loggingcategory.h"
#include <QComboBox>
class LIBKDEBUGSETTINGS_EXPORT CategoryTypeComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit CategoryTypeComboBox(bool customType, QWidget *parent = nullptr);
    ~CategoryTypeComboBox() override;

    [[nodiscard]] LoggingCategory::LoggingType type() const;
    void setType(LoggingCategory::LoggingType type);
    [[nodiscard]] bool loggingCategoryIsNotDefault() const;
    void setDefaultCategories(LoggingCategory::LoggingType defaultCategories);
    [[nodiscard]] LoggingCategory::LoggingType defaultCategories() const;

    void restoreToDefault();

private:
    LoggingCategory::LoggingType mDefaultCategories = LoggingCategory::Info;
};
