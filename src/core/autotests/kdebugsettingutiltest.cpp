/*
    SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdebugsettingutiltest.h"
using namespace Qt::Literals::StringLiterals;

#include "kdebugsettingsutil.h"
#include <QDebug>
#include <QTest>

QTEST_GUILESS_MAIN(KDebugSettingUtilTest)

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

    QTest::newRow("validLine") << u"log linux"_s << u"linux"_s << u"log"_s << QString() << QString() << true;
    QTest::newRow("validLinewithspace") << u" log linux  "_s << u"linux"_s << u"log"_s << QString() << QString() << true;
    QTest::newRow("comment") << u"#log linux  "_s << QString() << QString() << QString() << QString() << false;
    QTest::newRow("commentWithSpace") << u"   #log linux  "_s << QString() << QString() << QString() << QString() << false;
    QTest::newRow("badline") << u"log"_s << QString() << QString() << QString() << QString() << false;
    QTest::newRow("comment-2") << u"#log linux"_s << QString() << QString() << QString() << QString() << false;
    QTest::newRow("validLineWithParentheses") << u"log linux (foo)"_s << u"linux (foo)"_s << u"log"_s << QString() << QString() << true;

    QTest::newRow("validLineWithParenthesesAndCategories")
        << u"log linux (foo) [WARNING]"_s << u"linux (foo)"_s << u"log"_s << u"WARNING"_s << QString() << true;

    QTest::newRow("validLineCategoriesWarning") << u"log linux [WARNING]"_s << u"linux"_s << u"log"_s << u"WARNING"_s << QString() << true;
    QTest::newRow("validLineCategoriesWarning2") << u"log linux [WARNING]    "_s << u"linux"_s << u"log"_s << u"WARNING"_s << QString() << true;
    QTest::newRow("validLineCategoriesWarning3") << u"log linux      [WARNING]    "_s << u"linux"_s << u"log"_s << u"WARNING"_s << QString() << true;
    QTest::newRow("validLineBadCategories") << u"log linux      [FOO]    "_s << u"linux [FOO]"_s << u"log"_s << QString() << QString() << true;
    QTest::newRow("linewithcomment") << u"log linux#comment about linux"_s << u"linux"_s << u"log"_s << QString() << QString() << true;

    QTest::newRow("validLineCategoriesInfo") << u"log linux [INFO]"_s << u"linux"_s << u"log"_s << u"INFO"_s << QString() << true;
    QTest::newRow("validLineCategoriesInfo2") << u"log linux [INFO]    "_s << u"linux"_s << u"log"_s << u"INFO"_s << QString() << true;
    QTest::newRow("validLineCategoriesInfo3") << u"log linux      [INFO]    "_s << u"linux"_s << u"log"_s << u"INFO"_s << QString() << true;

    QTest::newRow("validLineCategoriesDEBUG") << u"log linux [DEBUG]"_s << u"linux"_s << u"log"_s << u"DEBUG"_s << QString() << true;
    QTest::newRow("validLineCategoriesDEBUG2") << u"log linux [DEBUG]    "_s << u"linux"_s << u"log"_s << u"DEBUG"_s << QString() << true;
    QTest::newRow("validLineCategoriesDEBUG3") << u"log linux      [DEBUG]    "_s << u"linux"_s << u"log"_s << u"DEBUG"_s << QString() << true;

    QTest::newRow("validLineCategoriesCRITICAL") << u"log linux [CRITICAL]"_s << u"linux"_s << u"log"_s << u"CRITICAL"_s << QString() << true;
    QTest::newRow("validLineCategoriesCRITICAL2") << u"log linux [CRITICAL]    "_s << u"linux"_s << u"log"_s << u"CRITICAL"_s << QString() << true;
    QTest::newRow("validLineCategoriesCRITICAL3") << u"log linux      [CRITICAL]    "_s << u"linux"_s << u"log"_s << u"CRITICAL"_s << QString() << true;

    // New Format
    QTest::newRow("validLineCategoriesWarning-newformat")
        << u"log linux DEFAULT_SEVERITY [WARNING]"_s << u"linux"_s << u"log"_s << u"WARNING"_s << QString() << true;
    QTest::newRow("validLineCategoriesWarning-newformat2")
        << u"log linux DEFAULT_SEVERITY [WARNING]    "_s << u"linux"_s << u"log"_s << u"WARNING"_s << QString() << true;
    QTest::newRow("validLineCategoriesWarning-newformat3")
        << u"log linux  DEFAULT_SEVERITY     [WARNING]    "_s << u"linux"_s << u"log"_s << u"WARNING"_s << QString() << true;
    QTest::newRow("validLineBadCategories-newformat") << u"log linux   DEFAULT_SEVERITY    [FOO]    "_s << u"linux DEFAULT_SEVERITY [FOO]"_s << u"log"_s
                                                      << QString() << QString() << true;
    QTest::newRow("linewithcomment-newformat") << u"log linux#comment about linux"_s << u"linux"_s << u"log"_s << QString() << QString() << true;

    QTest::newRow("validLineCategoriesInfo-newformat") << u"log linux DEFAULT_SEVERITY [INFO]"_s << u"linux"_s << u"log"_s << u"INFO"_s << QString() << true;
    QTest::newRow("validLineCategoriesInfo-newformat2")
        << u"log linux DEFAULT_SEVERITY [INFO]    "_s << u"linux"_s << u"log"_s << u"INFO"_s << QString() << true;
    QTest::newRow("validLineCategoriesInfo-newformat3")
        << u"log linux   DEFAULT_SEVERITY    [INFO]    "_s << u"linux"_s << u"log"_s << u"INFO"_s << QString() << true;

    QTest::newRow("validLineCategoriesDEBUG-newformat") << u"log linux DEFAULT_SEVERITY [DEBUG]"_s << u"linux"_s << u"log"_s << u"DEBUG"_s << QString() << true;
    QTest::newRow("validLineCategoriesDEBUG-newformat2")
        << u"log linux DEFAULT_SEVERITY [DEBUG]    "_s << u"linux"_s << u"log"_s << u"DEBUG"_s << QString() << true;
    QTest::newRow("validLineCategoriesDEBUG-newformat3")
        << u"log linux   DEFAULT_SEVERITY    [DEBUG]    "_s << u"linux"_s << u"log"_s << u"DEBUG"_s << QString() << true;

    QTest::newRow("validLineCategoriesCRITICAL-newformat")
        << u"log linux DEFAULT_SEVERITY [CRITICAL]"_s << u"linux"_s << u"log"_s << u"CRITICAL"_s << QString() << true;
    QTest::newRow("validLineCategoriesCRITICAL-newformat2")
        << u"log linux DEFAULT_SEVERITY [CRITICAL]    "_s << u"linux"_s << u"log"_s << u"CRITICAL"_s << QString() << true;
    QTest::newRow("validLineCategoriesCRITICAL-newformat3")
        << u"log linux  DEFAULT_SEVERITY     [CRITICAL]    "_s << u"linux"_s << u"log"_s << u"CRITICAL"_s << QString() << true;

    // Identifier
    QTest::newRow("validLineIdentifier1") << u"log linux IDENTIFIER [foo]"_s << u"linux"_s << u"log"_s << QString() << u"foo"_s << true;
    QTest::newRow("validLineIdentifier2") << u"log linux DEFAULT_SEVERITY     [CRITICAL] IDENTIFIER [foo]"_s << u"linux"_s << u"log"_s << u"CRITICAL"_s
                                          << u"foo"_s << true;
    QTest::newRow("validLineIdentifier3") << u"log linux fli DEFAULT_SEVERITY     [INFO] IDENTIFIER [bla;bli;ss]"_s << u"linux fli"_s << u"log"_s << u"INFO"_s
                                          << u"bla;bli;ss"_s << true;
    QTest::newRow("validLineIdentifier4") << u"log linux (fli) DEFAULT_SEVERITY     [INFO] IDENTIFIER [bla;bli;ss]"_s << u"linux (fli)"_s << u"log"_s
                                          << u"INFO"_s << u"bla;bli;ss"_s << true;
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
    QTest::newRow("valid") << u"toto=true"_s << u"toto"_s << KDebugSettingsUtil::LineLoggingQtCategory::All << true << true;
    QTest::newRow("validdisabled") << u"toto=false"_s << u"toto"_s << KDebugSettingsUtil::LineLoggingQtCategory::All << false << true;

    QTest::newRow("validdisabledwithtypewarning") << u"toto.warning=false"_s << u"toto"_s << KDebugSettingsUtil::LineLoggingQtCategory::Warning << false
                                                  << true;
    QTest::newRow("validenabledwithtypewarning") << u"toto.warning=true"_s << u"toto"_s << KDebugSettingsUtil::LineLoggingQtCategory::Warning << true << true;

    QTest::newRow("validdisabledwithtypecritical") << u"toto.critical=false"_s << u"toto"_s << KDebugSettingsUtil::LineLoggingQtCategory::Critical << false
                                                   << true;
    QTest::newRow("validenabledwithtypecritical") << u"toto.critical=true"_s << u"toto"_s << KDebugSettingsUtil::LineLoggingQtCategory::Critical << true
                                                  << true;

    QTest::newRow("validdisabledwithtypedebug") << u"toto.debug=false"_s << u"toto"_s << KDebugSettingsUtil::LineLoggingQtCategory::Debug << false << true;
    QTest::newRow("validenabledwithtypedebug") << u"toto.debug=true"_s << u"toto"_s << KDebugSettingsUtil::LineLoggingQtCategory::Debug << true << true;

    QTest::newRow("invalid") << u"dd"_s << QString() << KDebugSettingsUtil::LineLoggingQtCategory::Unknown << false << false;
    QTest::newRow("invalidWithoutEnabledDisabled") << u"dd="_s << u"dd"_s << KDebugSettingsUtil::LineLoggingQtCategory::All << false << true;
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
    QTest::newRow("empty") << u"empty.categories"_s << 0;
    QTest::newRow("correctlist") << u"correct.categories"_s << 5;
    QTest::newRow("withduplicate") << u"duplicates.categories"_s << 5;
    QTest::newRow("withcomment") << u"comments.categories"_s << 6;
}

void KDebugSettingUtilTest::shouldReadLoadKdeCategories()
{
    QFETCH(QString, filename);
    QFETCH(int, numberofcategories);
    const QString path = QString(QLatin1StringView(KDEBUGSETTINGS_DATA_DIR) + u'/' + filename);
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
    QTest::newRow("empty") << u"empty.renamecategories"_s << 0;
    QTest::newRow("2renamed") << u"tworename.renamecategories"_s << 2;
    QTest::newRow("withnewline") << u"newline.renamecategories"_s << 2;
}

void KDebugSettingUtilTest::shouldReadRenameCategories()
{
    QFETCH(QString, filename);
    QFETCH(int, numberofrenamecategories);
    const QString path = QString(QLatin1StringView(KDEBUGSETTINGS_DATA_DIR) + u'/' + filename);
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
    QTest::newRow("WARNING") << u"WARNING"_s << LoggingCategory::LoggingType::Warning;
    QTest::newRow("Info") << u"INFO"_s << LoggingCategory::LoggingType::Info;
    QTest::newRow("Debug") << u"DEBUG"_s << LoggingCategory::LoggingType::Debug;
    QTest::newRow("Critical") << u"CRITICAL"_s << LoggingCategory::LoggingType::Critical;
    QTest::newRow("unknown") << u"foo"_s << LoggingCategory::LoggingType::Info;
}

void KDebugSettingUtilTest::shouldConvertCategoryTypeFromString()
{
    QFETCH(QString, input);
    QFETCH(LoggingCategory::LoggingType, loggingType);
    QCOMPARE(KDebugSettingsUtil::convertCategoryTypeFromString(input), loggingType);
}

#include "moc_kdebugsettingutiltest.cpp"
