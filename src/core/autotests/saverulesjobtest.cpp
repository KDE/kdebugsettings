/*
    SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "saverulesjobtest.h"
#include "jobs/loadcategoriesjob.h"
#include "jobs/saverulesjob.h"

#include <QProcess>
#include <QTest>

QTEST_GUILESS_MAIN(SaveRulesJobTest)

void compareFile(const QString &name)
{
    const QString refFile = QLatin1String(KDEBUGSETTINGS_DATA_DIR) + QLatin1Char('/') + name + QStringLiteral(".ref");
    const QString generatedFile = QLatin1String(KDEBUGSETTINGS_BINARY_DATA_DIR) + QLatin1Char('/') + name + QStringLiteral("-generated.ref");
    QProcess proc;

#ifdef _WIN32
    QStringList args = QStringList() << QStringLiteral("Compare-Object") << QString(QStringLiteral("(Get-Content %1)")).arg(refFile)
                                     << QString(QStringLiteral("(Get-Content %1)")).arg(generatedFile);

    proc.start(QStringLiteral("powershell"), args);
    QVERIFY(proc.waitForFinished());

    auto pStdOut = proc.readAllStandardOutput();
    if (pStdOut.size()) {
        qDebug() << "Files are different, diff output message:\n" << pStdOut.toStdString().c_str();
    }

    QCOMPARE(pStdOut.size(), 0);
#else
    // compare to reference file
    const QStringList args = QStringList() << QStringLiteral("-u") << refFile << generatedFile;

    proc.setProcessChannelMode(QProcess::ForwardedChannels);
    proc.start(QStringLiteral("diff"), args);
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
    QTest::newRow("oneelementwarning.ini") << QStringLiteral("oneelementwarning");
    QTest::newRow("oneelementall.ini") << QStringLiteral("oneelementall");
    QTest::newRow("oneelementinfo.ini") << QStringLiteral("oneelementinfo");
    QTest::newRow("oneelementonelineoff.ini") << QStringLiteral("oneelementonelineoff");
    QTest::newRow("oneelementonelinecritical.ini") << QStringLiteral("oneelementonelinecritical");
}

void SaveRulesJobTest::shouldSaveLoadRules()
{
    QFETCH(QString, filename);
    LoadCategoriesJob job;
    job.setFileName(QLatin1String(KDEBUGSETTINGS_DATA_DIR) + QLatin1Char('/') + filename + QStringLiteral(".ini"));
    job.start();

    const LoggingCategory::List customCategories = job.customCategories();

    const LoggingCategory::List qtKdeCategories = job.qtKdeCategories();

    SaveRulesJob saveJob;
    QDir().mkpath(QLatin1String(KDEBUGSETTINGS_BINARY_DATA_DIR));
    saveJob.setFileName(QLatin1String(KDEBUGSETTINGS_BINARY_DATA_DIR) + QLatin1Char('/') + filename + QStringLiteral("-generated.ref"));
    qDebug() << " save " << saveJob.fileName();
    saveJob.setListCustom(customCategories);
    saveJob.setListKde(qtKdeCategories);
    QVERIFY(saveJob.start());
    compareFile(filename);
}
