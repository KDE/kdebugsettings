/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QAbstractListModel>

class CustomDebugModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CustomDebugModel(QObject *parent = nullptr);
    ~CustomDebugModel() override;
};
