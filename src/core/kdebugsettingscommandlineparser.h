/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */
#pragma once
#include "libkdebugsettingscore_export.h"
#include <QString>
class QCommandLineParser;
class LIBKDEBUGSETTINGSCORE_EXPORT KDebugSettingsCommandLineParser
{
public:
    enum class OptionParser : uint8_t {
        TestMode = 0,
        EnableFullDebug,
        DisableFullDebug,
        DebugMode,
        SelfTest,
    };
    explicit KDebugSettingsCommandLineParser(QCommandLineParser *parser);
    ~KDebugSettingsCommandLineParser();

    [[nodiscard]] static QString optionParserFromEnum(OptionParser e);

private:
    LIBKDEBUGSETTINGSCORE_NO_EXPORT void initializeCommandLine(QCommandLineParser *parser);
};
