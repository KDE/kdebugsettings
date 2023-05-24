/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdeapplicationlistviewtest.h"
#include "kdeapplicationlistview.h"
#include <QTest>

QTEST_MAIN(KDEApplicationListViewTest)
KDEApplicationListViewTest::KDEApplicationListViewTest(QObject *parent)
    : QObject{parent}
{
}

void KDEApplicationListViewTest::shouldHaveDefaultValues()
{
    KDEApplicationListView w;
    // TODO
}
