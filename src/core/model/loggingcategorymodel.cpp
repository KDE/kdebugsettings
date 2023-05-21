/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "loggingcategorymodel.h"
#include "kdebugsettingscore_debug.h"

LoggingCategoryModel::LoggingCategoryModel(QObject *parent)
    : QAbstractListModel{parent}
{
    mRoleNames.insert(Qt::DisplayRole, "display");
    mRoleNames.insert(DescriptionRole, "description");
    mRoleNames.insert(CategoryNameRole, "categoryName");
    mRoleNames.insert(IdentifierNameRole, "identifierName");
    mRoleNames.insert(DefaultCategoryRole, "defaultCategory");
    mRoleNames.insert(DisplayRuleRole, "displayRule");
    mRoleNames.insert(LoggingTypeRole, "loggingType");
}

LoggingCategoryModel::~LoggingCategoryModel() = default;

int LoggingCategoryModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mLoggingCategories.count();
}

bool LoggingCategoryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        qCWarning(KDEBUGSETTINGSCORE_LOG) << "ERROR: invalid index";
        return false;
    }
    // TODO
    return false;
}

QVariant LoggingCategoryModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mLoggingCategories.count()) {
        return {};
    }

    const LoggingCategory &category = mLoggingCategories.at(index.row());
    switch (role) {
    case DescriptionRole:
        return category.description;
    case CategoryNameRole:
        return category.categoryName;
    case IdentifierNameRole:
        return category.identifierName;
    case Qt::ToolTipRole:
        return category.generateToolTip();
    case DefaultCategoryRole:
        return category.defaultSeverityType;
    case Qt::DisplayRole:
    case DisplayRuleRole:
        return category.generateDisplayRule();
    case LoggingTypeRole:
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

void LoggingCategoryModel::removeCategory(const QString &identifier)
{
    for (int i = 0; i < mLoggingCategories.count(); ++i) {
        if (mLoggingCategories.at(i).identifierName == identifier) {
            beginRemoveRows(QModelIndex(), i, i);
            mLoggingCategories.removeAt(i);
            endRemoveRows();
            break;
        }
    }
}

void LoggingCategoryModel::insertCategories(const LoggingCategory::List &categories)
{
    if (!categories.isEmpty()) {
        beginInsertRows(QModelIndex(), mLoggingCategories.count() - 1, mLoggingCategories.count() + categories.count() - 1);
        mLoggingCategories.append(categories);
        endInsertRows();
    }
}

QHash<int, QByteArray> LoggingCategoryModel::roleNames() const
{
    return mRoleNames;
}
