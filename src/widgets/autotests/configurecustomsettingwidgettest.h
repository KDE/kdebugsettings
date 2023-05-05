/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class ConfigureCustomSettingWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfigureCustomSettingWidgetTest(QObject *parent = nullptr);
    ~ConfigureCustomSettingWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldRestoreRules_data();
    void shouldRestoreRules();
    void shouldEmitSignalWhenWeChangeLogName();
};
