/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdeapplicationtreeviewtest.h"
#include "kdeapplicationtreeview.h"
#include <QTest>

QTEST_MAIN(KDEApplicationTreeViewTest)
KDEApplicationTreeViewTest::KDEApplicationTreeViewTest(QObject *parent)
    : QObject{parent}
{
}

void KDEApplicationTreeViewTest::shouldHaveDefaultValues()
{
    KDEApplicationTreeView w;
    // TODO
}
