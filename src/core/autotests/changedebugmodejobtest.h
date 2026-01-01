/*
    SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class ChangeDebugModeJobTest : public QObject
{
    Q_OBJECT
public:
    explicit ChangeDebugModeJobTest(QObject *parent = nullptr);
    ~ChangeDebugModeJobTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldBeAbleToStart();
    void shouldBeAbleToStartWithoutArgument();
    void shouldConvertToLoggingType();
};
