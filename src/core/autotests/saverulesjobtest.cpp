/*
    SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "saverulesjobtest.h"

#include "jobs/loadcategoriesjob.h"
#include "jobs/saverulesjob.h"

#include <QDir>
#include <QFile>
#include <QTest>

QTEST_GUILESS_MAIN(SaveRulesJobTest)

using namespace Qt::Literals::StringLiterals;
// QIODevice::Text is used everywhere a file is read back so that the comparison stays
// insensitive to the end of line convention: SaveRulesJob writes the file in text mode,
// so it contains CRLF on Windows while generateRules() always returns LF.
static QString readTextFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Unable to open" << fileName << file.errorString();
        return {};
    }
    return QString::fromUtf8(file.readAll());
}

static void compareWithReference(const QString &name, const QString &generated)
{
    const QString refFile = QLatin1StringView(KDEBUGSETTINGS_DATA_DIR) + u'/' + name + u".ref"_s;
    const QString reference = readTextFile(refFile);
    QVERIFY2(!reference.isEmpty(), qPrintable(u"Unable to read reference file %1"_s.arg(refFile)));
    QCOMPARE(generated, reference);
}

SaveRulesJobTest::SaveRulesJobTest(QObject *parent)
    : QObject(parent)
{
}

void SaveRulesJobTest::shouldSaveLoadRules_data()
{
    QTest::addColumn<QString>("filename");
    QTest::newRow("oneelementwarning.ini") << u"oneelementwarning"_s;
    QTest::newRow("oneelementall.ini") << u"oneelementall"_s;
    QTest::newRow("oneelementinfo.ini") << u"oneelementinfo"_s;
    QTest::newRow("oneelementonelineoff.ini") << u"oneelementonelineoff"_s;
    QTest::newRow("oneelementonelinecritical.ini") << u"oneelementonelinecritical"_s;
    QTest::newRow("star.ini") << u"star"_s;
    QTest::newRow("star1.ini") << u"star1"_s;
}

void SaveRulesJobTest::shouldSaveLoadRules()
{
    QFETCH(QString, filename);
    LoadCategoriesJob job;
    job.setFileName(QStringLiteral(KDEBUGSETTINGS_DATA_DIR) + u'/' + filename + u".ini"_s);
    job.start();

    SaveRulesJob saveJob;
    saveJob.setListCustom(job.customCategories());
    saveJob.setListKde(job.qtKdeCategories());
    compareWithReference(filename, saveJob.generateRules());
}

void SaveRulesJobTest::shouldSaveKdeRulesAsExplicitSeverities()
{
    // A KDE category defines a severity threshold: it must be saved with all the
    // severities written explicitly (LoggingCategory::createRule()) and not as a
    // single line custom rule, otherwise "Off" would not be saved at all and the
    // other types would leave the remaining severities untouched.
    // KDEApplicationLoggingCategoryProxyModel::rules() always clears "enabled" as
    // the severity is carried by the type alone, so reproduce that here too.
    LoggingCategory::List kdeCategories;
    const QList<LoggingCategory::LoggingType> types =
        {LoggingCategory::All, LoggingCategory::Info, LoggingCategory::Warning, LoggingCategory::Debug, LoggingCategory::Critical, LoggingCategory::Off};
    for (const LoggingCategory::LoggingType type : types) {
        LoggingCategory category;
        category.categoryName = u"org.kde.category%1"_s.arg(static_cast<int>(type));
        category.loggingType = type;
        category.enabled = false;
        kdeCategories.append(category);
    }

    SaveRulesJob saveJob;
    saveJob.setListKde(kdeCategories);
    compareWithReference(u"kderules"_s, saveJob.generateRules());
}

void SaveRulesJobTest::shouldWriteGeneratedRulesToFile()
{
    // generateRules() is covered by the tests above: verify here that start() stores
    // exactly that content on disk.
    const QString filename = u"oneelementwarning"_s;
    LoadCategoriesJob job;
    job.setFileName(QStringLiteral(KDEBUGSETTINGS_DATA_DIR) + u'/' + filename + u".ini"_s);
    job.start();

    SaveRulesJob saveJob;
    saveJob.setListCustom(job.customCategories());
    saveJob.setListKde(job.qtKdeCategories());

    QVERIFY(QDir().mkpath(QStringLiteral(KDEBUGSETTINGS_BINARY_DATA_DIR)));
    const QString generatedFile = QLatin1StringView(KDEBUGSETTINGS_BINARY_DATA_DIR) + u'/' + filename + u"-generated.ref"_s;
    saveJob.setFileName(generatedFile);
    QVERIFY(saveJob.start());

    QCOMPARE(readTextFile(generatedFile), saveJob.generateRules());
}

#include "moc_saverulesjobtest.cpp"
