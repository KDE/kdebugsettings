/*
    SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class CategoryWarningTest : public QObject
{
    Q_OBJECT
public:
    explicit CategoryWarningTest(QObject *parent = nullptr);
    ~CategoryWarningTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
