/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdeapplicationtreelistwidgettest.h"
#include "kdeapplicationtreelistwidget.h"
#include <QHeaderView>
#include <QTest>

KDEApplicationTreeListWidgetTest::KDEApplicationTreeListWidgetTest(QObject *parent)
    : QObject(parent)
{
}

KDEApplicationTreeListWidgetTest::~KDEApplicationTreeListWidgetTest()
{
}

void KDEApplicationTreeListWidgetTest::shouldHaveDefaultValue()
{
    KDEApplicationTreeListWidget w;
    QCOMPARE(w.topLevelItemCount(), 0);
    QVERIFY(w.header()->isHidden());
    QCOMPARE(w.columnCount(), 4);
}

QTEST_MAIN(KDEApplicationTreeListWidgetTest)
