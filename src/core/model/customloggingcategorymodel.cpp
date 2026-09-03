/*
    SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customloggingcategorymodel.h"
#include "kdebugsettingscore_debug.h"

#include <QMultiHash>

CustomLoggingCategoryModel::CustomLoggingCategoryModel(QObject *parent)
    : QAbstractListModel{parent}
{
    mRoleNames.insert(Qt::DisplayRole, "display");
    mRoleNames.insert(DescriptionRole, "description");
    mRoleNames.insert(CategoryNameRole, "categoryName");
    mRoleNames.insert(IdentifierNameRole, "identifierName");
    mRoleNames.insert(DefaultCategoryRole, "defaultCategory");
    mRoleNames.insert(DisplayRuleRole, "displayRule");
    mRoleNames.insert(LoggingTypeRole, "loggingType");
    mRoleNames.insert(EnabledRole, "enabled");
}

CustomLoggingCategoryModel::~CustomLoggingCategoryModel() = default;

int CustomLoggingCategoryModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mLoggingCategories.count();
}

int CustomLoggingCategoryModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

bool CustomLoggingCategoryModel::setData(const QModelIndex &modelIndex, const QVariant &value, int role)
{
    if (!modelIndex.isValid()) {
        qCWarning(KDEBUGSETTINGSCORE_LOG) << "ERROR: invalid index";
        return false;
    }
    const int idx = modelIndex.row();
    if (idx < 0 || idx >= mLoggingCategories.count()) {
        qCWarning(KDEBUGSETTINGSCORE_LOG) << "ERROR: out-of-range index" << idx;
        return false;
    }
    switch (role) {
    case CategoryRole: {
        LoggingCategory &cat = mLoggingCategories[idx];
        cat = value.value<LoggingCategory>();
        const QModelIndex newIndex = index(modelIndex.row(), 0);
        Q_EMIT dataChanged(newIndex, newIndex);
        return true;
    }
    default:
        break;
    }
    return false;
}

void CustomLoggingCategoryModel::updateCategory(int row, const QString &categoryName, bool enabled, LoggingCategory::LoggingType type)
{
    if (row < 0 || row >= mLoggingCategories.count()) {
        qCWarning(KDEBUGSETTINGSCORE_LOG) << "invalid row: " << row;
        return;
    }
    LoggingCategory &cat = mLoggingCategories[row];
    cat.categoryName = categoryName;
    cat.enabled = enabled;
    cat.loggingType = type;
    const QModelIndex modelIndex = index(row, 0);
    Q_EMIT dataChanged(modelIndex, modelIndex);
}

QVariant CustomLoggingCategoryModel::data(const QModelIndex &index, int role) const
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
    case EnabledRole:
        return category.enabled;
    case CategoryRole:
        return QVariant::fromValue(category);
    }
    return {};
}

void CustomLoggingCategoryModel::setLoggingCategories(const LoggingCategory::List &list)
{
    beginResetModel();
    mLoggingCategories = list;
    endResetModel();
}

void CustomLoggingCategoryModel::clear()
{
    if (!mLoggingCategories.isEmpty()) {
        beginResetModel();
        mLoggingCategories.clear();
        endResetModel();
    }
}

void CustomLoggingCategoryModel::removeCategory(int row)
{
    if (row < 0 || row >= mLoggingCategories.count()) {
        qCWarning(KDEBUGSETTINGSCORE_LOG) << "invalid row: " << row;
        return;
    }
    beginRemoveRows(QModelIndex(), row, row);
    mLoggingCategories.removeAt(row);
    endRemoveRows();
}

void CustomLoggingCategoryModel::removeCategory(const LoggingCategory::List &categories)
{
    if (categories.isEmpty() || mLoggingCategories.isEmpty()) {
        return;
    }
    // Index the rows by category name: without it each entry of "categories"
    // rescans the whole list, and each removeAt() shifts the tail again.
    QMultiHash<QString, int> rowsByName;
    rowsByName.reserve(mLoggingCategories.count());
    for (int i = 0, total = mLoggingCategories.count(); i < total; ++i) {
        rowsByName.insert(mLoggingCategories.at(i).categoryName, i);
    }

    // Collect the rows to drop first, so that nothing is signaled when none of
    // the categories is present, and so that the removal can be reported as
    // rowsRemoved() instead of a full reset which would lose the selection.
    QList<bool> rowsToRemove(mLoggingCategories.count(), false);
    bool foundOne = false;
    for (const LoggingCategory &category : categories) {
        const auto candidates = rowsByName.equal_range(category.categoryName);
        for (auto it = candidates.first; it != candidates.second; ++it) {
            const int row = it.value();
            if (!rowsToRemove.at(row) && mLoggingCategories.at(row) == category) {
                rowsToRemove[row] = true;
                foundOne = true;
                break;
            }
        }
    }
    if (!foundOne) {
        return;
    }

    // Remove by descending contiguous ranges so the rows already reported keep
    // their index while the next range is computed.
    for (int end = rowsToRemove.count() - 1; end >= 0; --end) {
        if (!rowsToRemove.at(end)) {
            continue;
        }
        int start = end;
        while (start > 0 && rowsToRemove.at(start - 1)) {
            --start;
        }
        beginRemoveRows(QModelIndex(), start, end);
        mLoggingCategories.remove(start, end - start + 1);
        endRemoveRows();
        end = start;
    }
}

void CustomLoggingCategoryModel::addCategory(const QString &categoryName, bool enabled, LoggingCategory::LoggingType type)
{
    LoggingCategory category;
    category.categoryName = categoryName;
    category.enabled = enabled;
    category.loggingType = type;
    if (!addCategory(category)) {
        qCDebug(KDEBUGSETTINGSCORE_LOG) << " categorie already exist";
    }
}

bool CustomLoggingCategoryModel::addCategory(const LoggingCategory &category)
{
    bool added = false;
    if (category.isValid()) {
        auto it = std::find_if(mLoggingCategories.cbegin(), mLoggingCategories.cend(), [&category](const LoggingCategory &cat) {
            return cat == category;
        });
        if (it == mLoggingCategories.cend()) {
            beginInsertRows(QModelIndex(), mLoggingCategories.count(), mLoggingCategories.count());
            mLoggingCategories.append(category);
            endInsertRows();
            added = true;
        }
    }
    return added;
}

LoggingCategory::List CustomLoggingCategoryModel::loggingCategories() const
{
    return mLoggingCategories;
}

void CustomLoggingCategoryModel::insertCategories(const LoggingCategory::List &categories)
{
    if (!categories.isEmpty()) {
        beginInsertRows(QModelIndex(), mLoggingCategories.count(), mLoggingCategories.count() + categories.count() - 1);
        mLoggingCategories.append(categories);
        endInsertRows();
    }
}

QHash<int, QByteArray> CustomLoggingCategoryModel::roleNames() const
{
    return mRoleNames;
}

void CustomLoggingCategoryModel::refreshModel()
{
    beginResetModel();
    endResetModel();
}

#include "moc_customloggingcategorymodel.cpp"
