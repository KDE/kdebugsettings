/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "categorytypecomboboxtest.h"
#include "categorytypecombobox.h"
#include <QTest>

CategoryTypeComboBoxTest::CategoryTypeComboBoxTest(QObject *parent)
    : QObject(parent)
{
}

CategoryTypeComboBoxTest::~CategoryTypeComboBoxTest() = default;

void CategoryTypeComboBoxTest::shouldHaveDefaultValue()
{
    CategoryTypeComboBox w(true);
    QCOMPARE(w.count(), 4);

    CategoryTypeComboBox w2(false);
    QCOMPARE(w2.count(), 5);

    auto proxy = w.model();
    QCOMPARE(proxy->objectName(), QStringLiteral("proxy"));
}

void CategoryTypeComboBoxTest::shouldSetType_data()
{
    QTest::addColumn<LoggingCategory::LoggingType>("input");

    QTest::newRow("all") << LoggingCategory::All;
    QTest::newRow("info") << LoggingCategory::Info;
    QTest::newRow("warning") << LoggingCategory::Warning;
    QTest::newRow("critical") << LoggingCategory::Critical;
    QTest::newRow("off") << LoggingCategory::Off;
}

void CategoryTypeComboBoxTest::shouldSetType()
{
    QFETCH(LoggingCategory::LoggingType, input);
    CategoryTypeComboBox w(false);
    w.setType(input);
    QCOMPARE(w.type(), input);
}

void CategoryTypeComboBoxTest::shouldVerifyItNotDefault()
{
    CategoryTypeComboBox w(true);
    w.setType(LoggingCategory::All);
    QVERIFY(w.loggingCategoryIsNotDefault());

    w.setType(LoggingCategory::Info);
    QVERIFY(!w.loggingCategoryIsNotDefault());

    w.setType(LoggingCategory::Warning);
    QVERIFY(w.loggingCategoryIsNotDefault());

    w.setType(LoggingCategory::Debug);
    QVERIFY(w.loggingCategoryIsNotDefault());

    w.setType(LoggingCategory::Critical);
    QVERIFY(w.loggingCategoryIsNotDefault());
}

void CategoryTypeComboBoxTest::shouldChangeDefaultCategory()
{
    CategoryTypeComboBox w(true);
    w.setDefaultCategories(LoggingCategory::All);
    w.setType(LoggingCategory::All);
    QVERIFY(!w.loggingCategoryIsNotDefault());

    w.setDefaultCategories(LoggingCategory::Critical);
    w.setType(LoggingCategory::Critical);
    QVERIFY(!w.loggingCategoryIsNotDefault());

    w.setType(LoggingCategory::Debug);
    QVERIFY(w.loggingCategoryIsNotDefault());
}

void CategoryTypeComboBoxTest::shouldVerifyThatDefaultCategoryIsCorrect()
{
    CategoryTypeComboBox w(true);
    w.setDefaultCategories(LoggingCategory::All);
    QCOMPARE(w.defaultCategories(), LoggingCategory::All);

    w.setDefaultCategories(LoggingCategory::Critical);
    QCOMPARE(w.defaultCategories(), LoggingCategory::Critical);

    w.setDefaultCategories(LoggingCategory::Debug);
    QCOMPARE(w.defaultCategories(), LoggingCategory::Debug);
}

QTEST_MAIN(CategoryTypeComboBoxTest)
