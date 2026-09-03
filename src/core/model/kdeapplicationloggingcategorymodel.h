/*
    SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

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
        GeneratedToolTipRole,
        LoggingTypeStrRole,
        LastColumn = LoggingTypeStrRole,
    };

    // The enum above is used as a column index by the widgets views, so the QML
    // roles are exposed in the user-role range to avoid colliding with the Qt
    // built-in roles. Use it whenever a role id is expected (roleNames(), data()
    // or the dataChanged() roles) and never the raw enum value.
    [[nodiscard]] static constexpr int qmlRole(CategoryRoles role)
    {
        return static_cast<int>(Qt::UserRole) + static_cast<int>(role) + 1;
    }

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

    [[nodiscard]] LoggingCategory::List loggingCategories() const;

    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

    void replaceCategories(const LoggingCategory::List &categories);

    void refreshModel();

private:
    LoggingCategory::List mLoggingCategories;
    QHash<int, QByteArray> mRoleNames;
};
