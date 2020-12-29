/*
    SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef SAVERULESJOBTEST_H
#define SAVERULESJOBTEST_H

#include <QObject>

class SaveRulesJobTest : public QObject
{
    Q_OBJECT
public:
    explicit SaveRulesJobTest(QObject *parent = nullptr);
    ~SaveRulesJobTest() = default;
private Q_SLOTS:
    void shouldSaveLoadRules_data();
    void shouldSaveLoadRules();
};

#endif // SAVERULESJOBTEST_H
