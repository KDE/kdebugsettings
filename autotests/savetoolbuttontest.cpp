/*
    SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "savetoolbuttontest.h"
#include "savetoolbutton.h"
#include <QTest>
QTEST_MAIN(SaveToolButtonTest)
SaveToolButtonTest::SaveToolButtonTest(QObject *parent)
    : QObject(parent)
{
}

void SaveToolButtonTest::shouldHaveDefaultValues()
{
    SaveToolButton w;
    QVERIFY(w.menu());
    QVERIFY(!w.text().isEmpty());
    QCOMPARE(w.popupMode(), QToolButton::InstantPopup);
}
