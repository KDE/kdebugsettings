/*
    SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "configurecustomsettingwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "configurecustomsettingwidget.h"
#include <KLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QSignalSpy>
#include <QTest>

ConfigureCustomSettingWidgetTest::ConfigureCustomSettingWidgetTest(QObject *parent)
    : QObject(parent)
{
}

ConfigureCustomSettingWidgetTest::~ConfigureCustomSettingWidgetTest() = default;

void ConfigureCustomSettingWidgetTest::shouldHaveDefaultValue()
{
    ConfigureCustomSettingWidget w;
    auto lab = w.findChild<QLabel *>(u"category_label"_s);
    QVERIFY(lab);

    auto categoryLineEdit = w.findChild<KLineEdit *>(u"category_lineedit"_s);
    QVERIFY(categoryLineEdit);
    QVERIFY(categoryLineEdit->trapReturnKey());
    QVERIFY(categoryLineEdit->isClearButtonEnabled());

    auto enableCategory = w.findChild<QCheckBox *>(u"enable_category"_s);
    QVERIFY(enableCategory);

    lab = w.findChild<QLabel *>(u"categorytype_label"_s);
    QVERIFY(lab);
    auto categoryType = w.findChild<QComboBox *>(u"categorytype_combobox"_s);
    QVERIFY(categoryType);
    QCOMPARE(categoryType->count(), 4);
}

void ConfigureCustomSettingWidgetTest::shouldRestoreRules_data()
{
    QTest::addColumn<QString>("input");

    QTest::newRow("empty") << QString();
    QTest::newRow("validrule") << u"foo.warning=true"_s;
    QTest::newRow("validrule2") << u"foo=true"_s;
    QTest::newRow("validrule3") << u"foo=false"_s;
    QTest::newRow("validrule3*") << u"*.warning=false"_s;
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
    auto categoryLineEdit = w.findChild<KLineEdit *>(u"category_lineedit"_s);
    QVERIFY(categoryLineEdit);
    QSignalSpy spy(&w, &ConfigureCustomSettingWidget::enableButton);
    categoryLineEdit->setText(u"bla"_s);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toBool(), true);
    categoryLineEdit->clear();
    QCOMPARE(spy.count(), 2);
    QCOMPARE(spy.at(1).at(0).toBool(), false);

    categoryLineEdit->setText(u" "_s);
    QCOMPARE(spy.count(), 3);
    QCOMPARE(spy.at(2).at(0).toBool(), false);
}

QTEST_MAIN(ConfigureCustomSettingWidgetTest)

#include "moc_configurecustomsettingwidgettest.cpp"
