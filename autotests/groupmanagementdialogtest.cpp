/*
    SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "groupmanagementdialogtest.h"
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
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mGroupManagementWidget = w.findChild<GroupManagementWidget *>(QStringLiteral("mGroupManagementWidget"));
    QVERIFY(mGroupManagementWidget);

    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
}
