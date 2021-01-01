/*
    SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "saverulesjobtest.h"
#include "../src/loadcategoriesjob.h"
#include "../src/saverulesjob.h"

#include <QProcess>
#include <QTest>

QTEST_GUILESS_MAIN(SaveRulesJobTest)

void compareFile(const QString &name)
{
    const QString refFile = QLatin1String(KDEBUGSETTINGS_DATA_DIR) + QLatin1Char('/') + name + QStringLiteral(".ref");
    const QString generatedFile = QLatin1String(KDEBUGSETTINGS_BINARY_DATA_DIR) + QLatin1Char('/') + name + QStringLiteral("-generated.ref");

    // compare to reference file
    QStringList args = QStringList()
                       << QStringLiteral("-u")
                       << refFile
                       << generatedFile;
    QProcess proc;
    proc.setProcessChannelMode(QProcess::ForwardedChannels);
    proc.start(QStringLiteral("diff"), args);
    QVERIFY(proc.waitForFinished());
    QCOMPARE(proc.exitCode(), 0);
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
