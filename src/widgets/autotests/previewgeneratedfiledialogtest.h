/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class PreviewGeneratedFileDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit PreviewGeneratedFileDialogTest(QObject *parent = nullptr);
    ~PreviewGeneratedFileDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
