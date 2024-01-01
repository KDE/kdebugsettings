/*
    SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class LoggingCategoryTest : public QObject
{
    Q_OBJECT
public:
    explicit LoggingCategoryTest(QObject *parent = nullptr);
    ~LoggingCategoryTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldBeEqual();
    void shouldCreateRules();
    void shouldCreateRules_data();
};
