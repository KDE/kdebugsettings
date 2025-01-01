/*
    SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "environmentsettingsrulespagetest.h"
#include "environmentplaintextedit.h"
#include "environmentsettingsrulespage.h"
#include <QTest>
EnvironmentSettingsRulesPageTest::EnvironmentSettingsRulesPageTest(QObject *parent)
    : QObject(parent)
{
}

EnvironmentSettingsRulesPageTest::~EnvironmentSettingsRulesPageTest() = default;

void EnvironmentSettingsRulesPageTest::shouldHaveDefaultValue()
{
    EnvironmentSettingsRulesPage w;

    auto plainText = w.findChild<EnvironmentPlainTextEdit *>(QStringLiteral("richtext"));
    QVERIFY(plainText);
    QVERIFY(plainText->toPlainText().isEmpty());
    QVERIFY(plainText->isReadOnly());
}

void EnvironmentSettingsRulesPageTest::shouldSetRules()
{
    EnvironmentSettingsRulesPage w;
    auto plainText = w.findChild<EnvironmentPlainTextEdit *>(QStringLiteral("richtext"));
    QString rules = QStringLiteral("Rules for qt\ntest");
    w.setRules(rules);
    QVERIFY(plainText->toPlainText().endsWith(rules));
}

QTEST_MAIN(EnvironmentSettingsRulesPageTest)

#include "moc_environmentsettingsrulespagetest.cpp"
