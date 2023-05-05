/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#pragma once

#include <QWidget>

class CustomDebugListViewGui : public QWidget
{
    Q_OBJECT
public:
    explicit CustomDebugListViewGui(QWidget *parent = nullptr);
    ~CustomDebugListViewGui() override = default;
};
