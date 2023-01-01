/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class CustomDebugSettingsPageTest : public QObject
{
    Q_OBJECT
public:
    explicit CustomDebugSettingsPageTest(QObject *parent = nullptr);
    ~CustomDebugSettingsPageTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
