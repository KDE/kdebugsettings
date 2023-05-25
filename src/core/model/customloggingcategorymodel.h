/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "libkdebugsettingscore_export.h"
#include "loggingcategory.h"
#include <QAbstractListModel>

class LIBKDEBUGSETTINGSCORE_EXPORT CustomLoggingCategoryModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum CategoryRoles {
        DescriptionRole = Qt::UserRole + 1,
        CategoryNameRole,
        IdentifierNameRole,
        DefaultCategoryRole,
        DisplayRuleRole,
        LoggingTypeRole,
        CategoryRole,
    };

    explicit CustomLoggingCategoryModel(QObject *parent = nullptr);
    ~CustomLoggingCategoryModel() override;

    Q_REQUIRED_RESULT int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_REQUIRED_RESULT int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_REQUIRED_RESULT QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    // Use only for test apps
    void setLoggingCategories(const LoggingCategory::List &list);

    void clear();

    Q_REQUIRED_RESULT QHash<int, QByteArray> roleNames() const override;

    void insertCategories(const LoggingCategory::List &categories);

    void removeCategory(const LoggingCategory::List &categories);

    Q_REQUIRED_RESULT bool addCategory(const LoggingCategory &category);

    Q_REQUIRED_RESULT LoggingCategory::List loggingCategories() const;

private:
    LoggingCategory::List mLoggingCategories;
    QHash<int, QByteArray> mRoleNames;
};
