/*
    SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

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
