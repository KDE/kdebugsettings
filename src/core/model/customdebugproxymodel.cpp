/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customdebugproxymodel.h"

CustomDebugProxyModel::CustomDebugProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

CustomDebugProxyModel::~CustomDebugProxyModel() = default;