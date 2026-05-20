/*
 * SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */
#pragma once

#include <QObject>

class KDebugSettingsCommandLineParserTest : public QObject
{
    Q_OBJECT
public:
    explicit KDebugSettingsCommandLineParserTest(QObject *parent = nullptr);
    ~KDebugSettingsCommandLineParserTest() override = default;

private Q_SLOTS:
    void shouldVerifyOptionParserFromEnumValues();
};
