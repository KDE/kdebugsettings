/*
    SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "categorytypemodel.h"
#include "kdebugsettingsutil.h"
#include <KLocalizedString>

CategoryTypeModel::CategoryTypeModel(QObject *parent)
    : QAbstractListModel{parent}
{
    mRoleNames.insert(CategoryTypeNameRole, "display");
    mRoleNames.insert(LoggingCategoryTypeRole, "categoryType");
    fillCategoryTypes();
}

CategoryTypeModel::~CategoryTypeModel() = default;

int CategoryTypeModel::indexOfCategory(LoggingCategory::LoggingType type) const
{
    for (int i = 0; i < mCategoryInfoList.count(); ++i) {
        if (mCategoryInfoList.at(i).type == type) {
            return i;
        }
    }
    return -1;
}

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
        return statusInfo.type;
    }
    return {};
}

CategoryTypeModel::CategoryInfo CategoryTypeModel::createCategoryInfo(LoggingCategory::LoggingType type)
{
    const CategoryTypeModel::CategoryInfo cat(KDebugSettingsUtil::convertCategoryTypeToString(type), type);
    return cat;
}

void CategoryTypeModel::fillCategoryTypes()
{
    mCategoryInfoList = {
        createCategoryInfo(LoggingCategory::All),
        createCategoryInfo(LoggingCategory::Info),
        createCategoryInfo(LoggingCategory::Warning),
        createCategoryInfo(LoggingCategory::Critical),
        createCategoryInfo(LoggingCategory::Off),
    };
}

QHash<int, QByteArray> CategoryTypeModel::roleNames() const
{
    return mRoleNames;
}

#include "moc_categorytypemodel.cpp"
