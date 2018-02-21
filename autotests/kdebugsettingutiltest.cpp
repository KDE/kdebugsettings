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
#include <QDebug>

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
    QTest::addColumn<QString>("defaultCategory");
    QTest::addColumn<bool>("valid");
    QTest::newRow("empty") <<  QString() << QString() << QString() << QString() << false;

    QTest::newRow("validLine") << QStringLiteral("log linux") << QStringLiteral("linux") << QStringLiteral("log") << QString() << true;
    QTest::newRow("validLinewithspace") << QStringLiteral(" log linux  ") << QStringLiteral("linux") << QStringLiteral("log") << QString() << true;
    QTest::newRow("comment") << QStringLiteral("#log linux  ") << QString() << QString() << QString() << false;
    QTest::newRow("commentWithSpace") << QStringLiteral("   #log linux  ") << QString() << QString() << QString() << false;
    QTest::newRow("badline") << QStringLiteral("log") << QString() << QString() << QString() << false;
    QTest::newRow("comment-2") << QStringLiteral("#log linux") << QString() << QString() << QString() << false;
    QTest::newRow("validLineWithParentheses") << QStringLiteral("log linux (foo)") << QStringLiteral("linux (foo)") << QStringLiteral("log") << QString() << true;

    QTest::newRow("validLineWithParenthesesAndCategories") << QStringLiteral("log linux (foo) [WARNING]") << QStringLiteral("linux (foo)") << QStringLiteral("log") <<  QStringLiteral("WARNING") << true;

    QTest::newRow("validLineCategoriesWarning") << QStringLiteral("log linux [WARNING]") << QStringLiteral("linux") << QStringLiteral("log") << QStringLiteral("WARNING") << true;
    QTest::newRow("validLineCategoriesWarning2") << QStringLiteral("log linux [WARNING]    ") << QStringLiteral("linux") << QStringLiteral("log") << QStringLiteral("WARNING") << true;
    QTest::newRow("validLineCategoriesWarning3") << QStringLiteral("log linux      [WARNING]    ") << QStringLiteral("linux") << QStringLiteral("log") << QStringLiteral("WARNING") << true;
    QTest::newRow("validLineBadCategories") << QStringLiteral("log linux      [FOO]    ") << QStringLiteral("linux [FOO]") << QStringLiteral("log") << QString() << true;
    QTest::newRow("linewithcomment") << QStringLiteral("log linux#comment about linux") << QStringLiteral("linux") << QStringLiteral("log") << QString() << true;

    QTest::newRow("validLineCategoriesInfo") << QStringLiteral("log linux [INFO]") << QStringLiteral("linux") << QStringLiteral("log") << QStringLiteral("INFO") << true;
    QTest::newRow("validLineCategoriesInfo2") << QStringLiteral("log linux [INFO]    ") << QStringLiteral("linux") << QStringLiteral("log") << QStringLiteral("INFO") << true;
    QTest::newRow("validLineCategoriesInfo3") << QStringLiteral("log linux      [INFO]    ") << QStringLiteral("linux") << QStringLiteral("log") << QStringLiteral("INFO") << true;

    QTest::newRow("validLineCategoriesDEBUG") << QStringLiteral("log linux [DEBUG]") << QStringLiteral("linux") << QStringLiteral("log") << QStringLiteral("DEBUG") << true;
    QTest::newRow("validLineCategoriesDEBUG2") << QStringLiteral("log linux [DEBUG]    ") << QStringLiteral("linux") << QStringLiteral("log") << QStringLiteral("DEBUG") << true;
    QTest::newRow("validLineCategoriesDEBUG3") << QStringLiteral("log linux      [DEBUG]    ") << QStringLiteral("linux") << QStringLiteral("log") << QStringLiteral("DEBUG") << true;

    QTest::newRow("validLineCategoriesCRITICAL") << QStringLiteral("log linux [CRITICAL]") << QStringLiteral("linux") << QStringLiteral("log") << QStringLiteral("CRITICAL") << true;
    QTest::newRow("validLineCategoriesCRITICAL2") << QStringLiteral("log linux [CRITICAL]    ") << QStringLiteral("linux") << QStringLiteral("log") << QStringLiteral("CRITICAL") << true;
    QTest::newRow("validLineCategoriesCRITICAL3") << QStringLiteral("log linux      [CRITICAL]    ") << QStringLiteral("linux") << QStringLiteral("log") << QStringLiteral("CRITICAL") << true;
}

void KDebugSettingUtilTest::shouldParseKdeLoggingLine()
{
    QFETCH(QString, input);
    QFETCH(QString, description);
    QFETCH(QString, logname);
    QFETCH(QString, defaultCategory);
    QFETCH(bool, valid);
    KdeLoggingCategory result;
    result.description = description;
    result.logName = logname;
    result.defaultCategory = defaultCategory;
    const KdeLoggingCategory cat = KDebugSettingsUtil::parseLineKdeLoggingCategory(input);
    if (cat != result) {
        qDebug() << "Generated category " << cat;
        qDebug() << "Expected category: "<<result;
    }
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

void KDebugSettingUtilTest::shouldConvertCategoryTypeFromString_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<LoggingCategory::LoggingType>("loggingType");
    QTest::newRow("empty") << QString() << LoggingCategory::LoggingType::Info;
    QTest::newRow("WARNING") << QStringLiteral("WARNING") << LoggingCategory::LoggingType::Warning;
    QTest::newRow("Info") << QStringLiteral("INFO") << LoggingCategory::LoggingType::Info;
    QTest::newRow("Debug") << QStringLiteral("DEBUG") << LoggingCategory::LoggingType::Debug;
    QTest::newRow("Critical") << QStringLiteral("CRITICAL") << LoggingCategory::LoggingType::Critical;
    QTest::newRow("unknow") << QStringLiteral("foo") << LoggingCategory::LoggingType::Info;
}

void KDebugSettingUtilTest::shouldConvertCategoryTypeFromString()
{
    QFETCH(QString, input);
    QFETCH(LoggingCategory::LoggingType, loggingType);
    QCOMPARE(KDebugSettingsUtil::convertCategoryTypeFromString(input), loggingType);
}

QTEST_GUILESS_MAIN(KDebugSettingUtilTest)
