/*
    SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdeapplicationdebugsettingpagetest.h"
using namespace Qt::Literals::StringLiterals;

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
    auto mKdeApplicationTreeView = page.findChild<KDEApplicationTreeView *>(u"mKdeApplicationTreeView"_s);
    QVERIFY(mKdeApplicationTreeView);
    QVERIFY(!mKdeApplicationTreeView->rootIsDecorated());
    QVERIFY(mKdeApplicationTreeView->header()->isHidden());
    QVERIFY(mKdeApplicationTreeView->uniformRowHeights());

    auto mainLayout = page.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto selectAll = page.findChild<QPushButton *>(u"selectall"_s);
    QVERIFY(selectAll);
    QVERIFY(selectAll->isEnabled());

    auto deselectAll = page.findChild<QPushButton *>(u"deselectall"_s);
    QVERIFY(deselectAll);
    QVERIFY(deselectAll->isEnabled());

    auto mTurnOffAllMessages = page.findChild<QPushButton *>(u"deselectallmessage"_s);
    QVERIFY(mTurnOffAllMessages);
    QVERIFY(mTurnOffAllMessages->isEnabled());

    auto mSearchLineEdit = page.findChild<QLineEdit *>(u"mSearchLineEdit"_s);
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->text().isEmpty());
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
}

#include "moc_kdeapplicationdebugsettingpagetest.cpp"
