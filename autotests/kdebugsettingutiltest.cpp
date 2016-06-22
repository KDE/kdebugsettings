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
    QTest::addColumn<QString>("logname");
    QTest::addColumn<KDebugSettingsUtil::LoadLoggingCategory::LogType>("loggingtype");
    QTest::addColumn<bool>("enabled");
    QTest::addColumn<bool>("valid");
    QTest::newRow("empty") <<  QString() << QString() << KDebugSettingsUtil::LoadLoggingCategory::Unknown << false << false;
    QTest::newRow("valid") <<  QStringLiteral("toto=true") << QStringLiteral("toto") << KDebugSettingsUtil::LoadLoggingCategory::All << true << true;
    QTest::newRow("validdisabled") <<  QStringLiteral("toto=false") << QStringLiteral("toto") << KDebugSettingsUtil::LoadLoggingCategory::All << false << true;

    QTest::newRow("validdisabledwithtypewarning") <<  QStringLiteral("toto.warning=false") << QStringLiteral("toto") << KDebugSettingsUtil::LoadLoggingCategory::Warning << false << true;
    QTest::newRow("validenabledwithtypewarning") <<  QStringLiteral("toto.warning=true") << QStringLiteral("toto") << KDebugSettingsUtil::LoadLoggingCategory::Warning << true << true;

    QTest::newRow("validdisabledwithtypecritical") <<  QStringLiteral("toto.critical=false") << QStringLiteral("toto") << KDebugSettingsUtil::LoadLoggingCategory::Critical << false << true;
    QTest::newRow("validenabledwithtypecritical") <<  QStringLiteral("toto.critical=true") << QStringLiteral("toto") << KDebugSettingsUtil::LoadLoggingCategory::Critical << true << true;

    QTest::newRow("validdisabledwithtypedebug") <<  QStringLiteral("toto.debug=false") << QStringLiteral("toto") << KDebugSettingsUtil::LoadLoggingCategory::Debug << false << true;
    QTest::newRow("validenabledwithtypedebug") <<  QStringLiteral("toto.debug=true") << QStringLiteral("toto") << KDebugSettingsUtil::LoadLoggingCategory::Debug << true << true;

    QTest::newRow("invalid") <<  QStringLiteral("dd") << QString() << KDebugSettingsUtil::LoadLoggingCategory::Unknown << false << false;
    QTest::newRow("invalidWithoutEnabledDisabled") <<  QStringLiteral("dd=") << QStringLiteral("dd") << KDebugSettingsUtil::LoadLoggingCategory::All << false  << true;
}

void KDebugSettingUtilTest::shouldParseQtLoggingLine()
{
    QFETCH(QString, input);
    QFETCH(QString, logname);
    QFETCH(KDebugSettingsUtil::LoadLoggingCategory::LogType, loggingtype);
    QFETCH(bool, enabled);
    QFETCH(bool, valid);
    KDebugSettingsUtil::LoadLoggingCategory result;
    result.logName = logname;
    result.enabled = enabled;
    result.type = loggingtype;
    const KDebugSettingsUtil::LoadLoggingCategory cat = KDebugSettingsUtil::parseLineLoggingQtCategory(input);
    QCOMPARE(cat.isValid(), valid);
    QCOMPARE(cat, result);
}

void KDebugSettingUtilTest::shouldReadLoadKdeCategories_data()
{
    QTest::addColumn<QString>("filename");
    QTest::addColumn<int>("numberofcategories");
    QTest::newRow("empty") << QStringLiteral("empty.categories") << 0;
    QTest::newRow("correctlist") << QStringLiteral("correct.categories") << 5;
    QTest::newRow("withduplicate") << QStringLiteral("duplicates.categories") << 5;
    QTest::newRow("withcomment") << QStringLiteral("comments.categories") << 6;
}

void KDebugSettingUtilTest::shouldReadLoadKdeCategories()
{
    QFETCH(QString, filename);
    QFETCH(int, numberofcategories);
    const QString path = QString(QLatin1String(KDEBUGSETTINGS_DATA_DIR) + QLatin1Char('/') + filename);
    QFile file(path);
    QVERIFY(file.exists());
    KdeLoggingCategory::List lst;
    KDebugSettingsUtil::readLoggingCategories(path, lst, true);
    QCOMPARE(lst.count(), numberofcategories);
}

QTEST_GUILESS_MAIN(KDebugSettingUtilTest)
