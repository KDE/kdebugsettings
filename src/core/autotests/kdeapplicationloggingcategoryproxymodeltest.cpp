/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdeapplicationloggingcategoryproxymodeltest.h"

#include "model/kdeapplicationloggingcategorymodel.h"
#include "model/kdeapplicationloggingcategoryproxymodel.h"

#include <QTest>

QTEST_GUILESS_MAIN(KDEApplicationLoggingCategoryProxyModelTest)

using namespace Qt::Literals::StringLiterals;
KDEApplicationLoggingCategoryProxyModelTest::KDEApplicationLoggingCategoryProxyModelTest(QObject *parent)
    : QObject{parent}
{
}

void KDEApplicationLoggingCategoryProxyModelTest::shouldHaveDefaultValues()
{
    KDEApplicationLoggingCategoryProxyModel proxy;
    QVERIFY(proxy.filterText().isEmpty());
    QVERIFY(proxy.rules(true).isEmpty());
    QVERIFY(proxy.rules(false).isEmpty());
}

void KDEApplicationLoggingCategoryProxyModelTest::shouldReturnAllRulesWhenFiltering()
{
    KDEApplicationLoggingCategoryModel model;
    KDEApplicationLoggingCategoryProxyModel proxy;
    proxy.setSourceModel(&model);

    // Default severity is Info, so both categories differ from their default and
    // must be saved.
    LoggingCategory::List categories;
    categories.append(LoggingCategory(u"alpha description"_s, u"org.kde.alpha"_s, LoggingCategory::All, QString(), true));
    categories.append(LoggingCategory(u"beta description"_s, u"org.kde.beta"_s, LoggingCategory::Warning, QString(), true));
    model.setLoggingCategories(categories);

    QCOMPARE(proxy.rowCount(), 2);
    QCOMPARE(proxy.rules(false).count(), 2);

    // Filtering is only a display concern: the rules of the categories hidden by
    // the filter must still be saved, otherwise saving while a search is in
    // progress would drop them from qtlogging.ini.
    proxy.setFilterText(u"alpha"_s);
    QCOMPARE(proxy.rowCount(), 1);
    QCOMPARE(proxy.rules(false).count(), 2);
    QCOMPARE(proxy.rules(true).count(), 2);

    proxy.setFilterText(u"does not match anything"_s);
    QCOMPARE(proxy.rowCount(), 0);
    QCOMPARE(proxy.rules(false).count(), 2);

    // A category left at its default severity is not saved unless it is forced.
    proxy.setFilterText(QString());
    LoggingCategory defaultCategory;
    defaultCategory.description = u"gamma description"_s;
    defaultCategory.categoryName = u"org.kde.gamma"_s;
    defaultCategory.loggingType = LoggingCategory::Info;
    defaultCategory.defaultSeverityType = LoggingCategory::Info;
    categories.append(defaultCategory);
    model.setLoggingCategories(categories);

    QCOMPARE(proxy.rules(false).count(), 2);
    QCOMPARE(proxy.rules(true).count(), 3);
}

#include "moc_kdeapplicationloggingcategoryproxymodeltest.cpp"
