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
    const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
#if 0
    const QString categoryName = sourceIndex.data(KDEApplicationLoggingCategoryModel::DescriptionRole).toString();
    if (sourceIndex.data(KDEApplicationLoggingCategoryModel::DescriptionRole).toString().contains(mFilterText)
        || sourceIndex.data(CustomLoggingCategoryModel::IdentifierNameRole).toString().contains(mFilterText)) {
        return true;
    }
#endif
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
