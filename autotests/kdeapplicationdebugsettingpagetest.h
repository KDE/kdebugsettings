/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef KDEAPPLICATIONDEBUGSETTINGPAGETEST_H
#define KDEAPPLICATIONDEBUGSETTINGPAGETEST_H

#include <QObject>

class KDEApplicationDebugSettingPageTest : public QObject
{
    Q_OBJECT
public:
    explicit KDEApplicationDebugSettingPageTest(QObject *parent = nullptr);
    ~KDEApplicationDebugSettingPageTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // KDEAPPLICATIONDEBUGSETTINGPAGETEST_H
