/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdeapplicationloggingcategoryproxymodel.h"
#include "kdeapplicationloggingcategorymodel.h"

KDEApplicationLoggingCategoryProxyModel::KDEApplicationLoggingCategoryProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

KDEApplicationLoggingCategoryProxyModel::~KDEApplicationLoggingCategoryProxyModel() = default;

bool KDEApplicationLoggingCategoryProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (mFilterText.isEmpty()) {
        return true;
    }
    const QModelIndex sourceIndex = sourceModel()->index(source_row, KDEApplicationLoggingCategoryModel::CategoryRole, source_parent);
    const auto category = sourceIndex.data().value<LoggingCategory>();
    if (category.description.contains(mFilterText) || category.categoryName.contains(mFilterText) || category.identifierName.contains(mFilterText)) {
        return true;
    }
    return false;
}

QString KDEApplicationLoggingCategoryProxyModel::filterText() const
{
    return mFilterText;
}

void KDEApplicationLoggingCategoryProxyModel::setFilterText(const QString &newFilterText)
{
    if (mFilterText != newFilterText) {
        mFilterText = newFilterText;
        invalidateFilter();
        Q_EMIT filterTextChanged();
    }
}
