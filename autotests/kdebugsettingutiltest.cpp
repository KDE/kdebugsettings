/*
  Copyright (c) 2015 Montel Laurent <montel@kde.org>

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

void KDebugSettingUtilTest::shouldParseKdeLogginLine_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("description");
    QTest::addColumn<QString>("logname");
    QTest::addColumn<QString>("type");
    QTest::addColumn<bool>("enabled");
    QTest::newRow("empty") <<  QString() << QString() << QString() << QString() << false;
    QTest::newRow("validLine") << QStringLiteral("log linux") << QStringLiteral("linux") << QStringLiteral("log") << QString() << false;
    QTest::newRow("validLinewithspace") << QStringLiteral(" log linux  ") << QStringLiteral("linux") << QStringLiteral("log") << QString() << false;
    QTest::newRow("comment") << QStringLiteral("#log linux  ") << QString() << QString() << QString() << false;
    QTest::newRow("commentWithSpace") << QStringLiteral("   #log linux  ") << QString() << QString() << QString() << false;
    QTest::newRow("badline") << QStringLiteral("log") << QString() << QString() << QString() << false;
}

void KDebugSettingUtilTest::shouldParseKdeLogginLine()
{
    QFETCH( QString, input );
    QFETCH( QString, description );
    QFETCH( QString, logname );
    QFETCH( QString, type );
    QFETCH( bool, enabled );
    Category result;
    result.description = description;
    result.logName = logname;
    result.type = type;
    result.enabled = enabled;
    const Category cat = KDebugSettingsUtil::parseLineKdeLoggingCategory(input);
    QCOMPARE(cat, result);
}

void KDebugSettingUtilTest::shouldParseQtLogginLine_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("description");
    QTest::addColumn<QString>("logname");
    QTest::addColumn<QString>("type");
    QTest::addColumn<bool>("enabled");
    QTest::newRow("empty") <<  QString() << QString() << QString() << QString() << false;
    QTest::newRow("valid") <<  QStringLiteral("toto=true") << QString() << QStringLiteral("toto") << QString() << true;
    QTest::newRow("validdisabled") <<  QStringLiteral("toto=false") << QString() << QStringLiteral("toto") << QString() << false;

    QTest::newRow("validdisabledwithtypewarning") <<  QStringLiteral("toto.warning=false") << QString() << QStringLiteral("toto") << QStringLiteral("warning") << false;
    QTest::newRow("validenabledwithtypewarning") <<  QStringLiteral("toto.warning=true") << QString() << QStringLiteral("toto") << QStringLiteral("warning") << true;

    QTest::newRow("validdisabledwithtypecritical") <<  QStringLiteral("toto.critical=false") << QString() << QStringLiteral("toto") << QStringLiteral("critical") << false;
    QTest::newRow("validenabledwithtypecritical") <<  QStringLiteral("toto.critical=true") << QString() << QStringLiteral("toto") << QStringLiteral("critical") << true;

    QTest::newRow("validdisabledwithtypedebug") <<  QStringLiteral("toto.debug=false") << QString() << QStringLiteral("toto") << QStringLiteral("debug") << false;
    QTest::newRow("validenabledwithtypedebug") <<  QStringLiteral("toto.debug=true") << QString() << QStringLiteral("toto") << QStringLiteral("debug") << true;

    QTest::newRow("invalid") <<  QStringLiteral("dd") << QString() << QString() << QString() << false;
    QTest::newRow("invalidWithoutEnabledDisabled") <<  QStringLiteral("dd=") << QString() << QString() << QString() << false;
}

void KDebugSettingUtilTest::shouldParseQtLogginLine()
{
    QFETCH( QString, input );
    QFETCH( QString, description );
    QFETCH( QString, logname );
    QFETCH( QString, type );
    QFETCH( bool, enabled );
    Category result;
    result.description = description;
    result.logName = logname;
    result.type = type;
    result.enabled = enabled;
    const Category cat = KDebugSettingsUtil::parseLineLoggingQtCategory(input);
    QCOMPARE(cat, result);
}

QTEST_GUILESS_MAIN(KDebugSettingUtilTest)
