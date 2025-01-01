/*
    SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdeapplicationloggingcategorymodel.h"
#include "kdebugsettingscore_debug.h"
#include "kdebugsettingsutil.h"

KDEApplicationLoggingCategoryModel::KDEApplicationLoggingCategoryModel(QObject *parent)
    : QAbstractListModel{parent}
{
    mRoleNames.insert(DescriptionRole, "description");
    mRoleNames.insert(LoggingTypeRole, "loggingType");
}

KDEApplicationLoggingCategoryModel::~KDEApplicationLoggingCategoryModel() = default;

int KDEApplicationLoggingCategoryModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mLoggingCategories.count();
}

int KDEApplicationLoggingCategoryModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    constexpr int nbCol = static_cast<int>(KDEApplicationLoggingCategoryModel::LastColumn) + 1;
    return nbCol;
}

Qt::ItemFlags KDEApplicationLoggingCategoryModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    if (static_cast<CategoryRoles>(index.column()) == LoggingTypeStrRole) {
        return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
    }
    return QAbstractItemModel::flags(index);
}

void KDEApplicationLoggingCategoryModel::replaceCategories(const LoggingCategory::List &categories)
{
    beginResetModel();
    for (const auto &category : categories) {
        for (int i = 0; i < mLoggingCategories.count(); ++i) {
            if (mLoggingCategories.at(i).categoryName == category.categoryName) {
                mLoggingCategories.replace(i, category);
                break;
            }
        }
    }
    endResetModel();
}

void KDEApplicationLoggingCategoryModel::refreshModel()
{
    beginResetModel();
    endResetModel();
}

bool KDEApplicationLoggingCategoryModel::setData(const QModelIndex &modelIndex, const QVariant &value, int role)
{
    if (!modelIndex.isValid()) {
        qCWarning(KDEBUGSETTINGSCORE_LOG) << "ERROR: invalid index";
        return false;
    }
    if (role != Qt::EditRole) {
        return false;
    }
    const int idx = modelIndex.row();
    LoggingCategory &cat = mLoggingCategories[idx];
    switch (static_cast<CategoryRoles>(modelIndex.column())) {
    case LoggingTypeRole: {
        cat.loggingType = value.value<LoggingCategory::LoggingType>();
        const QModelIndex newIndex = index(modelIndex.row(), LoggingTypeRole);
        Q_EMIT dataChanged(newIndex, newIndex);
        return true;
    }
    default:
        break;
    }
    return false;
}

QVariant KDEApplicationLoggingCategoryModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mLoggingCategories.count()) {
        return {};
    }
    const LoggingCategory &category = mLoggingCategories.at(index.row());
    if (role == Qt::ToolTipRole) {
        return category.generateToolTip();
    }
    if (role != Qt::DisplayRole) {
        return {};
    }

    switch (static_cast<CategoryRoles>(index.column())) {
    case DescriptionRole: {
        return category.description;
    }
    case LoggingTypeStrRole:
        return KDebugSettingsUtil::convertCategoryTypeToString(category.loggingType);
    case LoggingTypeRole:
        return category.loggingType;
    case CategoryRole:
        return QVariant::fromValue(category);
    }
    return {};
}

void KDEApplicationLoggingCategoryModel::setLoggingCategories(const LoggingCategory::List &list)
{
    beginResetModel();
    mLoggingCategories = list;
    endResetModel();
}

void KDEApplicationLoggingCategoryModel::clear()
{
    if (!mLoggingCategories.isEmpty()) {
        beginResetModel();
        mLoggingCategories.clear();
        endResetModel();
    }
}

void KDEApplicationLoggingCategoryModel::removeCategory(const LoggingCategory::List &categories)
{
    beginResetModel();
    for (int j = 0; j < categories.count(); ++j) {
        for (int i = 0; i < mLoggingCategories.count(); ++i) {
            if (mLoggingCategories.at(i) == categories.at(j)) {
                mLoggingCategories.removeAt(i);
                break;
            }
        }
    }
    endResetModel();
}

bool KDEApplicationLoggingCategoryModel::addCategory(const LoggingCategory &category)
{
    bool found = false;
    if (category.isValid()) {
        auto it = std::find_if(mLoggingCategories.cbegin(), mLoggingCategories.cend(), [category](const LoggingCategory &cat) {
            return cat == category;
        });
        if (it == mLoggingCategories.cend()) {
            beginInsertRows(QModelIndex(), mLoggingCategories.count() - 1, mLoggingCategories.count());
            mLoggingCategories.append(category);
            endInsertRows();
        } else {
            found = true;
        }
    }
    return found;
}

LoggingCategory::List KDEApplicationLoggingCategoryModel::loggingCategories() const
{
    return mLoggingCategories;
}

void KDEApplicationLoggingCategoryModel::insertCategories(const LoggingCategory::List &categories)
{
    if (!categories.isEmpty()) {
        beginInsertRows(QModelIndex(), mLoggingCategories.count() - 1, mLoggingCategories.count() + categories.count() - 1);
        mLoggingCategories.append(categories);
        endInsertRows();
    }
}

QHash<int, QByteArray> KDEApplicationLoggingCategoryModel::roleNames() const
{
    return mRoleNames;
}

#include "moc_kdeapplicationloggingcategorymodel.cpp"
