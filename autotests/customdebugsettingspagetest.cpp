/*
  Copyright (c) 2015-2020 Laurent Montel <montel@kde.org>

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

#include "customdebugsettingspagetest.h"
#include "../src/customdebugsettingspage.h"
#include <KListWidgetSearchLine>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QTest>

CustomDebugSettingsPageTest::CustomDebugSettingsPageTest(QObject *parent)
    : QObject(parent)
{
}

CustomDebugSettingsPageTest::~CustomDebugSettingsPageTest()
{
}

void CustomDebugSettingsPageTest::shouldHaveDefaultValue()
{
    CustomDebugSettingsPage page;

    auto *lab = page.findChild<QLabel *>(QStringLiteral("custom_label"));
    QVERIFY(lab);

    auto *listWidget = page.findChild<QListWidget *>(QStringLiteral("custom_listwidget"));
    QVERIFY(listWidget);
    QCOMPARE(listWidget->selectionMode(), QAbstractItemView::MultiSelection);
    QCOMPARE(listWidget->count(), 0);

    auto *searchLine = page.findChild<KListWidgetSearchLine *>(QStringLiteral("searchline"));
    QVERIFY(searchLine);
    QVERIFY(!searchLine->placeholderText().isEmpty());
    QCOMPARE(searchLine->listWidget(), listWidget);

    auto *addButton = page.findChild<QPushButton *>(QStringLiteral("add_rule"));
    QVERIFY(addButton);
    QVERIFY(addButton->isEnabled());

    auto *editButton = page.findChild<QPushButton *>(QStringLiteral("edit_rule"));
    QVERIFY(editButton);
    QVERIFY(!editButton->isEnabled());

    auto *removeButton = page.findChild<QPushButton *>(QStringLiteral("remove_rule"));
    QVERIFY(removeButton);
    QVERIFY(!removeButton->isEnabled());
}

QTEST_MAIN(CustomDebugSettingsPageTest)
