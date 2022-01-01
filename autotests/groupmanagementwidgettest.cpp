/*
    SPDX-FileCopyrightText: 2020-2022 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "groupmanagementwidgettest.h"
#include "groupmanagementwidget.h"
#include <QListWidget>
#include <QTest>
#include <QVBoxLayout>

QTEST_MAIN(GroupManagementWidgetTest)
GroupManagementWidgetTest::GroupManagementWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void GroupManagementWidgetTest::shouldHaveDefaultValues()
{
    GroupManagementWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mListWidget = w.findChild<QListWidget *>(QStringLiteral("mListWidget"));
    QVERIFY(mListWidget);
    QCOMPARE(mListWidget->selectionMode(), QAbstractItemView::MultiSelection);
}
