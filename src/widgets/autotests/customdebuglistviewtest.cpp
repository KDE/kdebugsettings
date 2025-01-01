/*
    SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customdebuglistviewtest.h"
#include "customdebuglistview.h"
#include <QTest>

QTEST_MAIN(CustomDebugListViewTest)

CustomDebugListViewTest::CustomDebugListViewTest(QObject *parent)
    : QObject{parent}
{
}

void CustomDebugListViewTest::shouldHaveDefaultValues()
{
    CustomDebugListView w;
    QCOMPARE(w.contextMenuPolicy(), Qt::CustomContextMenu);
    QCOMPARE(w.selectionMode(), QAbstractItemView::ExtendedSelection);
}

#include "moc_customdebuglistviewtest.cpp"
