/*
    SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef CHANGEDEBUGMODEJOBTEST_H
#define CHANGEDEBUGMODEJOBTEST_H

#include <QObject>

class ChangeDebugModeJobTest : public QObject
{
    Q_OBJECT
public:
    explicit ChangeDebugModeJobTest(QObject *parent = nullptr);
    ~ChangeDebugModeJobTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldBeAbleToStart();
    void shouldBeAbleToStartWithoutArgument();
    void shouldConvertToLoggingType();
};

#endif // CHANGEDEBUGMODEJOBTEST_H
