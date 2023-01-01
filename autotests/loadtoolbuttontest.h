/*
    SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class LoadToolButtonTest : public QObject
{
    Q_OBJECT
public:
    explicit LoadToolButtonTest(QObject *parent = nullptr);
    ~LoadToolButtonTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
