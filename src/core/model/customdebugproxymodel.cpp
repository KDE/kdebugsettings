/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customdebugproxymodel.h"
#include "loggingcategorymodel.h"

CustomDebugProxyModel::CustomDebugProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

CustomDebugProxyModel::~CustomDebugProxyModel() = default;

bool CustomDebugProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (mFilterText.isEmpty()) {
        return true;
    }
    const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);

    const QString categoryName = sourceIndex.data(LoggingCategoryModel::CategoryNameRole).toString();
    if (sourceIndex.data(LoggingCategoryModel::CategoryNameRole).toString().contains(mFilterText)
        || sourceIndex.data(LoggingCategoryModel::DescriptionRole).toString().contains(mFilterText)
        || sourceIndex.data(LoggingCategoryModel::IdentifierNameRole).toString().contains(mFilterText)) {
        return true;
    }
    return false;
}

QString CustomDebugProxyModel::filterText() const
{
    return mFilterText;
}

void CustomDebugProxyModel::setFilterText(const QString &newFilterText)
{
    if (mFilterText != newFilterText) {
        mFilterText = newFilterText;
        invalidateFilter();
        Q_EMIT filterTextChanged();
    }
}
