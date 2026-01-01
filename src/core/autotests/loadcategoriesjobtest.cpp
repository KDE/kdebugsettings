/*
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loadcategoriesjobtest.h"
using namespace Qt::Literals::StringLiterals;

#include "jobs/loadcategoriesjob.h"
#include "kdebugsettingsutil.h"

#include <QDebug>
#include <QFile>
#include <QTest>

LoadCategoriesJobTest::LoadCategoriesJobTest(QObject *parent)
    : QObject(parent)
{
}

LoadCategoriesJobTest::~LoadCategoriesJobTest() = default;

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
    QTest::newRow("empty") << u"emptyrulefiles.ini"_s << QString() << false << LoggingCategory::List() << LoggingCategory::List();
    QTest::newRow("commentedlines") << u"commentedrulefiles.ini"_s << QString() << false << LoggingCategory::List() << LoggingCategory::List();
    QTest::newRow("rulesbeforesection") << u"rulebeforerulessectionfiles.ini"_s << QString() << false << LoggingCategory::List() << LoggingCategory::List();

    const LoggingCategory ikwsInfo(u"KUriFilter IKWS (KIO)"_s, u"org.kde.kurifilter-ikws"_s, LoggingCategory::Info, QString(), true);
    const LoggingCategory shorturiInfo(u"KUriFilter Shorturi (KIO)"_s, u"org.kde.kurifilter-shorturi"_s, LoggingCategory::Info, QString(), true);
    const LoggingCategory bluezQtInfo(u"BluezQt"_s, u"BluezQt"_s, LoggingCategory::Info, QString(), true);
    const LoggingCategory kauthInfo(u"KAuth"_s, u"kf5.kauth"_s, LoggingCategory::Info, QString(), true);

    LoggingCategory::List qtKdeCategories;
    qtKdeCategories.append(LoggingCategory(u"KPasswdServer (KIO)"_s, u"org.kde.kio.kpasswdserver"_s, LoggingCategory::Info, QString(), true));
    qtKdeCategories.append(ikwsInfo);
    qtKdeCategories.append(shorturiInfo);
    qtKdeCategories.append(bluezQtInfo);
    qtKdeCategories.append(kauthInfo);

    QTest::newRow("emptywithlistkdeloggingcategories")
        << u"rulebeforerulessectionfiles.ini"_s << u"correct.categories"_s << false << LoggingCategory::List() << qtKdeCategories;

    qtKdeCategories[0] = LoggingCategory(u"KPasswdServer (KIO)"_s, u"org.kde.kio.kpasswdserver"_s, LoggingCategory::Off, QString(), false);

    QTest::newRow("oneelementoff") << u"oneelementoff.ini"_s << u"correct.categories"_s << false << LoggingCategory::List() << qtKdeCategories;

    QTest::newRow("oneelementonelineoff") << u"oneelementonelineoff.ini"_s << u"correct.categories"_s << false << LoggingCategory::List() << qtKdeCategories;

    qtKdeCategories[0] = LoggingCategory(u"KPasswdServer (KIO)"_s, u"org.kde.kio.kpasswdserver"_s, LoggingCategory::All, QString(), true);

    QTest::newRow("oneelementall") << u"oneelementall.ini"_s << u"correct.categories"_s << false << LoggingCategory::List() << qtKdeCategories;

    QTest::newRow("oneelementonelineall") << u"oneelementonelineall.ini"_s << u"correct.categories"_s << false << LoggingCategory::List() << qtKdeCategories;

    qtKdeCategories[0] = LoggingCategory(u"KPasswdServer (KIO)"_s, u"org.kde.kio.kpasswdserver"_s, LoggingCategory::Info, QString(), true);

    QTest::newRow("oneelementinfo") << u"oneelementinfo.ini"_s << u"correct.categories"_s << false << LoggingCategory::List() << qtKdeCategories;

    QTest::newRow("oneelementinfo") << u"oneelementinfobis.ini"_s << u"correct.categories"_s << false << LoggingCategory::List() << qtKdeCategories;

    qtKdeCategories[0] = LoggingCategory(u"KPasswdServer (KIO)"_s, u"org.kde.kio.kpasswdserver"_s, LoggingCategory::Warning, QString(), true);

    QTest::newRow("oneelementwarning") << u"oneelementwarning.ini"_s << u"correct.categories"_s << false << LoggingCategory::List() << qtKdeCategories;

    qtKdeCategories[0] = LoggingCategory(u"KPasswdServer (KIO)"_s, u"org.kde.kio.kpasswdserver"_s, LoggingCategory::Critical, QString(), true);

    QTest::newRow("oneelementcritical") << u"oneelementcritical.ini"_s << u"correct.categories"_s << false << LoggingCategory::List() << qtKdeCategories;

    QTest::newRow("oneelementonelinecritical") << u"oneelementonelinecritical.ini"_s << u"correct.categories"_s << false << LoggingCategory::List()
                                               << qtKdeCategories;
    QTest::newRow("oneelementtwolinecritical") << u"oneelementtwolinecritical.ini"_s << u"correct.categories"_s << false << LoggingCategory::List()
                                               << qtKdeCategories;

    qtKdeCategories[0] = LoggingCategory(u"KPasswdServer (KIO)"_s, u"org.kde.kio.kpasswdserver"_s, LoggingCategory::Warning, QString(), true);

    QTest::newRow("oneelementdebug") << u"oneelementdebug.ini"_s << u"correct.categories"_s << false << LoggingCategory::List() << qtKdeCategories;
    // Duplicate entries
    qtKdeCategories[0] = LoggingCategory(u"KPasswdServer (KIO)"_s, u"org.kde.kio.kpasswdserver"_s, LoggingCategory::All, QString(), true);
    QTest::newRow("duplicates") << u"duplicates.ini"_s << u"correct.categories"_s << false << LoggingCategory::List() << qtKdeCategories;

    // Duplicate entries with duplicate categories
    qtKdeCategories[0] = LoggingCategory(u"KPasswdServer (KIO)"_s, u"org.kde.kio.kpasswdserver"_s, LoggingCategory::All, QString(), true);
    QTest::newRow("duplicates") << u"duplicates.ini"_s << u"duplicates.categories"_s << false << LoggingCategory::List() << qtKdeCategories;

    // Test with extract elements
    LoggingCategory::List customCategories;
    LoggingCategory customTmp;
    customTmp.categoryName = u"toto"_s;
    customTmp.loggingType = LoggingCategory::Critical;
    customTmp.enabled = true;
    customCategories.append(customTmp);
    qtKdeCategories[0] = LoggingCategory(u"KPasswdServer (KIO)"_s, u"org.kde.kio.kpasswdserver"_s, LoggingCategory::Warning, QString(), true);

    QTest::newRow("oneelementdebugandanextract") << u"oneelementdebugandanextract.ini"_s << u"correct.categories"_s << false << customCategories
                                                 << qtKdeCategories;

    // Test with extract elements
    customCategories.clear();
    customTmp.categoryName = u"toto"_s;
    customTmp.loggingType = LoggingCategory::Critical;
    customTmp.enabled = false;
    customCategories.append(customTmp);

    QTest::newRow("oneelementdebugandanextractfalse") << u"oneelementdebugandanextractfalse.ini"_s << u"correct.categories"_s << false << customCategories
                                                      << qtKdeCategories;

    // Test without categories
    qtKdeCategories.clear();
    customCategories.clear();
    customTmp.categoryName = u"toto"_s;
    customTmp.loggingType = LoggingCategory::Info;
    customTmp.enabled = false;
    customCategories.append(customTmp);
    customTmp.categoryName = u"toto"_s;
    customTmp.loggingType = LoggingCategory::Warning;
    customTmp.enabled = false;
    customCategories.append(customTmp);
    customTmp.categoryName = u"toto"_s;
    customTmp.loggingType = LoggingCategory::Debug;
    customTmp.enabled = false;
    customCategories.append(customTmp);

    customTmp.categoryName = u"toto"_s;
    customTmp.loggingType = LoggingCategory::Critical;
    customTmp.enabled = false;
    customCategories.append(customTmp);

    QTest::newRow("testwithoutcategories") << u"testwithoutcategories.ini"_s << QString() << false << customCategories << qtKdeCategories;

    qtKdeCategories.clear();
    customCategories.clear();
    customTmp.categoryName = u"toto"_s;
    customTmp.loggingType = LoggingCategory::Warning;
    customTmp.enabled = false;
    customCategories.append(customTmp);
    QTest::newRow("testwithoutcategorieswarning") << u"testwithoutcategorieswarning.ini"_s << QString() << false << customCategories << qtKdeCategories;
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
        const QString kdeLoggingCategoriesPath = QString(QLatin1StringView(KDEBUGSETTINGS_DATA_DIR) + u'/' + filenamelistKdeLoggingCategories);
        KDebugSettingsUtil::readLoggingCategories(kdeLoggingCategoriesPath, listKdeLoggingCategories, true);
    }

    const QString path = QString(QLatin1StringView(KDEBUGSETTINGS_DATA_DIR) + u'/' + filename);
    QFile file(path);
    QVERIFY(file.exists());
    job.setFileName(path);
    job.setCategories(listKdeLoggingCategories);
    job.start();

    if (job.customCategories() != customcategories) {
        const auto catList = job.customCategories();
        for (const LoggingCategory &cat : catList) {
            qDebug() << "customcategories cat." << cat.description << " logname" << cat.categoryName << " enabled " << cat.enabled << "type "
                     << cat.loggingType;
        }

        qDebug() << "AFTER";
        for (const LoggingCategory &cat : std::as_const(customcategories)) {
            qDebug() << "customcategories cat." << cat.description << " logname" << cat.categoryName << " enabled " << cat.enabled << "type "
                     << cat.loggingType;
        }
    }
    QCOMPARE(job.customCategories().count(), customcategories.count());
    QCOMPARE(job.customCategories(), customcategories);

    QCOMPARE(job.foundOverrideRule(), foundoverriderules);

    if (job.qtKdeCategories() != qtkdecategories) {
        const auto catList = job.qtKdeCategories();
        for (const LoggingCategory &cat : catList) {
            qDebug() << "qtKdeCategories cat." << cat.description << " logname" << cat.categoryName << " enabled " << cat.enabled << "type " << cat.loggingType;
        }

        qDebug() << "AFTER";
        for (const LoggingCategory &cat : std::as_const(qtkdecategories)) {
            qDebug() << "qtKdeCategories cat." << cat.description << " logname" << cat.categoryName << " enabled " << cat.enabled << "type " << cat.loggingType;
        }
    }
    QCOMPARE(job.qtKdeCategories().count(), qtkdecategories.count());
    QCOMPARE(job.qtKdeCategories(), qtkdecategories);
}

QTEST_MAIN(LoadCategoriesJobTest)

#include "moc_loadcategoriesjobtest.cpp"
