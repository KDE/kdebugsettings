/*
    SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef LOADTOOLBUTTONTEST_H
#define LOADTOOLBUTTONTEST_H

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

#endif // LOADTOOLBUTTONTEST_H
