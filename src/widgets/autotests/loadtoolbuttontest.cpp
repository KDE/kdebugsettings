/*
    SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loadtoolbuttontest.h"
#include "loadtoolbutton.h"
#include <QTest>
QTEST_MAIN(LoadToolButtonTest)
LoadToolButtonTest::LoadToolButtonTest(QObject *parent)
    : QObject(parent)
{
}

void LoadToolButtonTest::shouldHaveDefaultValues()
{
    LoadToolButton w;
    QVERIFY(w.menu());
    QVERIFY(!w.text().isEmpty());
    QCOMPARE(w.popupMode(), QToolButton::InstantPopup);
}

#include "moc_loadtoolbuttontest.cpp"
