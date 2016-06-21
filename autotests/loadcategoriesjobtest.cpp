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
    QTest::addColumn<KdeLoggingCategory::List>("listKdeLoggingCategories");
    QTest::addColumn<bool>("foundoverriderules");
    QTest::newRow("empty") << QString(QLatin1String(KDEBUGSETTINGS_DATA_DIR) + QLatin1Char('/') + QStringLiteral("emptyrulefiles.ini")) << KdeLoggingCategory::List() << false;
}

void LoadCategoriesJobTest::shouldReadRules()
{
    QFETCH(QString, filename);
    QFETCH(KdeLoggingCategory::List, listKdeLoggingCategories);
    QFETCH(bool, foundoverriderules);
    QFile file(filename);
    QVERIFY(file.exists());
    LoadCategoriesJob job;
    job.setFileName(filename);
    QVERIFY(job.customCategories().isEmpty());
    QCOMPARE(job.foundOverrideRule(), foundoverriderules);
    QVERIFY(job.qtKdeCategories().isEmpty());
}


QTEST_MAIN(LoadCategoriesJobTest)
