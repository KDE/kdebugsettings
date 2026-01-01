/*
    SPDX-FileCopyrightText: 2020-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "groupmanagementwidgettest.h"
using namespace Qt::Literals::StringLiterals;

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
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mListWidget = w.findChild<QListWidget *>(u"mListWidget"_s);
    QVERIFY(mListWidget);
    QCOMPARE(mListWidget->selectionMode(), QAbstractItemView::ExtendedSelection);
}

#include "moc_groupmanagementwidgettest.cpp"
