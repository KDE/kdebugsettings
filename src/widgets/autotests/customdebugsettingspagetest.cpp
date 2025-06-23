/*
    SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "customdebugsettingspagetest.h"
using namespace Qt::Literals::StringLiterals;

#include "customdebuglistview.h"
#include "customdebugsettingspage.h"
#include <QLineEdit>
#include <QPushButton>
#include <QTest>

CustomDebugSettingsPageTest::CustomDebugSettingsPageTest(QObject *parent)
    : QObject(parent)
{
}

CustomDebugSettingsPageTest::~CustomDebugSettingsPageTest() = default;

void CustomDebugSettingsPageTest::shouldHaveDefaultValue()
{
    CustomDebugSettingsPage page;

    auto mCustomDebugListView = page.findChild<CustomDebugListView *>(u"mCustomDebugListView"_s);
    QVERIFY(mCustomDebugListView);

    auto mSearchLineEdit = page.findChild<QLineEdit *>(u"mSearchLineEdit"_s);
    QVERIFY(mSearchLineEdit);
    QVERIFY(!mSearchLineEdit->placeholderText().isEmpty());

    auto addButton = page.findChild<QPushButton *>(u"add_rule"_s);
    QVERIFY(addButton);
    QVERIFY(addButton->isEnabled());

    auto editButton = page.findChild<QPushButton *>(u"edit_rule"_s);
    QVERIFY(editButton);
    QVERIFY(!editButton->isEnabled());

    auto removeButton = page.findChild<QPushButton *>(u"remove_rule"_s);
    QVERIFY(removeButton);
    QVERIFY(!removeButton->isEnabled());
}

QTEST_MAIN(CustomDebugSettingsPageTest)

#include "moc_customdebugsettingspagetest.cpp"
