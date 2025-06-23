/*
    SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "groupmanagementdialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "groupmanagementdialog.h"
#include "groupmanagementwidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(GroupManagementDialogTest)
GroupManagementDialogTest::GroupManagementDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void GroupManagementDialogTest::shouldHaveDefaultValues()
{
    GroupManagementDialog w;
    QVERIFY(!w.windowTitle().isEmpty());
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mGroupManagementWidget = w.findChild<GroupManagementWidget *>(u"mGroupManagementWidget"_s);
    QVERIFY(mGroupManagementWidget);

    auto buttonBox = w.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
}

#include "moc_groupmanagementdialogtest.cpp"
