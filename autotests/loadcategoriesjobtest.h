/*
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef LOADCATEGORIESJOBTEST_H
#define LOADCATEGORIESJOBTEST_H

#include <QObject>

class LoadCategoriesJobTest : public QObject
{
    Q_OBJECT
public:
    explicit LoadCategoriesJobTest(QObject *parent = nullptr);
    ~LoadCategoriesJobTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldReadRules_data();
    void shouldReadRules();
};

#endif // LOADCATEGORIESJOBTEST_H
