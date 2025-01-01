/*
    SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class SaveRulesJobTest : public QObject
{
    Q_OBJECT
public:
    explicit SaveRulesJobTest(QObject *parent = nullptr);
    ~SaveRulesJobTest() override = default;
private Q_SLOTS:
    void shouldSaveLoadRules_data();
    void shouldSaveLoadRules();
};
