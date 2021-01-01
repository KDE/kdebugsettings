/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "categorywarningtest.h"
#include "../src/categorywarning.h"
#include <QTest>

CategoryWarningTest::CategoryWarningTest(QObject *parent)
    : QObject(parent)
{
}

CategoryWarningTest::~CategoryWarningTest()
{
}

void CategoryWarningTest::shouldHaveDefaultValue()
{
    CategoryWarning w;
    QVERIFY(!w.isVisible());
    QVERIFY(w.wordWrap());
}

QTEST_MAIN(CategoryWarningTest)
