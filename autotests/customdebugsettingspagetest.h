/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef CUSTOMDEBUGSETTINGSPAGETEST_H
#define CUSTOMDEBUGSETTINGSPAGETEST_H

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

#endif // CUSTOMDEBUGSETTINGSPAGETEST_H
