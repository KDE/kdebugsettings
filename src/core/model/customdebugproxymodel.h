/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QSortFilterProxyModel>

class CustomDebugProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit CustomDebugProxyModel(QObject *parent = nullptr);
    ~CustomDebugProxyModel() override;
};
