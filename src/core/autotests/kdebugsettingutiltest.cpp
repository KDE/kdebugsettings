/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdebugsettingutiltest.h"
#include "kdebugsettingsutil.h"
#include <QDebug>
#include <QTest>

KDebugSettingUtilTest::KDebugSettingUtilTest(QObject *parent)
    : QObject(parent)
{
}

KDebugSettingUtilTest::~KDebugSettingUtilTest() = default;

void KDebugSettingUtilTest::shouldParseKdeLoggingLine_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("description");
    QTest::addColumn<QString>("logname");
    QTest::addColumn<QString>("defaultSeverity");
    QTest::addColumn<QString>("identifier");
    QTest::addColumn<bool>("valid");
    // Old format
    QTest::newRow("empty") << QString() << QString() << QString() << QString() << QString() << false;

    QTest::newRow("validLine") << QStringLiteral("log linux") << QStringLiteral("linux") << QStringLiteral("log") << QString() << QString() << true;
    QTest::newRow("validLinewithspace") << QStringLiteral(" log linux  ") << QStringLiteral("linux") << QStringLiteral("log") << QString() << QString() << true;
    QTest::newRow("comment") << QStringLiteral("#log linux  ") << QString() << QString() << QString() << QString() << false;
    QTest::newRow("commentWithSpace") << QStringLiteral("   #log linux  ") << QString() << QString() << QString() << QString() << false;
    QTest::newRow("badline") << QStringLiteral("log") << QString() << QString() << QString() << QString() << false;
    QTest::newRow("comment-2") << QStringLiteral("#log linux") << QString() << QString() << QString() << QString() << false;
    QTest::newRow("validLineWithParentheses") << QStringLiteral("log linux (foo)") << QStringLiteral("linux (foo)") << QStringLiteral("log") << QString()
                                              << QString() << true;

    QTest::newRow("validLineWithParenthesesAndCategories") << QStringLiteral("log linux (foo) [WARNING]") << QStringLiteral("linux (foo)")
                                                           << QStringLiteral("log") << QStringLiteral("WARNING") << QString() << true;

    QTest::newRow("validLineCategoriesWarning") << QStringLiteral("log linux [WARNING]") << QStringLiteral("linux") << QStringLiteral("log")
                                                << QStringLiteral("WARNING") << QString() << true;
    QTest::newRow("validLineCategoriesWarning2") << QStringLiteral("log linux [WARNING]    ") << QStringLiteral("linux") << QStringLiteral("log")
                                                 << QStringLiteral("WARNING") << QString() << true;
    QTest::newRow("validLineCategoriesWarning3") << QStringLiteral("log linux      [WARNING]    ") << QStringLiteral("linux") << QStringLiteral("log")
                                                 << QStringLiteral("WARNING") << QString() << true;
    QTest::newRow("validLineBadCategories") << QStringLiteral("log linux      [FOO]    ") << QStringLiteral("linux [FOO]") << QStringLiteral("log") << QString()
                                            << QString() << true;
    QTest::newRow("linewithcomment") << QStringLiteral("log linux#comment about linux") << QStringLiteral("linux") << QStringLiteral("log") << QString()
                                     << QString() << true;

    QTest::newRow("validLineCategoriesInfo") << QStringLiteral("log linux [INFO]") << QStringLiteral("linux") << QStringLiteral("log") << QStringLiteral("INFO")
                                             << QString() << true;
    QTest::newRow("validLineCategoriesInfo2") << QStringLiteral("log linux [INFO]    ") << QStringLiteral("linux") << QStringLiteral("log")
                                              << QStringLiteral("INFO") << QString() << true;
    QTest::newRow("validLineCategoriesInfo3") << QStringLiteral("log linux      [INFO]    ") << QStringLiteral("linux") << QStringLiteral("log")
                                              << QStringLiteral("INFO") << QString() << true;

    QTest::newRow("validLineCategoriesDEBUG") << QStringLiteral("log linux [DEBUG]") << QStringLiteral("linux") << QStringLiteral("log")
                                              << QStringLiteral("DEBUG") << QString() << true;
    QTest::newRow("validLineCategoriesDEBUG2") << QStringLiteral("log linux [DEBUG]    ") << QStringLiteral("linux") << QStringLiteral("log")
                                               << QStringLiteral("DEBUG") << QString() << true;
    QTest::newRow("validLineCategoriesDEBUG3") << QStringLiteral("log linux      [DEBUG]    ") << QStringLiteral("linux") << QStringLiteral("log")
                                               << QStringLiteral("DEBUG") << QString() << true;

    QTest::newRow("validLineCategoriesCRITICAL") << QStringLiteral("log linux [CRITICAL]") << QStringLiteral("linux") << QStringLiteral("log")
                                                 << QStringLiteral("CRITICAL") << QString() << true;
    QTest::newRow("validLineCategoriesCRITICAL2") << QStringLiteral("log linux [CRITICAL]    ") << QStringLiteral("linux") << QStringLiteral("log")
                                                  << QStringLiteral("CRITICAL") << QString() << true;
    QTest::newRow("validLineCategoriesCRITICAL3") << QStringLiteral("log linux      [CRITICAL]    ") << QStringLiteral("linux") << QStringLiteral("log")
                                                  << QStringLiteral("CRITICAL") << QString() << true;

    // New Format
    QTest::newRow("validLineCategoriesWarning-newformat") << QStringLiteral("log linux DEFAULT_SEVERITY [WARNING]") << QStringLiteral("linux")
                                                          << QStringLiteral("log") << QStringLiteral("WARNING") << QString() << true;
    QTest::newRow("validLineCategoriesWarning-newformat2") << QStringLiteral("log linux DEFAULT_SEVERITY [WARNING]    ") << QStringLiteral("linux")
                                                           << QStringLiteral("log") << QStringLiteral("WARNING") << QString() << true;
    QTest::newRow("validLineCategoriesWarning-newformat3") << QStringLiteral("log linux  DEFAULT_SEVERITY     [WARNING]    ") << QStringLiteral("linux")
                                                           << QStringLiteral("log") << QStringLiteral("WARNING") << QString() << true;
    QTest::newRow("validLineBadCategories-newformat") << QStringLiteral("log linux   DEFAULT_SEVERITY    [FOO]    ")
                                                      << QStringLiteral("linux DEFAULT_SEVERITY [FOO]") << QStringLiteral("log") << QString() << QString()
                                                      << true;
    QTest::newRow("linewithcomment-newformat") << QStringLiteral("log linux#comment about linux") << QStringLiteral("linux") << QStringLiteral("log")
                                               << QString() << QString() << true;

    QTest::newRow("validLineCategoriesInfo-newformat") << QStringLiteral("log linux DEFAULT_SEVERITY [INFO]") << QStringLiteral("linux")
                                                       << QStringLiteral("log") << QStringLiteral("INFO") << QString() << true;
    QTest::newRow("validLineCategoriesInfo-newformat2") << QStringLiteral("log linux DEFAULT_SEVERITY [INFO]    ") << QStringLiteral("linux")
                                                        << QStringLiteral("log") << QStringLiteral("INFO") << QString() << true;
    QTest::newRow("validLineCategoriesInfo-newformat3") << QStringLiteral("log linux   DEFAULT_SEVERITY    [INFO]    ") << QStringLiteral("linux")
                                                        << QStringLiteral("log") << QStringLiteral("INFO") << QString() << true;

    QTest::newRow("validLineCategoriesDEBUG-newformat") << QStringLiteral("log linux DEFAULT_SEVERITY [DEBUG]") << QStringLiteral("linux")
                                                        << QStringLiteral("log") << QStringLiteral("DEBUG") << QString() << true;
    QTest::newRow("validLineCategoriesDEBUG-newformat2") << QStringLiteral("log linux DEFAULT_SEVERITY [DEBUG]    ") << QStringLiteral("linux")
                                                         << QStringLiteral("log") << QStringLiteral("DEBUG") << QString() << true;
    QTest::newRow("validLineCategoriesDEBUG-newformat3") << QStringLiteral("log linux   DEFAULT_SEVERITY    [DEBUG]    ") << QStringLiteral("linux")
                                                         << QStringLiteral("log") << QStringLiteral("DEBUG") << QString() << true;

    QTest::newRow("validLineCategoriesCRITICAL-newformat") << QStringLiteral("log linux DEFAULT_SEVERITY [CRITICAL]") << QStringLiteral("linux")
                                                           << QStringLiteral("log") << QStringLiteral("CRITICAL") << QString() << true;
    QTest::newRow("validLineCategoriesCRITICAL-newformat2") << QStringLiteral("log linux DEFAULT_SEVERITY [CRITICAL]    ") << QStringLiteral("linux")
                                                            << QStringLiteral("log") << QStringLiteral("CRITICAL") << QString() << true;
    QTest::newRow("validLineCategoriesCRITICAL-newformat3") << QStringLiteral("log linux  DEFAULT_SEVERITY     [CRITICAL]    ") << QStringLiteral("linux")
                                                            << QStringLiteral("log") << QStringLiteral("CRITICAL") << QString() << true;

    // Identifier
    QTest::newRow("validLineIdentifier1") << QStringLiteral("log linux IDENTIFIER [foo]") << QStringLiteral("linux") << QStringLiteral("log") << QString()
                                          << QStringLiteral("foo") << true;
    QTest::newRow("validLineIdentifier2") << QStringLiteral("log linux DEFAULT_SEVERITY     [CRITICAL] IDENTIFIER [foo]") << QStringLiteral("linux")
                                          << QStringLiteral("log") << QStringLiteral("CRITICAL") << QStringLiteral("foo") << true;
    QTest::newRow("validLineIdentifier3") << QStringLiteral("log linux fli DEFAULT_SEVERITY     [INFO] IDENTIFIER [bla;bli;ss]") << QStringLiteral("linux fli")
                                          << QStringLiteral("log") << QStringLiteral("INFO") << QStringLiteral("bla;bli;ss") << true;
    QTest::newRow("validLineIdentifier4") << QStringLiteral("log linux (fli) DEFAULT_SEVERITY     [INFO] IDENTIFIER [bla;bli;ss]")
                                          << QStringLiteral("linux (fli)") << QStringLiteral("log") << QStringLiteral("INFO") << QStringLiteral("bla;bli;ss")
                                          << true;
}

void KDebugSettingUtilTest::shouldParseKdeLoggingLine()
{
    QFETCH(QString, input);
    QFETCH(QString, description);
    QFETCH(QString, logname);
    QFETCH(QString, defaultSeverity);
    QFETCH(QString, identifier);
    QFETCH(bool, valid);
    KdeLoggingCategory result;
    result.description = description;
    result.categoryName = logname;
    result.defaultSeverity = defaultSeverity;
    result.identifierName = identifier;
    const KdeLoggingCategory cat = KDebugSettingsUtil::parseLineKdeLoggingCategory(input, QString());
    if (cat != result) {
        qDebug() << "Generated category " << cat;
        qDebug() << "Expected category: " << result;
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
    QTest::newRow("empty") << QString() << QString() << KDebugSettingsUtil::LineLoggingQtCategory::Unknown << false << false;
    QTest::newRow("valid") << QStringLiteral("toto=true") << QStringLiteral("toto") << KDebugSettingsUtil::LineLoggingQtCategory::All << true << true;
    QTest::newRow("validdisabled") << QStringLiteral("toto=false") << QStringLiteral("toto") << KDebugSettingsUtil::LineLoggingQtCategory::All << false << true;

    QTest::newRow("validdisabledwithtypewarning") << QStringLiteral("toto.warning=false") << QStringLiteral("toto")
                                                  << KDebugSettingsUtil::LineLoggingQtCategory::Warning << false << true;
    QTest::newRow("validenabledwithtypewarning") << QStringLiteral("toto.warning=true") << QStringLiteral("toto")
                                                 << KDebugSettingsUtil::LineLoggingQtCategory::Warning << true << true;

    QTest::newRow("validdisabledwithtypecritical") << QStringLiteral("toto.critical=false") << QStringLiteral("toto")
                                                   << KDebugSettingsUtil::LineLoggingQtCategory::Critical << false << true;
    QTest::newRow("validenabledwithtypecritical") << QStringLiteral("toto.critical=true") << QStringLiteral("toto")
                                                  << KDebugSettingsUtil::LineLoggingQtCategory::Critical << true << true;

    QTest::newRow("validdisabledwithtypedebug") << QStringLiteral("toto.debug=false") << QStringLiteral("toto")
                                                << KDebugSettingsUtil::LineLoggingQtCategory::Debug << false << true;
    QTest::newRow("validenabledwithtypedebug") << QStringLiteral("toto.debug=true") << QStringLiteral("toto")
                                               << KDebugSettingsUtil::LineLoggingQtCategory::Debug << true << true;

    QTest::newRow("invalid") << QStringLiteral("dd") << QString() << KDebugSettingsUtil::LineLoggingQtCategory::Unknown << false << false;
    QTest::newRow("invalidWithoutEnabledDisabled") << QStringLiteral("dd=") << QStringLiteral("dd") << KDebugSettingsUtil::LineLoggingQtCategory::All << false
                                                   << true;
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
    QTest::newRow("unknown") << QStringLiteral("foo") << LoggingCategory::LoggingType::Info;
}

void KDebugSettingUtilTest::shouldConvertCategoryTypeFromString()
{
    QFETCH(QString, input);
    QFETCH(LoggingCategory::LoggingType, loggingType);
    QCOMPARE(KDebugSettingsUtil::convertCategoryTypeFromString(input), loggingType);
}

QTEST_GUILESS_MAIN(KDebugSettingUtilTest)
