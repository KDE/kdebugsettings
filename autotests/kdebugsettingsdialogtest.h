/*
    SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef KDEBUGSETTINGSDIALOGTEST_H
#define KDEBUGSETTINGSDIALOGTEST_H

#include <QObject>

class KDebugSettingsDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit KDebugSettingsDialogTest(QObject *parent = nullptr);
    ~KDebugSettingsDialogTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // KDEBUGSETTINGSDIALOGTEST_H
