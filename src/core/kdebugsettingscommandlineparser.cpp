/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "kdebugsettingscommandlineparser.h"
#include <KLocalizedString>
#include <QCommandLineParser>

using namespace Qt::Literals::StringLiterals;
KDebugSettingsCommandLineParser::KDebugSettingsCommandLineParser(QCommandLineParser *parser)
{
    initializeCommandLine(parser);
}

KDebugSettingsCommandLineParser::~KDebugSettingsCommandLineParser() = default;

void KDebugSettingsCommandLineParser::initializeCommandLine(QCommandLineParser *parser)
{
    const QCommandLineOption testModeOption(KDebugSettingsCommandLineParser::optionParserFromEnum(KDebugSettingsCommandLineParser::OptionParser::TestMode),
                                            i18n("Enable QStandardPaths test mode, i.e. read/write settings used by unittests"));
    parser->addOption(testModeOption);

    const QCommandLineOption switchFullDebugOption(
        KDebugSettingsCommandLineParser::optionParserFromEnum(KDebugSettingsCommandLineParser::OptionParser::EnableFullDebug),
        i18n("Activate full debug for all modules."));
    parser->addOption(switchFullDebugOption);
    const QCommandLineOption switchOffDebugOption(
        KDebugSettingsCommandLineParser::optionParserFromEnum(KDebugSettingsCommandLineParser::OptionParser::DisableFullDebug),
        i18n("Disable full debug for all modules."));
    parser->addOption(switchOffDebugOption);

    const QCommandLineOption changeDebugSettingOption(
        KDebugSettingsCommandLineParser::optionParserFromEnum(KDebugSettingsCommandLineParser::OptionParser::DebugMode),
        i18n("Change debug mode as console (in console)"),
        u"Full|Info|Warning|Critical|Off"_s);
    parser->addOption(changeDebugSettingOption);
    parser->addPositionalArgument(u"logging category name"_s, i18n("Specify logging category name that you want to change debug mode (in console)"));

    QCommandLineOption selfTestOption(optionParserFromEnum(OptionParser::SelfTest), QStringLiteral("internal, for automated testing"));
    selfTestOption.setFlags(QCommandLineOption::HiddenFromHelp);
    parser->addOption(selfTestOption);
}

QString KDebugSettingsCommandLineParser::optionParserFromEnum(OptionParser e)
{
    switch (e) {
    case OptionParser::TestMode:
        return u"test-mode"_s;
    case OptionParser::EnableFullDebug:
        return u"enable-full-debug"_s;
    case OptionParser::DisableFullDebug:
        return u"disable-full-debug"_s;
    case OptionParser::DebugMode:
        return u"debug-mode"_s;
    case OptionParser::SelfTest:
        return u"self-test"_s;
    }
    return {};
}
