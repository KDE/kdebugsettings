/*
    SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class RenameCategoryTest : public QObject
{
    Q_OBJECT
public:
    explicit RenameCategoryTest(QObject *parent = nullptr);
    ~RenameCategoryTest() override;
private Q_SLOTS:
    void shouldParseRenameLine_data();
    void shouldParseRenameLine();
};
