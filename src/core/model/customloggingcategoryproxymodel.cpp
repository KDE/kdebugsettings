/*
    SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customloggingcategoryproxymodel.h"
#include "customloggingcategorymodel.h"

CustomLoggingCategoryProxyModel::CustomLoggingCategoryProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

CustomLoggingCategoryProxyModel::~CustomLoggingCategoryProxyModel() = default;

bool CustomLoggingCategoryProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (mFilterText.isEmpty()) {
        return true;
    }
    const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);

    const QString categoryName = sourceIndex.data(CustomLoggingCategoryModel::CategoryNameRole).toString();
    if (sourceIndex.data(CustomLoggingCategoryModel::CategoryNameRole).toString().contains(mFilterText)
        || sourceIndex.data(CustomLoggingCategoryModel::DescriptionRole).toString().contains(mFilterText)
        || sourceIndex.data(CustomLoggingCategoryModel::IdentifierNameRole).toString().contains(mFilterText)
        || sourceIndex.data(CustomLoggingCategoryModel::DisplayRuleRole).toString().contains(mFilterText)) {
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
        mFilterText = newFilterText;
        invalidateFilter();
        Q_EMIT filterTextChanged();
    }
}

#include "moc_customloggingcategoryproxymodel.cpp"
