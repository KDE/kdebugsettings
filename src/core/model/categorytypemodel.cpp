/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "categorytypemodel.h"

CategoryTypeModel::CategoryTypeModel(QObject *parent)
    : QAbstractListModel{parent}
{
    // TODO fill mRoleNames
}

CategoryTypeModel::~CategoryTypeModel() = default;

int CategoryTypeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    // TODO
    return -1;
}

QVariant CategoryTypeModel::data(const QModelIndex &index, int role) const
{
    // TODO
    return {};
}

void CategoryTypeModel::fillCategoryTypes()
{
    // TODO
}

QHash<int, QByteArray> CategoryTypeModel::roleNames() const
{
    return mRoleNames;
}
