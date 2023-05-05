/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdeapplicationdebugsettingpagetest.h"
#include "kdeapplicationdebugsettingpage.h"
#include "kdeapplicationtreelistwidget.h"
#include <KTreeWidgetSearchLine>
#include <QHeaderView>
#include <QPushButton>
#include <QTest>
#include <QVBoxLayout>

KDEApplicationDebugSettingPageTest::KDEApplicationDebugSettingPageTest(QObject *parent)
    : QObject(parent)
{
}

KDEApplicationDebugSettingPageTest::~KDEApplicationDebugSettingPageTest() = default;

void KDEApplicationDebugSettingPageTest::shouldHaveDefaultValue()
{
    KDEApplicationDebugSettingPage page;
    auto listWidget = page.findChild<KDEApplicationTreeListWidget *>(QStringLiteral("listwidget"));
    QVERIFY(listWidget);
    QVERIFY(!listWidget->rootIsDecorated());
    QVERIFY(listWidget->header()->isHidden());
    QVERIFY(listWidget->isColumnHidden(2));
    QCOMPARE(listWidget->columnCount(), 4);
    QVERIFY(listWidget->uniformRowHeights());

    auto mainLayout = page.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

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