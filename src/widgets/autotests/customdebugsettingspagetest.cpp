/*
    SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "customdebugsettingspagetest.h"
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

    auto mCustomDebugListView = page.findChild<CustomDebugListView *>(QStringLiteral("mCustomDebugListView"));
    QVERIFY(mCustomDebugListView);

    auto mSearchLineEdit = page.findChild<QLineEdit *>(QStringLiteral("mSearchLineEdit"));
    QVERIFY(mSearchLineEdit);
    QVERIFY(!mSearchLineEdit->placeholderText().isEmpty());

    auto addButton = page.findChild<QPushButton *>(QStringLiteral("add_rule"));
    QVERIFY(addButton);
    QVERIFY(addButton->isEnabled());

    auto editButton = page.findChild<QPushButton *>(QStringLiteral("edit_rule"));
    QVERIFY(editButton);
    QVERIFY(!editButton->isEnabled());

    auto removeButton = page.findChild<QPushButton *>(QStringLiteral("remove_rule"));
    QVERIFY(removeButton);
    QVERIFY(!removeButton->isEnabled());
}

QTEST_MAIN(CustomDebugSettingsPageTest)

#include "moc_customdebugsettingspagetest.cpp"
