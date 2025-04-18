/*
    SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "categorywarningtest.h"
#include "categorywarning.h"
#include <QTest>

CategoryWarningTest::CategoryWarningTest(QObject *parent)
    : QObject(parent)
{
}

CategoryWarningTest::~CategoryWarningTest() = default;

void CategoryWarningTest::shouldHaveDefaultValue()
{
    CategoryWarning w;
    QVERIFY(!w.isVisible());
    QVERIFY(w.wordWrap());
}

QTEST_MAIN(CategoryWarningTest)

#include "moc_categorywarningtest.cpp"
