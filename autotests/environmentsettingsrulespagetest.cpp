/*
    SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "environmentsettingsrulespagetest.h"
#include "../src/environmentsettingsrulespage.h"
#include "../src/environmentplaintextedit.h"
#include <QLabel>
#include <QTest>
EnvironmentSettingsRulesPageTest::EnvironmentSettingsRulesPageTest(QObject *parent)
    : QObject(parent)
{
}

EnvironmentSettingsRulesPageTest::~EnvironmentSettingsRulesPageTest()
{
}

void EnvironmentSettingsRulesPageTest::shouldHaveDefaultValue()
{
    EnvironmentSettingsRulesPage w;

    auto lab = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(lab);
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
