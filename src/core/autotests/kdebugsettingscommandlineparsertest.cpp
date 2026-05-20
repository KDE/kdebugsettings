/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "kdebugsettingscommandlineparsertest.h"
#include "kdebugsettingscommandlineparser.h"
#include <QTest>
QTEST_GUILESS_MAIN(KDebugSettingsCommandLineParserTest)
using namespace Qt::Literals::StringLiterals;
KDebugSettingsCommandLineParserTest::KDebugSettingsCommandLineParserTest(QObject *parent)
    : QObject{parent}
{
}

void KDebugSettingsCommandLineParserTest::shouldVerifyOptionParserFromEnumValues()
{
    QCOMPARE(KDebugSettingsCommandLineParser::optionParserFromEnum(KDebugSettingsCommandLineParser::OptionParser::SelfTest), u"self-test"_s);
    QCOMPARE(KDebugSettingsCommandLineParser::optionParserFromEnum(KDebugSettingsCommandLineParser::OptionParser::TestMode), u"test-mode"_s);
    QCOMPARE(KDebugSettingsCommandLineParser::optionParserFromEnum(KDebugSettingsCommandLineParser::OptionParser::EnableFullDebug), u"enable-full-debug"_s);
    QCOMPARE(KDebugSettingsCommandLineParser::optionParserFromEnum(KDebugSettingsCommandLineParser::OptionParser::DisableFullDebug), u"disable-full-debug"_s);
    QCOMPARE(KDebugSettingsCommandLineParser::optionParserFromEnum(KDebugSettingsCommandLineParser::OptionParser::DebugMode), u"debug-mode"_s);
}

#include "moc_kdebugsettingscommandlineparsertest.cpp"
