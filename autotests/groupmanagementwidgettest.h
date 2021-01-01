/*
    SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef GROUPMANAGEMENTWIDGETTEST_H
#define GROUPMANAGEMENTWIDGETTEST_H

#include <QObject>

class GroupManagementWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit GroupManagementWidgetTest(QObject *parent = nullptr);
    ~GroupManagementWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // GROUPMANAGEMENTWIDGETTEST_H
