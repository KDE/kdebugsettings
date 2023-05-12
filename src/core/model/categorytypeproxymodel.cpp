/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "categorytypeproxymodel.h"
#include "categorytypemodel.h"

CategoryTypeProxyModel::CategoryTypeProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

CategoryTypeProxyModel::~CategoryTypeProxyModel() = default;

bool CategoryTypeProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);

    if (!mShowOffType) {
        const LoggingCategory::LoggingType type = sourceIndex.data(CategoryTypeModel::LoggingCategoryTypeRole).value<LoggingCategory::LoggingType>();
        if (type == LoggingCategory::LoggingType::Off) {
            return false;
        }
    }
    return true;
}

bool CategoryTypeProxyModel::showOffType() const
{
    return mShowOffType;
}

void CategoryTypeProxyModel::setShowOffType(bool newShowOffType)
{
    if (mShowOffType != newShowOffType) {
        mShowOffType = newShowOffType;
        Q_EMIT showOffTypeChanged();
    }
}
