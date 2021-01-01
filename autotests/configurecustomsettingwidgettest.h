/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef CONFIGURECUSTOMSETTINGWIDGETTEST_H
#define CONFIGURECUSTOMSETTINGWIDGETTEST_H

#include <QObject>

class ConfigureCustomSettingWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfigureCustomSettingWidgetTest(QObject *parent = nullptr);
    ~ConfigureCustomSettingWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldRestoreRules_data();
    void shouldRestoreRules();
    void shouldEmitSignalWhenWeChangeLogName();
};

#endif // CONFIGURECUSTOMSETTINGWIDGETTEST_H
