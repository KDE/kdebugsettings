/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdeapplicationdebugsettingpagetest.h"
#include "kdeapplicationdebugsettingpage.h"
#include "kdeapplicationtreeview.h"
#include <QHeaderView>
#include <QLineEdit>
#include <QPushButton>
#include <QTest>
#include <QVBoxLayout>

QTEST_MAIN(KDEApplicationDebugSettingPageTest)

KDEApplicationDebugSettingPageTest::KDEApplicationDebugSettingPageTest(QObject *parent)
    : QObject(parent)
{
}

KDEApplicationDebugSettingPageTest::~KDEApplicationDebugSettingPageTest() = default;

void KDEApplicationDebugSettingPageTest::shouldHaveDefaultValue()
{
    KDEApplicationDebugSettingPage page;
    auto mKdeApplicationTreeView = page.findChild<KDEApplicationTreeView *>(QStringLiteral("mKdeApplicationTreeView"));
    QVERIFY(mKdeApplicationTreeView);
    QVERIFY(!mKdeApplicationTreeView->rootIsDecorated());
    QVERIFY(mKdeApplicationTreeView->header()->isHidden());
    QVERIFY(mKdeApplicationTreeView->uniformRowHeights());

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

    auto mSearchLineEdit = page.findChild<QLineEdit *>(QStringLiteral("mSearchLineEdit"));
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->text().isEmpty());
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
}
