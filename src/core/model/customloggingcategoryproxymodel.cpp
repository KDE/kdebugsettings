/*
    SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customloggingcategoryproxymodel.h"
#include "customloggingcategorymodel.h"

CustomLoggingCategoryProxyModel::CustomLoggingCategoryProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

CustomLoggingCategoryProxyModel::~CustomLoggingCategoryProxyModel() = default;

void CustomLoggingCategoryProxyModel::removeCategory(int proxyRow)
{
    if (proxyRow < 0 || proxyRow >= rowCount()) {
        return;
    }

    const QModelIndex proxyIndex = index(proxyRow, 0);
    if (!proxyIndex.isValid()) {
        return;
    }

    const QModelIndex sourceIndex = mapToSource(proxyIndex);
    if (!sourceIndex.isValid() || !sourceModel()) {
        return;
    }
    return static_cast<CustomLoggingCategoryModel *>(sourceModel())->removeCategory(sourceIndex.row());
}

void CustomLoggingCategoryProxyModel::addCategory()
{
    // TODO
}

bool CustomLoggingCategoryProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (mFilterText.isEmpty()) {
        return true;
    }
    const auto *model = sourceModel();
    if (!model) {
        return false;
    }
    const QModelIndex sourceIndex = model->index(source_row, 0, source_parent);
    if (!sourceIndex.isValid()) {
        return false;
    }

    const QString categoryName = sourceIndex.data(CustomLoggingCategoryModel::CategoryNameRole).toString();
    if (categoryName.contains(mFilterText, Qt::CaseInsensitive)
        || sourceIndex.data(CustomLoggingCategoryModel::DescriptionRole).toString().contains(mFilterText, Qt::CaseInsensitive)
        || sourceIndex.data(CustomLoggingCategoryModel::IdentifierNameRole).toString().contains(mFilterText, Qt::CaseInsensitive)
        || sourceIndex.data(CustomLoggingCategoryModel::DisplayRuleRole).toString().contains(mFilterText, Qt::CaseInsensitive)) {
        return true;
    }
    return false;
}

QString CustomLoggingCategoryProxyModel::filterText() const
{
    return mFilterText;
}

void CustomLoggingCategoryProxyModel::setFilterText(const QString &newFilterText)
{
    if (mFilterText != newFilterText) {
        beginFilterChange();
        mFilterText = newFilterText;
        endFilterChange(QSortFilterProxyModel::Direction::Rows);
        Q_EMIT filterTextChanged();
    }
}

#include "moc_customloggingcategoryproxymodel.cpp"
