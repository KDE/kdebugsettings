/*
    SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loggingcategorytest.h"
#include "loggingcategory.h"
#include <QTest>

LoggingCategoryTest::LoggingCategoryTest(QObject *parent)
    : QObject(parent)
{
}

LoggingCategoryTest::~LoggingCategoryTest() = default;

void LoggingCategoryTest::shouldHaveDefaultValue()
{
    LoggingCategory log;
    QVERIFY(log.enabled);
    QVERIFY(log.description.isEmpty());
    QVERIFY(log.categoryName.isEmpty());
    QVERIFY(log.identifierName.isEmpty());
    QCOMPARE(log.loggingType, LoggingCategory::Info);
    QVERIFY(!log.isValid());
}

void LoggingCategoryTest::shouldBeEqual()
{
    LoggingCategory log;
    log.enabled = false;
    log.description = QStringLiteral("foo");
    log.categoryName = QStringLiteral("bla");
    log.identifierName = QStringLiteral("blu");
    log.loggingType = LoggingCategory::All;
    LoggingCategory log2;
    log2 = log;
    QVERIFY(log2 == log);
}

void LoggingCategoryTest::shouldCreateRules_data()
{
    QTest::addColumn<QString>("logname");
    QTest::addColumn<LoggingCategory::LoggingType>("loggingType");
    QTest::addColumn<QString>("result");

    QTest::newRow("all") << QStringLiteral("foo") << LoggingCategory::All << QStringLiteral("foo=true\n");
    QTest::newRow("debug") << QStringLiteral("foo") << LoggingCategory::Debug
                           << QStringLiteral("foo.info=false\nfoo.debug=true\nfoo.warning=true\nfoo.critical=true\n");
    QTest::newRow("info") << QStringLiteral("foo") << LoggingCategory::Info
                          << QStringLiteral("foo.info=true\nfoo.warning=true\nfoo.critical=true\nfoo.debug=false\n");
    QTest::newRow("critical") << QStringLiteral("foo") << LoggingCategory::Critical
                              << QStringLiteral("foo.info=false\nfoo.debug=false\nfoo.warning=false\nfoo.critical=true\n");
    QTest::newRow("warning") << QStringLiteral("foo") << LoggingCategory::Warning
                             << QStringLiteral("foo.info=false\nfoo.debug=false\nfoo.warning=true\nfoo.critical=true\n");
    QTest::newRow("off") << QStringLiteral("foo") << LoggingCategory::Off
                         << QStringLiteral("foo.info=false\nfoo.debug=false\nfoo.warning=false\nfoo.critical=false\n");
}

void LoggingCategoryTest::shouldCreateRules()
{
    QFETCH(QString, logname);
    QFETCH(LoggingCategory::LoggingType, loggingType);
    QFETCH(QString, result);
    LoggingCategory log;
    log.categoryName = logname;
    log.loggingType = loggingType;
    QCOMPARE(log.createRule(), result);
    QVERIFY(log.isValid());
}

QTEST_MAIN(LoggingCategoryTest)

#include "moc_loggingcategorytest.cpp"
