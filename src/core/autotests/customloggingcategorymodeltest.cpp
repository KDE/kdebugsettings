/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customloggingcategorymodeltest.h"
#include "model/customloggingcategorymodel.h"

#include <QSignalSpy>
#include <QTest>

namespace
{
LoggingCategory createCategory(const QString &name, LoggingCategory::LoggingType type = LoggingCategory::All)
{
    return LoggingCategory(QString(), name, type, QString(), true);
}

LoggingCategory::List createCategories()
{
    return {
        createCategory(QStringLiteral("org.kde.a")),
        createCategory(QStringLiteral("org.kde.b")),
        createCategory(QStringLiteral("org.kde.c")),
        createCategory(QStringLiteral("org.kde.d")),
    };
}
}

QTEST_GUILESS_MAIN(CustomLoggingCategoryModelTest)

CustomLoggingCategoryModelTest::CustomLoggingCategoryModelTest(QObject *parent)
    : QObject{parent}
{
}

void CustomLoggingCategoryModelTest::shouldNotSignalWhenRemovingUnknownCategories()
{
    CustomLoggingCategoryModel model;
    model.setLoggingCategories(createCategories());

    QSignalSpy resetSpy(&model, &QAbstractItemModel::modelReset);
    QSignalSpy removedSpy(&model, &QAbstractItemModel::rowsRemoved);

    // Explicit type: removeCategory({}) would pick the removeCategory(int) overload.
    model.removeCategory(LoggingCategory::List{});
    // Same category name but a different type: not the same rule.
    model.removeCategory({createCategory(QStringLiteral("org.kde.a"), LoggingCategory::Warning)});
    model.removeCategory({createCategory(QStringLiteral("org.kde.unknown"))});

    QCOMPARE(model.rowCount(), 4);
    QCOMPARE(resetSpy.count(), 0);
    QCOMPARE(removedSpy.count(), 0);
}

void CustomLoggingCategoryModelTest::shouldRemoveCategoriesAsRowsRemoved()
{
    CustomLoggingCategoryModel model;
    const LoggingCategory::List categories = createCategories();
    model.setLoggingCategories(categories);

    QSignalSpy removedSpy(&model, &QAbstractItemModel::rowsRemoved);

    // Rows 1 and 2 are contiguous and must be reported as a single range.
    model.removeCategory({categories.at(2), categories.at(1)});

    QCOMPARE(removedSpy.count(), 1);
    QCOMPARE(removedSpy.at(0).at(1).toInt(), 1);
    QCOMPARE(removedSpy.at(0).at(2).toInt(), 2);

    QCOMPARE(model.rowCount(), 2);
    QCOMPARE(model.loggingCategories(), LoggingCategory::List({categories.at(0), categories.at(3)}));
}

void CustomLoggingCategoryModelTest::shouldRemoveOneRowPerRequestedCategory()
{
    CustomLoggingCategoryModel model;
    const LoggingCategory duplicated = createCategory(QStringLiteral("org.kde.a"));
    model.setLoggingCategories({duplicated, duplicated, createCategory(QStringLiteral("org.kde.b"))});

    model.removeCategory({duplicated});
    QCOMPARE(model.rowCount(), 2);

    model.removeCategory({duplicated, duplicated});
    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.loggingCategories().at(0).categoryName, QStringLiteral("org.kde.b"));
}

#include "moc_customloggingcategorymodeltest.cpp"
