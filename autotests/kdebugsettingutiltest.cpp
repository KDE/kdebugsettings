/*
  Copyright (c) 2015-2016 Montel Laurent <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

*/

#include "kdebugsettingutiltest.h"
#include "../src/kdebugsettingsutil.h"
#include <qtest.h>

KDebugSettingUtilTest::KDebugSettingUtilTest(QObject *parent)
    : QObject(parent)
{

}

KDebugSettingUtilTest::~KDebugSettingUtilTest()
{

}

void KDebugSettingUtilTest::shouldParseKdeLoggingLine_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("description");
    QTest::addColumn<QString>("logname");
    QTest::addColumn<bool>("valid");
    QTest::newRow("empty") <<  QString() << QString() << QString() << false;
    QTest::newRow("validLine") << QStringLiteral("log linux") << QStringLiteral("linux") << QStringLiteral("log") << true;
    QTest::newRow("validLinewithspace") << QStringLiteral(" log linux  ") << QStringLiteral("linux") << QStringLiteral("log") << true;
    QTest::newRow("comment") << QStringLiteral("#log linux  ") << QString() << QString() << false;
    QTest::newRow("commentWithSpace") << QStringLiteral("   #log linux  ") << QString() << QString() << false;
    QTest::newRow("badline") << QStringLiteral("log") << QString() << QString() << false;
}

void KDebugSettingUtilTest::shouldParseKdeLoggingLine()
{
    QFETCH(QString, input);
    QFETCH(QString, description);
    QFETCH(QString, logname);
    QFETCH(bool, valid);
    KdeLoggingCategory result;
    result.description = description;
    result.logName = logname;
    const KdeLoggingCategory cat = KDebugSettingsUtil::parseLineKdeLoggingCategory(input);
    QCOMPARE(cat, result);
    QCOMPARE(cat.isValid(), valid);
}

void KDebugSettingUtilTest::shouldParseQtLoggingLine_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("description");
    QTest::addColumn<QString>("logname");
    QTest::addColumn<QString>("type");
    QTest::addColumn<LoggingCategory::LoggingType>("loggingtype");
    QTest::addColumn<bool>("enabled");
    QTest::addColumn<bool>("valid");
    QTest::newRow("empty") <<  QString() << QString() << QString() << QString() << LoggingCategory::Info << true << false;
    QTest::newRow("valid") <<  QStringLiteral("toto=true") << QString() << QStringLiteral("toto") << QString() << LoggingCategory::Info << true << true;
    QTest::newRow("validdisabled") <<  QStringLiteral("toto=false") << QString() << QStringLiteral("toto") << QString() << LoggingCategory::Info << false << true;

    QTest::newRow("validdisabledwithtypewarning") <<  QStringLiteral("toto.warning=false") << QString() << QStringLiteral("toto") << QStringLiteral("warning") << LoggingCategory::Info << false << true;
    QTest::newRow("validenabledwithtypewarning") <<  QStringLiteral("toto.warning=true") << QString() << QStringLiteral("toto") << QStringLiteral("warning") << LoggingCategory::Info << true << true;

    QTest::newRow("validdisabledwithtypecritical") <<  QStringLiteral("toto.critical=false") << QString() << QStringLiteral("toto") << QStringLiteral("critical") << LoggingCategory::Info << false << true;
    QTest::newRow("validenabledwithtypecritical") <<  QStringLiteral("toto.critical=true") << QString() << QStringLiteral("toto") << QStringLiteral("critical") << LoggingCategory::Info << true << true;

    QTest::newRow("validdisabledwithtypedebug") <<  QStringLiteral("toto.debug=false") << QString() << QStringLiteral("toto") << QStringLiteral("debug") << LoggingCategory::Info << false << true;
    QTest::newRow("validenabledwithtypedebug") <<  QStringLiteral("toto.debug=true") << QString() << QStringLiteral("toto") << QStringLiteral("debug") << LoggingCategory::Info << true << true;

    QTest::newRow("invalid") <<  QStringLiteral("dd") << QString() << QString() << QString() << LoggingCategory::Info << true << false;
    QTest::newRow("invalidWithoutEnabledDisabled") <<  QStringLiteral("dd=") << QString() << QString() << QString() << LoggingCategory::Info << true  << false;
}

void KDebugSettingUtilTest::shouldParseQtLoggingLine()
{
    QFETCH(QString, input);
    QFETCH(QString, description);
    QFETCH(QString, logname);
    QFETCH(QString, type);
    QFETCH(LoggingCategory::LoggingType, loggingtype);
    QFETCH(bool, enabled);
    QFETCH(bool, valid);
    LoggingCategory result;
    result.description = description;
    result.logName = logname;
    result.type = type;
    result.enabled = enabled;
    result.loggingType = loggingtype;
#if 0 //FIXME
    const LoggingCategory cat = KDebugSettingsUtil::parseLineLoggingQtCategory(input);
    QCOMPARE(cat, result);
    QCOMPARE(cat.isValid(), valid);
#endif
}

QTEST_GUILESS_MAIN(KDebugSettingUtilTest)
