/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customdebugmodel.h"

CustomDebugModel::CustomDebugModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

CustomDebugModel::~CustomDebugModel() = default;
