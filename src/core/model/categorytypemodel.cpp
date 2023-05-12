/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "categorytypemodel.h"

CategoryTypeModel::CategoryTypeModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

CategoryTypeModel::~CategoryTypeModel() = default;
