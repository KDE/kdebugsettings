/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "libkdebugsettingscore_export.h"
#include <QAbstractListModel>

class LIBKDEBUGSETTINGSCORE_EXPORT CategoryTypeModel : public QAbstractListModel
{
    Q_OBJECT
public:
    // TODO add more enum
    enum CategoryTypeRoles {
        CategoryTypeNameRole = Qt::UserRole + 1,
    };
    explicit CategoryTypeModel(QObject *parent = nullptr);
    ~CategoryTypeModel() override;

    Q_REQUIRED_RESULT int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_REQUIRED_RESULT QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_REQUIRED_RESULT QHash<int, QByteArray> roleNames() const override;

private:
    void fillCategoryTypes();
    QHash<int, QByteArray> mRoleNames;
};
