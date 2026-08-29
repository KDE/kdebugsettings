/*
    SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "saverulesjobtest.h"

#include "jobs/loadcategoriesjob.h"
#include "jobs/saverulesjob.h"

#include <QDir>
#include <QProcess>
#include <QTest>

QTEST_GUILESS_MAIN(SaveRulesJobTest)

using namespace Qt::Literals::StringLiterals;
static void compareFile(const QString &name)
{
    const QString refFile = QLatin1StringView(KDEBUGSETTINGS_DATA_DIR) + u'/' + name + u".ref"_s;
    const QString generatedFile = QLatin1StringView(KDEBUGSETTINGS_BINARY_DATA_DIR) + u'/' + name + u"-generated.ref"_s;
    QProcess proc;

#ifdef _WIN32
    QStringList args = QStringList() << u"Compare-Object"_s << QString(u"(Get-Content %1)"_s).arg(refFile) << QString(u"(Get-Content %1)"_s).arg(generatedFile);

    proc.start(u"powershell"_s, args);
    QVERIFY(proc.waitForFinished());

    auto pStdOut = proc.readAllStandardOutput();
    if (pStdOut.size()) {
        qDebug() << "Files are different, diff output message:\n" << pStdOut.toStdString().c_str();
    }

    QCOMPARE(pStdOut.size(), 0);
#else
    // compare to reference file
    const QStringList args = QStringList() << u"-u"_s << refFile << generatedFile;

    proc.setProcessChannelMode(QProcess::ForwardedChannels);
    proc.start(u"diff"_s, args);
    QVERIFY(proc.waitForFinished());
    QCOMPARE(proc.exitCode(), 0);
#endif
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
}

void SaveRulesJobTest::shouldSaveLoadRules()
{
    QFETCH(QString, filename);
    LoadCategoriesJob job;
    job.setFileName(QStringLiteral(KDEBUGSETTINGS_DATA_DIR) + u'/' + filename + u".ini"_s);
    job.start();

    const LoggingCategory::List customCategories = job.customCategories();

    const LoggingCategory::List qtKdeCategories = job.qtKdeCategories();

    SaveRulesJob saveJob;
    QDir().mkpath(QStringLiteral(KDEBUGSETTINGS_BINARY_DATA_DIR));
    saveJob.setFileName(QLatin1StringView(KDEBUGSETTINGS_BINARY_DATA_DIR) + u'/' + filename + u"-generated.ref"_s);
    qDebug() << " save " << saveJob.fileName();
    saveJob.setListCustom(customCategories);
    saveJob.setListKde(qtKdeCategories);
    QVERIFY(saveJob.start());
    compareFile(filename);
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

    const QString filename = u"kderules"_s;
    SaveRulesJob saveJob;
    QDir().mkpath(QStringLiteral(KDEBUGSETTINGS_BINARY_DATA_DIR));
    saveJob.setFileName(QLatin1StringView(KDEBUGSETTINGS_BINARY_DATA_DIR) + u'/' + filename + u"-generated.ref"_s);
    saveJob.setListKde(kdeCategories);
    QVERIFY(saveJob.start());
    compareFile(filename);
}

#include "moc_saverulesjobtest.cpp"
