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

#define DEBUG_RESULT 1

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

    LoggingCategory::List qtKdeCategories;
    LoggingCategory tmp;
    tmp.description = QStringLiteral("KPasswdServer (KIO)");
    tmp.logName = QStringLiteral("org.kde.kio.kpasswdserver");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KUriFilter IKWS (KIO)");
    tmp.logName = QStringLiteral("org.kde.kurifilter-ikws");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KUriFilter Shorturi (KIO)");
    tmp.logName = QStringLiteral("org.kde.kurifilter-shorturi");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("BluezQt");
    tmp.logName = QStringLiteral("BluezQt");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KAuth");
    tmp.logName = QStringLiteral("kf5.kauth");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    QTest::newRow("emptywithlistkdeloggingcategories") << QStringLiteral("rulebeforerulessectionfiles.ini") << QStringLiteral("correct.categories") << false
            << LoggingCategory::List()
            << qtKdeCategories;

    qtKdeCategories.clear();
    tmp.description = QStringLiteral("KPasswdServer (KIO)");
    tmp.logName = QStringLiteral("org.kde.kio.kpasswdserver");
    tmp.loggingType = LoggingCategory::Off;
    tmp.enabled = false;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KUriFilter IKWS (KIO)");
    tmp.logName = QStringLiteral("org.kde.kurifilter-ikws");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KUriFilter Shorturi (KIO)");
    tmp.logName = QStringLiteral("org.kde.kurifilter-shorturi");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("BluezQt");
    tmp.logName = QStringLiteral("BluezQt");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KAuth");
    tmp.logName = QStringLiteral("kf5.kauth");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    QTest::newRow("oneelementoff") << QStringLiteral("oneelementoff.ini") << QStringLiteral("correct.categories") << false
                                   << LoggingCategory::List()
                                   << qtKdeCategories;

    QTest::newRow("oneelementonelineoff") << QStringLiteral("oneelementonelineoff.ini") << QStringLiteral("correct.categories") << false
                                          << LoggingCategory::List()
                                          << qtKdeCategories;

    qtKdeCategories.clear();
    tmp.description = QStringLiteral("KPasswdServer (KIO)");
    tmp.logName = QStringLiteral("org.kde.kio.kpasswdserver");
    tmp.loggingType = LoggingCategory::All;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KUriFilter IKWS (KIO)");
    tmp.logName = QStringLiteral("org.kde.kurifilter-ikws");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KUriFilter Shorturi (KIO)");
    tmp.logName = QStringLiteral("org.kde.kurifilter-shorturi");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("BluezQt");
    tmp.logName = QStringLiteral("BluezQt");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KAuth");
    tmp.logName = QStringLiteral("kf5.kauth");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    QTest::newRow("oneelementall") << QStringLiteral("oneelementall.ini") << QStringLiteral("correct.categories") << false
                                   << LoggingCategory::List()
                                   << qtKdeCategories;

    QTest::newRow("oneelementonelineall") << QStringLiteral("oneelementonelineall.ini") << QStringLiteral("correct.categories") << false
                                          << LoggingCategory::List()
                                          << qtKdeCategories;

    qtKdeCategories.clear();
    tmp.description = QStringLiteral("KPasswdServer (KIO)");
    tmp.logName = QStringLiteral("org.kde.kio.kpasswdserver");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KUriFilter IKWS (KIO)");
    tmp.logName = QStringLiteral("org.kde.kurifilter-ikws");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KUriFilter Shorturi (KIO)");
    tmp.logName = QStringLiteral("org.kde.kurifilter-shorturi");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("BluezQt");
    tmp.logName = QStringLiteral("BluezQt");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KAuth");
    tmp.logName = QStringLiteral("kf5.kauth");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    QTest::newRow("oneelementinfo") << QStringLiteral("oneelementinfo.ini") << QStringLiteral("correct.categories") << false
                                    << LoggingCategory::List()
                                    << qtKdeCategories;

    QTest::newRow("oneelementinfo") << QStringLiteral("oneelementinfobis.ini") << QStringLiteral("correct.categories") << false
                                    << LoggingCategory::List()
                                    << qtKdeCategories;

    qtKdeCategories.clear();
    tmp.description = QStringLiteral("KPasswdServer (KIO)");
    tmp.logName = QStringLiteral("org.kde.kio.kpasswdserver");
    tmp.loggingType = LoggingCategory::Warning;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KUriFilter IKWS (KIO)");
    tmp.logName = QStringLiteral("org.kde.kurifilter-ikws");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KUriFilter Shorturi (KIO)");
    tmp.logName = QStringLiteral("org.kde.kurifilter-shorturi");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("BluezQt");
    tmp.logName = QStringLiteral("BluezQt");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KAuth");
    tmp.logName = QStringLiteral("kf5.kauth");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    QTest::newRow("oneelementwarning") << QStringLiteral("oneelementwarning.ini") << QStringLiteral("correct.categories") << false
                                       << LoggingCategory::List()
                                       << qtKdeCategories;

    qtKdeCategories.clear();
    tmp.description = QStringLiteral("KPasswdServer (KIO)");
    tmp.logName = QStringLiteral("org.kde.kio.kpasswdserver");
    tmp.loggingType = LoggingCategory::Critical;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KUriFilter IKWS (KIO)");
    tmp.logName = QStringLiteral("org.kde.kurifilter-ikws");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KUriFilter Shorturi (KIO)");
    tmp.logName = QStringLiteral("org.kde.kurifilter-shorturi");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("BluezQt");
    tmp.logName = QStringLiteral("BluezQt");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KAuth");
    tmp.logName = QStringLiteral("kf5.kauth");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    QTest::newRow("oneelementcritical") << QStringLiteral("oneelementcritical.ini") << QStringLiteral("correct.categories") << false
                                        << LoggingCategory::List()
                                        << qtKdeCategories;

    QTest::newRow("oneelementonelinecritical") << QStringLiteral("oneelementonelinecritical.ini") << QStringLiteral("correct.categories") << false
            << LoggingCategory::List()
            << qtKdeCategories;
    QTest::newRow("oneelementtwolinecritical") << QStringLiteral("oneelementonelinecritical.ini") << QStringLiteral("correct.categories") << false
            << LoggingCategory::List()
            << qtKdeCategories;

    qtKdeCategories.clear();
    tmp.description = QStringLiteral("KPasswdServer (KIO)");
    tmp.logName = QStringLiteral("org.kde.kio.kpasswdserver");
    tmp.loggingType = LoggingCategory::Debug;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KUriFilter IKWS (KIO)");
    tmp.logName = QStringLiteral("org.kde.kurifilter-ikws");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KUriFilter Shorturi (KIO)");
    tmp.logName = QStringLiteral("org.kde.kurifilter-shorturi");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("BluezQt");
    tmp.logName = QStringLiteral("BluezQt");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    tmp.description = QStringLiteral("KAuth");
    tmp.logName = QStringLiteral("kf5.kauth");
    tmp.loggingType = LoggingCategory::Info;
    tmp.enabled = true;
    qtKdeCategories.append(tmp);

    QTest::newRow("oneelementdebug") << QStringLiteral("oneelementdebug.ini") << QStringLiteral("correct.categories") << false
                                     << LoggingCategory::List()
                                     << qtKdeCategories;

    // Test with extract elements
    LoggingCategory::List customCategories;
    LoggingCategory customTmp;
    customTmp.logName = QStringLiteral("toto");
    customTmp.loggingType = LoggingCategory::Critical;
    customTmp.enabled = true;
    customCategories.append(customTmp);

    QTest::newRow("oneelementdebugandanextract") << QStringLiteral("oneelementdebugandanextract.ini") << QStringLiteral("correct.categories") << false
            << customCategories
            << qtKdeCategories;

    // Test with extract elements
    customCategories.clear();
    customTmp.logName = QStringLiteral("toto");
    customTmp.loggingType = LoggingCategory::Critical;
    customTmp.enabled = false;
    customCategories.append(customTmp);

    QTest::newRow("oneelementdebugandanextractfalse") << QStringLiteral("oneelementdebugandanextractfalse.ini") << QStringLiteral("correct.categories") << false
            << customCategories
            << qtKdeCategories;

    //Test without categories
    qtKdeCategories.clear();
    customCategories.clear();
    customTmp.logName = QStringLiteral("toto");
    customTmp.loggingType = LoggingCategory::Warning;
    customTmp.enabled = false;
    customCategories.append(customTmp);
    customTmp.logName = QStringLiteral("toto");
    customTmp.loggingType = LoggingCategory::Debug;
    customTmp.enabled = false;
    customCategories.append(customTmp);

    customTmp.logName = QStringLiteral("toto");
    customTmp.loggingType = LoggingCategory::Info;
    customTmp.enabled = false;
    customCategories.append(customTmp);

    customTmp.logName = QStringLiteral("toto");
    customTmp.loggingType = LoggingCategory::Critical;
    customTmp.enabled = false;
    customCategories.append(customTmp);

    QTest::newRow("testwithoutcategories") << QStringLiteral("testwithoutcategories.ini") << QString() << false
            << customCategories
            << qtKdeCategories;


    qtKdeCategories.clear();
    customCategories.clear();
    customTmp.logName = QStringLiteral("toto");
    customTmp.loggingType = LoggingCategory::Warning;
    customTmp.enabled = false;
    customCategories.append(customTmp);
    QTest::newRow("testwithoutcategorieswarning") << QStringLiteral("testwithoutcategorieswarning.ini") << QString() << false
            << customCategories
            << qtKdeCategories;

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


#ifdef DEBUG_RESULT
    Q_FOREACH (const LoggingCategory &cat, job.customCategories()) {
        qDebug() << "customcategories cat." << cat.description << " logname" << cat.logName << " enabled " << cat.enabled << "type " << cat.loggingType;
    }

    qDebug() << "AFTER";
    Q_FOREACH (const LoggingCategory &cat, customcategories) {
        qDebug() << "customcategories cat." << cat.description << " logname" << cat.logName << " enabled " << cat.enabled << "type " << cat.loggingType;
    }
#endif
    QCOMPARE(job.customCategories().count(), customcategories.count());

    QCOMPARE(job.customCategories(), customcategories);

    QCOMPARE(job.foundOverrideRule(), foundoverriderules);


#ifdef DEBUG_RESULT
    Q_FOREACH (const LoggingCategory &cat, job.qtKdeCategories()) {
        qDebug() << "qtKdeCategories cat." << cat.description << " logname" << cat.logName << " enabled " << cat.enabled << "type " << cat.loggingType;
    }

    qDebug() << "AFTER";
    Q_FOREACH (const LoggingCategory &cat, qtkdecategories) {
        qDebug() << "qtKdeCategories cat." << cat.description << " logname" << cat.logName << " enabled " << cat.enabled << "type " << cat.loggingType;
    }
#endif
    QCOMPARE(job.qtKdeCategories().count(), qtkdecategories.count());
    QCOMPARE(job.qtKdeCategories(), qtkdecategories);
}

QTEST_MAIN(LoadCategoriesJobTest)
