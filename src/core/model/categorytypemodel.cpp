/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "categorytypemodel.h"
#include <KLocalizedString>

CategoryTypeModel::CategoryTypeModel(QObject *parent)
    : QAbstractListModel{parent}
{
    mRoleNames.insert(CategoryTypeNameRole, "display");
    mRoleNames.insert(LoggingCategoryTypeRole, "categoryType");
    fillCategoryTypes();
}

CategoryTypeModel::~CategoryTypeModel() = default;

int CategoryTypeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mCategoryInfoList.count();
}

QVariant CategoryTypeModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mCategoryInfoList.count()) {
        return {};
    }
    const CategoryInfo statusInfo = mCategoryInfoList.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
    case CategoryTypeNameRole:
        return statusInfo.displayText;
    case LoggingCategoryTypeRole:
        return QVariant::fromValue(statusInfo.type);
    }
    return {};
}

void CategoryTypeModel::fillCategoryTypes()
{
    mCategoryInfoList = {
        {i18n("Full Debug"), LoggingCategory::All},
        {i18n("Info"), LoggingCategory::Info},
        {i18n("Warning"), LoggingCategory::Warning},
        {i18n("Critical"), LoggingCategory::Critical},
        {i18n("Off"), LoggingCategory::Off},
    };
}

QHash<int, QByteArray> CategoryTypeModel::roleNames() const
{
    return mRoleNames;
}
