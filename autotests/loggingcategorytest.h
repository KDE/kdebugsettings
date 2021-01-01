/*
    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef LOGGINGCATEGORYTEST_H
#define LOGGINGCATEGORYTEST_H

#include <QObject>

class LoggingCategoryTest : public QObject
{
    Q_OBJECT
public:
    explicit LoggingCategoryTest(QObject *parent = nullptr);
    ~LoggingCategoryTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldBeEqual();
    void shouldCreateRules();
    void shouldCreateRules_data();
};

#endif // LOGGINGCATEGORYTEST_H
