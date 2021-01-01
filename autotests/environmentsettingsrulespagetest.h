/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef ENVIRONMENTSETTINGSRULESPAGETEST_H
#define ENVIRONMENTSETTINGSRULESPAGETEST_H

#include <QObject>

class EnvironmentSettingsRulesPageTest : public QObject
{
    Q_OBJECT
public:
    explicit EnvironmentSettingsRulesPageTest(QObject *parent = nullptr);
    ~EnvironmentSettingsRulesPageTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldSetRules();
};

#endif // ENVIRONMENTSETTINGSRULESPAGETEST_H
