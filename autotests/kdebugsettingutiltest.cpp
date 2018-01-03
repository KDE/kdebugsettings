/*
  Copyright (c) 2015-2018 Montel Laurent <montel@kde.org>

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
    QTest::newRow("comment-2") << QStringLiteral("#log linux") << QString() << QString() << false;

    QTest::newRow("linewithcomment") << QStringLiteral("log linux#comment about linux") << QStringLiteral("linux") << QStringLiteral("log") << true;
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
    QTest::addColumn<KDebugSettingsUtil::LineLoggingQtCategory::LoggingType>("loggingtype");
    QTest::addColumn<bool>("enabled");
    QTest::addColumn<bool>("valid");
    QTest::newRow("empty") <<  QString() << QString() << KDebugSettingsUtil::LineLoggingQtCategory::Unknown << false << false;
    QTest::newRow("valid") <<  QStringLiteral("toto=true") << QStringLiteral("toto") << KDebugSettingsUtil::LineLoggingQtCategory::All << true << true;
    QTest::newRow("validdisabled") <<  QStringLiteral("toto=false") << QStringLiteral("toto") << KDebugSettingsUtil::LineLoggingQtCategory::All << false << true;

    QTest::newRow("validdisabledwithtypewarning") <<  QStringLiteral("toto.warning=false") << QStringLiteral("toto") << KDebugSettingsUtil::LineLoggingQtCategory::Warning << false << true;
    QTest::newRow("validenabledwithtypewarning") <<  QStringLiteral("toto.warning=true") << QStringLiteral("toto") << KDebugSettingsUtil::LineLoggingQtCategory::Warning << true << true;

    QTest::newRow("validdisabledwithtypecritical") <<  QStringLiteral("toto.critical=false") << QStringLiteral("toto") << KDebugSettingsUtil::LineLoggingQtCategory::Critical << false << true;
    QTest::newRow("validenabledwithtypecritical") <<  QStringLiteral("toto.critical=true") << QStringLiteral("toto") << KDebugSettingsUtil::LineLoggingQtCategory::Critical << true << true;

    QTest::newRow("validdisabledwithtypedebug") <<  QStringLiteral("toto.debug=false") << QStringLiteral("toto") << KDebugSettingsUtil::LineLoggingQtCategory::Debug << false << true;
    QTest::newRow("validenabledwithtypedebug") <<  QStringLiteral("toto.debug=true") << QStringLiteral("toto") << KDebugSettingsUtil::LineLoggingQtCategory::Debug << true << true;

    QTest::newRow("invalid") <<  QStringLiteral("dd") << QString() << KDebugSettingsUtil::LineLoggingQtCategory::Unknown << false << false;
    QTest::newRow("invalidWithoutEnabledDisabled") <<  QStringLiteral("dd=") << QStringLiteral("dd") << KDebugSettingsUtil::LineLoggingQtCategory::All << false  << true;
}

void KDebugSettingUtilTest::shouldParseQtLoggingLine()
{
    QFETCH(QString, input);
    QFETCH(QString, logname);
    QFETCH(KDebugSettingsUtil::LineLoggingQtCategory::LoggingType, loggingtype);
    QFETCH(bool, enabled);
    QFETCH(bool, valid);
    KDebugSettingsUtil::LineLoggingQtCategory result;
    result.logName = logname;
    result.enabled = enabled;
    result.type = loggingtype;
    const KDebugSettingsUtil::LineLoggingQtCategory cat = KDebugSettingsUtil::parseLineLoggingQtCategory(input);
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

void KDebugSettingUtilTest::shouldReadRenameCategories_data()
{
    QTest::addColumn<QString>("filename");
    QTest::addColumn<int>("numberofrenamecategories");
    QTest::newRow("empty") << QStringLiteral("empty.renamecategories") << 0;
    QTest::newRow("2renamed") << QStringLiteral("tworename.renamecategories") << 2;
    QTest::newRow("withnewline") << QStringLiteral("newline.renamecategories") << 2;
}

void KDebugSettingUtilTest::shouldReadRenameCategories()
{
    QFETCH(QString, filename);
    QFETCH(int, numberofrenamecategories);
    const QString path = QString(QLatin1String(KDEBUGSETTINGS_DATA_DIR) + QLatin1Char('/') + filename);
    QFile file(path);
    QVERIFY(file.exists());
    const RenameCategory::List lst = KDebugSettingsUtil::readRenameCategories(path);
    QCOMPARE(lst.count(), numberofrenamecategories);
}

QTEST_GUILESS_MAIN(KDebugSettingUtilTest)
