/*
    SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef CATEGORYTYPECOMBOBOXTEST_H
#define CATEGORYTYPECOMBOBOXTEST_H

#include <QObject>

class CategoryTypeComboBoxTest : public QObject
{
    Q_OBJECT
public:
    explicit CategoryTypeComboBoxTest(QObject *parent = nullptr);
    ~CategoryTypeComboBoxTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldSetType_data();
    void shouldSetType();

    void shouldVerifyItNotDefault();
    void shouldChangeDefaultCategory();

    void shouldVerifyThatDefaultCategoryIsCorrect();
};

#endif // CATEGORYTYPECOMBOBOXTEST_H
