/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#pragma once

#include <QWidget>

class KDEApplicationListViewGui : public QWidget
{
    Q_OBJECT
public:
    explicit KDEApplicationListViewGui(QWidget *parent = nullptr);
    ~KDEApplicationListViewGui() override = default;
};
