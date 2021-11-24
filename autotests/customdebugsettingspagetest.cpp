/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "customdebugsettingspagetest.h"
#include "customdebugsettingspage.h"
#include <KListWidgetSearchLine>
#include <QLabel>
#include <QListWidget>
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

    auto lab = page.findChild<QLabel *>(QStringLiteral("custom_label"));
    QVERIFY(lab);

    auto listWidget = page.findChild<QListWidget *>(QStringLiteral("custom_listwidget"));
    QVERIFY(listWidget);
    QCOMPARE(listWidget->selectionMode(), QAbstractItemView::ExtendedSelection);
    QCOMPARE(listWidget->count(), 0);
    QCOMPARE(listWidget->contextMenuPolicy(), Qt::CustomContextMenu);

    auto searchLine = page.findChild<KListWidgetSearchLine *>(QStringLiteral("searchline"));
    QVERIFY(searchLine);
    QVERIFY(!searchLine->placeholderText().isEmpty());
    QCOMPARE(searchLine->listWidget(), listWidget);

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
