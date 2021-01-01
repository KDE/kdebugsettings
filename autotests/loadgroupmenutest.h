/*
    SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef LOADGROUPMENUTEST_H
#define LOADGROUPMENUTEST_H

#include <QObject>

class LoadGroupMenuTest : public QObject
{
    Q_OBJECT
public:
    explicit LoadGroupMenuTest(QObject *parent = nullptr);
    ~LoadGroupMenuTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // LOADGROUPMENUTEST_H
