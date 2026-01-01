/*
    SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class CategoryTypeComboBoxTest : public QObject
{
    Q_OBJECT
public:
    explicit CategoryTypeComboBoxTest(QObject *parent = nullptr);
    ~CategoryTypeComboBoxTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldSetType_data();
    void shouldSetType();

    void shouldVerifyItNotDefault();
    void shouldChangeDefaultCategory();

    void shouldVerifyThatDefaultCategoryIsCorrect();
};
