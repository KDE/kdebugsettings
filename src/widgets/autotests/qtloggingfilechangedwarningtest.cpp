/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#include "qtloggingfilechangedwarningtest.h"
#include "qtloggingfilechangedwarning.h"
#include <QTest>

QTEST_MAIN(QtLoggingFileChangedWarningTest)

QtLoggingFileChangedWarningTest::QtLoggingFileChangedWarningTest(QObject *parent)
    : QObject{parent}
{
}

void QtLoggingFileChangedWarningTest::shouldHaveDefaultValues()
{
    const QtLoggingFileChangedWarning w;
    QVERIFY(!w.isVisible());
    QVERIFY(w.wordWrap());
}
#include "moc_qtloggingfilechangedwarningtest.cpp"
