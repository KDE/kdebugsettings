/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "loggingcategorymodel.h"

LoggingCategoryModel::LoggingCategoryModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

LoggingCategoryModel::~LoggingCategoryModel() = default;

int LoggingCategoryModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mLoggingCategories.count();
}

QVariant LoggingCategoryModel::data(const QModelIndex &index, int role) const
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
    case Qt::ToolTipRole:
        return category.generateToolTip();
    case DefaultCategory:
        return category.defaultSeverityType;
    case Qt::DisplayRole:
    case DisplayRule:
        return category.generateDisplayRule();
    case LoggingType:
        return category.loggingType;
    }
    return {};
}

void LoggingCategoryModel::setLoggingCategories(const LoggingCategory::List &list)
{
    beginResetModel();
    mLoggingCategories = list;
    endResetModel();
}

void LoggingCategoryModel::clear()
{
    if (!mLoggingCategories.isEmpty()) {
        beginResetModel();
        mLoggingCategories.clear();
        endResetModel();
    }
}
