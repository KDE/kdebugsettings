/*
    SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef GROUPMANAGEMENTDIALOGTEST_H
#define GROUPMANAGEMENTDIALOGTEST_H

#include <QObject>

class GroupManagementDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit GroupManagementDialogTest(QObject *parent = nullptr);
    ~GroupManagementDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // GROUPMANAGEMENTDIALOGTEST_H
