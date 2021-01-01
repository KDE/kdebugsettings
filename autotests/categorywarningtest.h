/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef CATEGORYWARNINGTEST_H
#define CATEGORYWARNINGTEST_H

#include <QObject>

class CategoryWarningTest : public QObject
{
    Q_OBJECT
public:
    explicit CategoryWarningTest(QObject *parent = nullptr);
    ~CategoryWarningTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // CATEGORYWARNINGTEST_H
