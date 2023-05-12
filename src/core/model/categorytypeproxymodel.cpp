/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "categorytypeproxymodel.h"

CategoryTypeProxyModel::CategoryTypeProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

CategoryTypeProxyModel::~CategoryTypeProxyModel() = default;
