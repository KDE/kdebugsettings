/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdeapplicationdebugsettingpagetest.h"
#include "../src/kdeapplicationdebugsettingpage.h"
#include "../src/kdeapplicationtreelistwidget.h"
#include <QPushButton>
#include <QHeaderView>
#include <QTest>
#include <KTreeWidgetSearchLine>

KDEApplicationDebugSettingPageTest::KDEApplicationDebugSettingPageTest(QObject *parent)
    : QObject(parent)
{
}

KDEApplicationDebugSettingPageTest::~KDEApplicationDebugSettingPageTest()
{
}

void KDEApplicationDebugSettingPageTest::shouldHaveDefaultValue()
{
    KDEApplicationDebugSettingPage page;
    auto listWidget = page.findChild<KDEApplicationTreeListWidget *>(QStringLiteral("listwidget"));
    QVERIFY(listWidget);
    QVERIFY(!listWidget->rootIsDecorated());
    QVERIFY(listWidget->header()->isHidden());
    QVERIFY(listWidget->isColumnHidden(2));
    QCOMPARE(listWidget->columnCount(), 4);

    auto selectAll = page.findChild<QPushButton *>(QStringLiteral("selectall"));
    QVERIFY(selectAll);
    QVERIFY(selectAll->isEnabled());

    auto deselectAll = page.findChild<QPushButton *>(QStringLiteral("deselectall"));
    QVERIFY(deselectAll);
    QVERIFY(deselectAll->isEnabled());

    auto mTurnOffAllMessages = page.findChild<QPushButton *>(QStringLiteral("deselectallmessage"));
    QVERIFY(mTurnOffAllMessages);
    QVERIFY(mTurnOffAllMessages->isEnabled());

    auto searchLine = page.findChild<KTreeWidgetSearchLine *>(QStringLiteral("searchline"));
    QVERIFY(searchLine);
    QVERIFY(searchLine->text().isEmpty());
}

QTEST_MAIN(KDEApplicationDebugSettingPageTest)
