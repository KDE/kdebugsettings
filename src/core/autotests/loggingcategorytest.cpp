/*
    SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loggingcategorytest.h"
using namespace Qt::Literals::StringLiterals;

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
    log.description = u"foo"_s;
    log.categoryName = u"bla"_s;
    log.identifierName = u"blu"_s;
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

    QTest::newRow("all") << u"foo"_s << LoggingCategory::All << u"foo=true\n"_s;
    QTest::newRow("debug") << u"foo"_s << LoggingCategory::Debug << u"foo.info=false\nfoo.debug=true\nfoo.warning=true\nfoo.critical=true\n"_s;
    QTest::newRow("info") << u"foo"_s << LoggingCategory::Info << u"foo.info=true\nfoo.warning=true\nfoo.critical=true\nfoo.debug=false\n"_s;
    QTest::newRow("critical") << u"foo"_s << LoggingCategory::Critical << u"foo.info=false\nfoo.debug=false\nfoo.warning=false\nfoo.critical=true\n"_s;
    QTest::newRow("warning") << u"foo"_s << LoggingCategory::Warning << u"foo.info=false\nfoo.debug=false\nfoo.warning=true\nfoo.critical=true\n"_s;
    QTest::newRow("off") << u"foo"_s << LoggingCategory::Off << u"foo.info=false\nfoo.debug=false\nfoo.warning=false\nfoo.critical=false\n"_s;
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
