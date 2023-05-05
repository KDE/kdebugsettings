/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customdebugmodel.h"

CustomDebugModel::CustomDebugModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

CustomDebugModel::~CustomDebugModel() = default;

int CustomDebugModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mLoggingCategories.count();
}

QVariant CustomDebugModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mLoggingCategories.count()) {
        return {};
    }
    const LoggingCategory &category = mLoggingCategories.at(index.row());
    switch (role) {
    case Description:
        return category.description;
    case CategoryName:
        return category.categoryName;
    case IdentifierName:
        return category.identifierName;
    case Qt::ToolTip:
        return category.generateToolTip();
#if 0
    case Qt::DisplayRole:
        return category.description;
#endif
    case DefaultCategory:
        return category.defaultSeverityType;

    case Qt::DisplayRole:
    case DisplayRule: {
        return category.generateDisplayRule();
    }
    case LoggingType:
        return category.loggingType;
    }
    return {};
}

void CustomDebugModel::setLoggingCategories(const LoggingCategory::List &list)
{
    beginResetModel();
    mLoggingCategories = list;
    endResetModel();
}

void CustomDebugModel::clear()
{
    if (!mLoggingCategories.isEmpty()) {
        beginResetModel();
        mLoggingCategories.clear();
        endResetModel();
    }
}
