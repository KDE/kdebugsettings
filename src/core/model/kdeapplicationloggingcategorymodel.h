/*
    SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "libkdebugsettingscore_export.h"
#include "loggingcategory.h"
#include <QAbstractListModel>

class LIBKDEBUGSETTINGSCORE_EXPORT KDEApplicationLoggingCategoryModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum CategoryRoles {
        DescriptionRole,
        LoggingTypeRole,
        CategoryRole,
        LoggingTypeStrRole,
        LastColumn = LoggingTypeStrRole,
    };

    explicit KDEApplicationLoggingCategoryModel(QObject *parent = nullptr);
    ~KDEApplicationLoggingCategoryModel() override;

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    // Use only for test apps
    void setLoggingCategories(const LoggingCategory::List &list);

    void clear();

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    void insertCategories(const LoggingCategory::List &categories);

    void removeCategory(const LoggingCategory::List &categories);

    [[nodiscard]] bool addCategory(const LoggingCategory &category);

    [[nodiscard]] LoggingCategory::List loggingCategories() const;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void replaceCategories(const LoggingCategory::List &categories);

    void refreshModel();

private:
    LoggingCategory::List mLoggingCategories;
    QHash<int, QByteArray> mRoleNames;
};
