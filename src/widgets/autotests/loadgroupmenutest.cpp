/*
    SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loadgroupmenutest.h"
#include "loadgroupmenu.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(LoadGroupMenuTest)
LoadGroupMenuTest::LoadGroupMenuTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void LoadGroupMenuTest::shouldHaveDefaultValues()
{
    LoadGroupMenu m;
    QVERIFY(m.isEmpty());
    QVERIFY(!m.isEnabled());
    QVERIFY(!m.title().isEmpty());
    QVERIFY(m.groupNames().isEmpty());
}

#include "moc_loadgroupmenutest.cpp"
