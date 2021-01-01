/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef CONFIGURECUSTOMSETTINGDIALOGTEST_H
#define CONFIGURECUSTOMSETTINGDIALOGTEST_H

#include <QObject>

class ConfigureCustomSettingDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfigureCustomSettingDialogTest(QObject *parent = nullptr);
    ~ConfigureCustomSettingDialogTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // CONFIGURECUSTOMSETTINGDIALOGTEST_H
