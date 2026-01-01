/*
    SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "changedebugmodejobtest.h"
using namespace Qt::Literals::StringLiterals;

#include "jobs/changedebugmodejob.h"
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
    job.setDebugMode(u"foo"_s);
    QVERIFY(!job.debugMode().isEmpty());
    QVERIFY(job.loggingCategoriesName().isEmpty());
    QVERIFY(!job.canStart());
    job.setLoggingCategoriesName({u"foo"_s});
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
    job.setDebugMode(u"foo"_s);
    QVERIFY(job.canStart());
}

void ChangeDebugModeJobTest::shouldConvertToLoggingType()
{
    ChangeDebugModeJob job;
    QCOMPARE(job.convertDebugModeToLoggingType(u"bla"_s), LoggingCategory::LoggingType::Undefined);
    QCOMPARE(job.convertDebugModeToLoggingType(QString()), LoggingCategory::LoggingType::Undefined);

    QCOMPARE(job.convertDebugModeToLoggingType(u"Full"_s), LoggingCategory::LoggingType::All);
    QCOMPARE(job.convertDebugModeToLoggingType(u"Info"_s), LoggingCategory::LoggingType::Info);
    QCOMPARE(job.convertDebugModeToLoggingType(u"Warning"_s), LoggingCategory::LoggingType::Warning);
    QCOMPARE(job.convertDebugModeToLoggingType(u"Critical"_s), LoggingCategory::LoggingType::Critical);
    QCOMPARE(job.convertDebugModeToLoggingType(u"Off"_s), LoggingCategory::LoggingType::Off);
}

#include "moc_changedebugmodejobtest.cpp"
