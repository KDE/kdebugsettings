/*
    SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdeapplicationloggingcategorymodel.h"
#include "kdebugsettingscore_debug.h"
#include "kdebugsettingsutil.h"

namespace
{
constexpr int qmlRole(KDEApplicationLoggingCategoryModel::CategoryRoles role)
{
    return static_cast<int>(Qt::UserRole) + static_cast<int>(role) + 1;
}
}

KDEApplicationLoggingCategoryModel::KDEApplicationLoggingCategoryModel(QObject *parent)
    : QAbstractListModel{parent}
{
    // Expose QML roles in the user-role range to avoid collisions with Qt built-in roles.
    mRoleNames.insert(qmlRole(DescriptionRole), "description");
    mRoleNames.insert(qmlRole(LoggingTypeRole), "loggingType");
    mRoleNames.insert(qmlRole(CategoryRole), "category");
    mRoleNames.insert(qmlRole(LoggingTypeStrRole), "loggingTypeStr");
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
    if (idx < 0 || idx >= mLoggingCategories.count()) {
        qCWarning(KDEBUGSETTINGSCORE_LOG) << "ERROR: out-of-range index" << idx;
        return false;
    }
    LoggingCategory &cat = mLoggingCategories[idx];
    switch (static_cast<CategoryRoles>(modelIndex.column())) {
    case LoggingTypeRole: {
        cat.loggingType = value.value<LoggingCategory::LoggingType>();
        const QModelIndex topLeft = index(modelIndex.row(), LoggingTypeRole);
        const QModelIndex bottomRight = index(modelIndex.row(), LoggingTypeStrRole);
        Q_EMIT dataChanged(topLeft, bottomRight);
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

    // Keep widgets behavior (column-based access through DisplayRole).
    if (role == Qt::DisplayRole) {
        switch (static_cast<CategoryRoles>(index.column())) {
        case DescriptionRole:
            return category.description;
        case LoggingTypeStrRole:
            return KDebugSettingsUtil::convertCategoryTypeToString(category.loggingType);
        case LoggingTypeRole:
            return category.loggingType;
        case CategoryRole:
            return QVariant::fromValue(category);
        }
        return {};
    }

    // QML asks data by role id; use dedicated user-role values.
    switch (role) {
    case qmlRole(DescriptionRole):
        return category.description;
    case qmlRole(LoggingTypeStrRole):
        return KDebugSettingsUtil::convertCategoryTypeToString(category.loggingType);
    case qmlRole(LoggingTypeRole):
        return category.loggingType;
    case qmlRole(CategoryRole):
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
            beginInsertRows(QModelIndex(), mLoggingCategories.count(), mLoggingCategories.count());
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
        beginInsertRows(QModelIndex(), mLoggingCategories.count(), mLoggingCategories.count() + categories.count() - 1);
        mLoggingCategories.append(categories);
        endInsertRows();
    }
}

QHash<int, QByteArray> KDEApplicationLoggingCategoryModel::roleNames() const
{
    return mRoleNames;
}

#include "moc_kdeapplicationloggingcategorymodel.cpp"
