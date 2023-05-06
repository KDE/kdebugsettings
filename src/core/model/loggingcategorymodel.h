/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "libkdebugsettingscore_export.h"
#include "loggingcategory.h"
#include <QAbstractListModel>

class LIBKDEBUGSETTINGSCORE_EXPORT LoggingCategoryModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum CategoryRoles {
        Description = Qt::UserRole + 1,
        CategoryName,
        IdentifierName,
        DefaultCategory,
        DisplayRule,
        LoggingType,
    };

    explicit LoggingCategoryModel(QObject *parent = nullptr);
    ~LoggingCategoryModel() override;

    Q_REQUIRED_RESULT int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_REQUIRED_RESULT QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setLoggingCategories(const LoggingCategory::List &list);

    void clear();

private:
    LoggingCategory::List mLoggingCategories;
};