/*
    SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdeapplicationloggingcategoryproxymodel.h"
#include "kdeapplicationloggingcategorymodel.h"

KDEApplicationLoggingCategoryProxyModel::KDEApplicationLoggingCategoryProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

KDEApplicationLoggingCategoryProxyModel::~KDEApplicationLoggingCategoryProxyModel() = default;

bool KDEApplicationLoggingCategoryProxyModel::setCategoryType(int proxyRow, int type)
{
    if (proxyRow < 0 || proxyRow >= rowCount()) {
        return false;
    }

    const QModelIndex proxyIndex = index(proxyRow, KDEApplicationLoggingCategoryModel::LoggingTypeRole);
    if (!proxyIndex.isValid()) {
        return false;
    }

    const QModelIndex sourceIndex = mapToSource(proxyIndex);
    if (!sourceIndex.isValid() || !sourceModel()) {
        return false;
    }

    return sourceModel()->setData(sourceIndex, QVariant::fromValue(static_cast<LoggingCategory::LoggingType>(type)), Qt::EditRole);
}

bool KDEApplicationLoggingCategoryProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (mFilterText.isEmpty()) {
        return true;
    }
    const QModelIndex sourceIndex = sourceModel()->index(source_row, KDEApplicationLoggingCategoryModel::CategoryRole, source_parent);
    const auto category = sourceIndex.data().value<LoggingCategory>();
    if (category.description.contains(mFilterText, Qt::CaseInsensitive) || category.categoryName.contains(mFilterText, Qt::CaseInsensitive)
        || category.identifierName.contains(mFilterText, Qt::CaseInsensitive)) {
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
        beginFilterChange();
        mFilterText = newFilterText;
        endFilterChange(QSortFilterProxyModel::Direction::Rows);
        Q_EMIT filterTextChanged();
    }
}

LoggingCategory::List KDEApplicationLoggingCategoryProxyModel::rules(bool forceSavingAllRules) const
{
    LoggingCategory::List lst;
    for (int i = 0; i < rowCount(); ++i) {
        const QModelIndex newModelIndex = mapToSource(index(i, KDEApplicationLoggingCategoryModel::CategoryRole));
        auto cat = newModelIndex.data().value<LoggingCategory>();
        if (forceSavingAllRules || (cat.loggingType != cat.defaultSeverityType)) {
            cat.enabled = false;
            if (cat.isValid()) {
                lst.append(cat);
            }
        }
    }
    return lst;
}

#include "moc_kdeapplicationloggingcategoryproxymodel.cpp"
