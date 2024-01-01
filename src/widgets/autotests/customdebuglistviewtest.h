/*
    SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class CustomDebugListViewTest : public QObject
{
    Q_OBJECT
public:
    explicit CustomDebugListViewTest(QObject *parent = nullptr);
    ~CustomDebugListViewTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
