/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class CustomLoggingCategoryModelTest : public QObject
{
    Q_OBJECT
public:
    explicit CustomLoggingCategoryModelTest(QObject *parent = nullptr);
    ~CustomLoggingCategoryModelTest() override = default;

private Q_SLOTS:
    void shouldNotSignalWhenRemovingUnknownCategories();
    void shouldRemoveCategoriesAsRowsRemoved();
    void shouldRemoveOneRowPerRequestedCategory();
};
