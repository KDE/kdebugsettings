/*
  Copyright (c) 2019 Montel Laurent <montel@kde.org>

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

#include "changedebugmodejobtest.h"
#include "changedebugmodejob.h"
#include <QTest>
QTEST_GUILESS_MAIN(ChangeDebugModeJobTest)

ChangeDebugModeJobTest::ChangeDebugModeJobTest(QObject *parent)
    : QObject(parent)
{
}

void ChangeDebugModeJobTest::shouldHaveDefaultValue()
{
    ChangeDebugModeJob job;
    QVERIFY(job.debugMode().isEmpty());
    QVERIFY(job.loggingCategoriesName().isEmpty());
    QVERIFY(!job.canStart());
    QVERIFY(!job.withoutArguments());
}

void ChangeDebugModeJobTest::shouldBeAbleToStart()
{
    ChangeDebugModeJob job;
    job.setDebugMode(QStringLiteral("foo"));
    QVERIFY(!job.debugMode().isEmpty());
    QVERIFY(job.loggingCategoriesName().isEmpty());
    QVERIFY(!job.canStart());
    job.setLoggingCategoriesName({QStringLiteral("foo")});
    QVERIFY(!job.debugMode().isEmpty());
    QVERIFY(!job.loggingCategoriesName().isEmpty());
    QVERIFY(job.canStart());
}

void ChangeDebugModeJobTest::shouldBeAbleToStartWithoutArgument()
{
    ChangeDebugModeJob job;
    QVERIFY(!job.canStart());
    job.setWithoutArguments(true);
    QVERIFY(job.canStart());
    job.setDebugMode(QStringLiteral("foo"));
    QVERIFY(job.canStart());
}

void ChangeDebugModeJobTest::shouldConvertToLoggingType()
{
    ChangeDebugModeJob job;
    QCOMPARE(job.convertDebugModeToLoggingType(QStringLiteral("bla")), LoggingCategory::LoggingType::Undefined);
    QCOMPARE(job.convertDebugModeToLoggingType(QString()), LoggingCategory::LoggingType::Undefined);

    QCOMPARE(job.convertDebugModeToLoggingType(QStringLiteral("Full")), LoggingCategory::LoggingType::All);
    QCOMPARE(job.convertDebugModeToLoggingType(QStringLiteral("Info")), LoggingCategory::LoggingType::Info);
    QCOMPARE(job.convertDebugModeToLoggingType(QStringLiteral("Warning")), LoggingCategory::LoggingType::Warning);
    QCOMPARE(job.convertDebugModeToLoggingType(QStringLiteral("Critical")), LoggingCategory::LoggingType::Critical);
    QCOMPARE(job.convertDebugModeToLoggingType(QStringLiteral("Off")), LoggingCategory::LoggingType::Off);
}
