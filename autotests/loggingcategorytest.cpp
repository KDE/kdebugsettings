/*
  Copyright (c) 2016-2018 Montel Laurent <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

*/

#include "loggingcategorytest.h"
#include "../src/loggingcategory.h"
#include <QTest>

LoggingCategoryTest::LoggingCategoryTest(QObject *parent)
    : QObject(parent)
{
}

LoggingCategoryTest::~LoggingCategoryTest()
{
}

void LoggingCategoryTest::shouldHaveDefaultValue()
{
    LoggingCategory log;
    QVERIFY(log.enabled);
    QVERIFY(log.description.isEmpty());
    QVERIFY(log.categoryName.isEmpty());
    QCOMPARE(log.loggingType, LoggingCategory::Info);
    QVERIFY(!log.isValid());
}

void LoggingCategoryTest::shouldBeEqual()
{
    LoggingCategory log;
    log.enabled = false;
    log.description = QStringLiteral("foo");
    log.categoryName = QStringLiteral("bla");
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
    QTest::newRow("debug") << QStringLiteral("foo") << LoggingCategory::Debug << QStringLiteral("foo.info=false\nfoo.debug=true\nfoo.warning=true\nfoo.critical=true\n");
    QTest::newRow("info") << QStringLiteral("foo") << LoggingCategory::Info << QStringLiteral("foo.info=true\nfoo.warning=true\nfoo.critical=true\nfoo.debug=false\n");
    QTest::newRow("critical") << QStringLiteral("foo") << LoggingCategory::Critical << QStringLiteral("foo.info=false\nfoo.debug=false\nfoo.warning=false\nfoo.critical=true\n");
    QTest::newRow("warning") << QStringLiteral("foo") << LoggingCategory::Warning << QStringLiteral("foo.info=false\nfoo.debug=false\nfoo.warning=true\nfoo.critical=true\n");
    QTest::newRow("off") << QStringLiteral("foo") << LoggingCategory::Off << QStringLiteral("foo.info=false\nfoo.debug=false\nfoo.warning=false\nfoo.critical=false\n");
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
