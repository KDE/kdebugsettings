/*
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class LoadCategoriesJobTest : public QObject
{
    Q_OBJECT
public:
    explicit LoadCategoriesJobTest(QObject *parent = nullptr);
    ~LoadCategoriesJobTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldReadRules_data();
    void shouldReadRules();
};
