/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "configurecustomsettingdialogtest.h"
#include "../src/configurecustomsettingdialog.h"
#include "../src/configurecustomsettingwidget.h"
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTest>
ConfigureCustomSettingDialogTest::ConfigureCustomSettingDialogTest(QObject *parent)
    : QObject(parent)
{
}

ConfigureCustomSettingDialogTest::~ConfigureCustomSettingDialogTest()
{
}

void ConfigureCustomSettingDialogTest::shouldHaveDefaultValue()
{
    ConfigureCustomSettingDialog dlg;
    auto buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);
    QVERIFY(!buttonBox->button(QDialogButtonBox::Ok)->isEnabled());
    auto widget = dlg.findChild<ConfigureCustomSettingWidget *>(QStringLiteral("customsettingwidget"));
    QVERIFY(widget);
}

QTEST_MAIN(ConfigureCustomSettingDialogTest)
