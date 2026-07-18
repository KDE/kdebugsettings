/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdeapplicationloggingcategorymodeltest.h"
#include "model/kdeapplicationloggingcategorymodel.h"

#include <QTest>

namespace
{
constexpr int qmlRole(KDEApplicationLoggingCategoryModel::CategoryRoles role)
{
    return static_cast<int>(Qt::UserRole) + static_cast<int>(role) + 1;
}
}

QTEST_GUILESS_MAIN(KDEApplicationLoggingCategoryModelTest)

KDEApplicationLoggingCategoryModelTest::KDEApplicationLoggingCategoryModelTest(QObject *parent)
    : QObject{parent}
{
}

void KDEApplicationLoggingCategoryModelTest::shouldExposeUserRolesForQml()
{
    const KDEApplicationLoggingCategoryModel model;
    const auto roles = model.roleNames();

    QVERIFY(!roles.contains(Qt::DisplayRole));
    QVERIFY(!roles.contains(KDEApplicationLoggingCategoryModel::DescriptionRole));

    QCOMPARE(roles.value(qmlRole(KDEApplicationLoggingCategoryModel::DescriptionRole)), QByteArray("description"));
    QCOMPARE(roles.value(qmlRole(KDEApplicationLoggingCategoryModel::LoggingTypeRole)), QByteArray("loggingType"));
    QCOMPARE(roles.value(qmlRole(KDEApplicationLoggingCategoryModel::CategoryRole)), QByteArray("category"));
    QCOMPARE(roles.value(qmlRole(KDEApplicationLoggingCategoryModel::LoggingTypeStrRole)), QByteArray("loggingTypeStr"));
}

void KDEApplicationLoggingCategoryModelTest::shouldReturnExpectedDataForWidgetsAndQml()
{
    KDEApplicationLoggingCategoryModel model;

    LoggingCategory cat(QStringLiteral("desc"), QStringLiteral("org.kde.test"), LoggingCategory::Warning, QStringLiteral("ident"), true);
    cat.defaultSeverityType = LoggingCategory::Info;
    model.setLoggingCategories({cat});

    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.columnCount(), static_cast<int>(KDEApplicationLoggingCategoryModel::LastColumn) + 1);

    const QModelIndex descriptionIndex = model.index(0, KDEApplicationLoggingCategoryModel::DescriptionRole);
    const QModelIndex typeIndex = model.index(0, KDEApplicationLoggingCategoryModel::LoggingTypeRole);
    const QModelIndex categoryIndex = model.index(0, KDEApplicationLoggingCategoryModel::CategoryRole);
    const QModelIndex typeStrIndex = model.index(0, KDEApplicationLoggingCategoryModel::LoggingTypeStrRole);

    QCOMPARE(model.data(descriptionIndex, Qt::DisplayRole).toString(), QStringLiteral("desc"));
    QCOMPARE(model.data(typeIndex, Qt::DisplayRole).value<LoggingCategory::LoggingType>(), LoggingCategory::Warning);
    QCOMPARE(model.data(categoryIndex, Qt::DisplayRole).value<LoggingCategory>(), cat);
    QCOMPARE(model.data(typeStrIndex, Qt::DisplayRole).toString(),
             model.data(descriptionIndex, qmlRole(KDEApplicationLoggingCategoryModel::LoggingTypeStrRole)).toString());

    // QML uses role-based lookup on any column index.
    QCOMPARE(model.data(descriptionIndex, qmlRole(KDEApplicationLoggingCategoryModel::DescriptionRole)).toString(), QStringLiteral("desc"));
    QCOMPARE(model.data(descriptionIndex, qmlRole(KDEApplicationLoggingCategoryModel::LoggingTypeRole)).value<LoggingCategory::LoggingType>(),
             LoggingCategory::Warning);
    QCOMPARE(model.data(descriptionIndex, qmlRole(KDEApplicationLoggingCategoryModel::CategoryRole)).value<LoggingCategory>(), cat);
    QCOMPARE(model.data(descriptionIndex, qmlRole(KDEApplicationLoggingCategoryModel::LoggingTypeStrRole)).toString(),
             model.data(typeStrIndex, Qt::DisplayRole).toString());

    // Role value 0 is Qt::DisplayRole, not the QML "description" role.
    QCOMPARE(model.data(descriptionIndex, KDEApplicationLoggingCategoryModel::DescriptionRole).toString(), QStringLiteral("desc"));
}

#include "moc_kdeapplicationloggingcategorymodeltest.cpp"
