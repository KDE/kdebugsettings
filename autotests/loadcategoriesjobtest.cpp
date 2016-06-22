/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

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

#include "loadcategoriesjobtest.h"
#include "../src/loadcategoriesjob.h"
#include "../src/kdebugsettingsutil.h"

#include <QTest>
#include <QFile>
#include <QDebug>

LoadCategoriesJobTest::LoadCategoriesJobTest(QObject *parent)
    : QObject(parent)
{

}

LoadCategoriesJobTest::~LoadCategoriesJobTest()
{

}

void LoadCategoriesJobTest::shouldHaveDefaultValue()
{
    LoadCategoriesJob job;
    QVERIFY(job.customCategories().isEmpty());
    QVERIFY(!job.foundOverrideRule());
    QVERIFY(job.qtKdeCategories().isEmpty());
}

void LoadCategoriesJobTest::shouldReadRules_data()
{
    QTest::addColumn<QString>("filename");
    QTest::addColumn<QString>("filenamelistKdeLoggingCategories");
    QTest::addColumn<bool>("foundoverriderules");
    QTest::addColumn<LoggingCategory::List>("customcategories");
    QTest::addColumn<LoggingCategory::List>("qtkdecategories");
    QTest::newRow("empty") << QStringLiteral("emptyrulefiles.ini") << QString() << false << LoggingCategory::List() << LoggingCategory::List();
    QTest::newRow("commentedlines") << QStringLiteral("commentedrulefiles.ini") << QString() << false << LoggingCategory::List() << LoggingCategory::List();
    QTest::newRow("rulesbeforesection") << QStringLiteral("rulebeforerulessectionfiles.ini") << QString() << false << LoggingCategory::List() << LoggingCategory::List();
}

void LoadCategoriesJobTest::shouldReadRules()
{
    QFETCH(QString, filename);
    QFETCH(QString, filenamelistKdeLoggingCategories);
    QFETCH(bool, foundoverriderules);
    QFETCH(LoggingCategory::List, customcategories);
    QFETCH(LoggingCategory::List, qtkdecategories);
    LoadCategoriesJob job;
    KdeLoggingCategory::List listKdeLoggingCategories;
    if (!filenamelistKdeLoggingCategories.isEmpty()) {
        const QString kdeLoggingCategoriesPath = QString(QLatin1String(KDEBUGSETTINGS_DATA_DIR) + QLatin1Char('/') + filenamelistKdeLoggingCategories);
        KDebugSettingsUtil::readLoggingCategories(kdeLoggingCategoriesPath, listKdeLoggingCategories, true);
    }

    const QString path = QString(QLatin1String(KDEBUGSETTINGS_DATA_DIR) + QLatin1Char('/') + filename);
    QFile file(path);
    QVERIFY(file.exists());
    job.setFileName(path);
    job.setCategories(listKdeLoggingCategories);
    job.start();

    qDebug() << "job.customCategories()"<<job.customCategories().count();
    QCOMPARE(job.customCategories(), customcategories);
    QCOMPARE(job.foundOverrideRule(), foundoverriderules);
    QCOMPARE(job.qtKdeCategories(), qtkdecategories);
}


QTEST_MAIN(LoadCategoriesJobTest)
