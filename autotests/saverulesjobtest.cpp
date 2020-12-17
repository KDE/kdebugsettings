/*
  Copyright (c) 2017-2020 Laurent Montel <montel@kde.org>

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
