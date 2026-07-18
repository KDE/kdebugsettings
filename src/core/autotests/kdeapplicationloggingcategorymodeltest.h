/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class KDEApplicationLoggingCategoryModelTest : public QObject
{
    Q_OBJECT
public:
    explicit KDEApplicationLoggingCategoryModelTest(QObject *parent = nullptr);
    ~KDEApplicationLoggingCategoryModelTest() override = default;

private Q_SLOTS:
    void shouldExposeUserRolesForQml();
    void shouldReturnExpectedDataForWidgetsAndQml();
};
