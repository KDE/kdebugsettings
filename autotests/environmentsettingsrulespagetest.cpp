/*
  Copyright (c) 2015 Montel Laurent <montel@kde.org>

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

#include "environmentsettingsrulespagetest.h"
#include "../src/environmentsettingsrulespage.h"
#include <QLabel>
#include <QPlainTextEdit>
#include <qtest.h>
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

    QLabel *lab = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(lab);
    QPlainTextEdit *plainText = w.findChild<QPlainTextEdit *>(QStringLiteral("plaintext"));
    QVERIFY(plainText);
    QVERIFY(plainText->toPlainText().isEmpty());
}

void EnvironmentSettingsRulesPageTest::shouldSetRules()
{
    EnvironmentSettingsRulesPage w;
    QPlainTextEdit *plainText = w.findChild<QPlainTextEdit *>(QStringLiteral("plaintext"));
    QString rules = QStringLiteral("Rules for qt\ntest");
    w.setRules(rules);
    QCOMPARE(plainText->toPlainText(), rules);
}

QTEST_MAIN(EnvironmentSettingsRulesPageTest)
