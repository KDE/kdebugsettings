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

#include "configurecustomsettingwidgettest.h"
#include "../src/configurecustomsettingwidget.h"
#include <QComboBox>
#include <QLabel>
#include <KLineEdit>
#include <QSignalSpy>
#include <qcheckbox.h>
#include <qtest.h>

ConfigureCustomSettingWidgetTest::ConfigureCustomSettingWidgetTest(QObject *parent)
    : QObject(parent)
{

}

ConfigureCustomSettingWidgetTest::~ConfigureCustomSettingWidgetTest()
{

}

void ConfigureCustomSettingWidgetTest::shouldHaveDefaultValue()
{
    ConfigureCustomSettingWidget w;
    QLabel *lab = w.findChild<QLabel *>(QStringLiteral("category_label"));
    QVERIFY(lab);

    KLineEdit *categoryLineEdit = w.findChild<KLineEdit *>(QStringLiteral("category_lineedit"));
    QVERIFY(categoryLineEdit);
    QVERIFY(categoryLineEdit->trapReturnKey());

    QCheckBox *enableCategory = w.findChild<QCheckBox *>(QStringLiteral("enable_category"));
    QVERIFY(enableCategory);

    lab = w.findChild<QLabel *>(QStringLiteral("categorytype_label"));
    QVERIFY(lab);
    QComboBox *categoryType = w.findChild<QComboBox *>(QStringLiteral("categorytype_combobox"));
    QVERIFY(categoryType);
    QCOMPARE(categoryType->count(), 4);
}

void ConfigureCustomSettingWidgetTest::shouldRestoreRules_data()
{
    QTest::addColumn<QString>("input");

    QTest::newRow("empty") <<  QString();
    QTest::newRow("validrule") <<  QStringLiteral("foo.warning=true");
    QTest::newRow("validrule2") <<  QStringLiteral("foo=true");
    QTest::newRow("validrule3") <<  QStringLiteral("foo=false");
    QTest::newRow("validrule3*") <<  QStringLiteral("*.debug=false");
}

void ConfigureCustomSettingWidgetTest::shouldRestoreRules()
{
    QFETCH(QString, input);
    ConfigureCustomSettingWidget w;
    w.setRule(input);
    QCOMPARE(input, w.rule());
}

void ConfigureCustomSettingWidgetTest::shouldEmitSignalWhenWeChangeLogName()
{
    ConfigureCustomSettingWidget w;
    KLineEdit *categoryLineEdit = w.findChild<KLineEdit *>(QStringLiteral("category_lineedit"));
    QVERIFY(categoryLineEdit);
    QSignalSpy spy(&w, SIGNAL(enableButton(bool)));
    categoryLineEdit->setText(QStringLiteral("bla"));
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<bool>(), true);
    categoryLineEdit->clear();
    QCOMPARE(spy.count(), 2);
    QCOMPARE(spy.at(1).at(0).value<bool>(), false);

    categoryLineEdit->setText(QStringLiteral(" "));
    QCOMPARE(spy.count(), 3);
    QCOMPARE(spy.at(2).at(0).value<bool>(), false);
}

QTEST_MAIN(ConfigureCustomSettingWidgetTest)
