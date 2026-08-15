/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdeapplicationloggingcategorymodeltest.h"
#include "model/kdeapplicationloggingcategorymodel.h"

#include <QSignalSpy>
#include <QTest>

namespace
{
// Short alias for the call sites below, the value itself comes from the model.
constexpr int qmlRole(KDEApplicationLoggingCategoryModel::CategoryRoles role)
{
    return KDEApplicationLoggingCategoryModel::qmlRole(role);
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
    QCOMPARE(roles.value(qmlRole(KDEApplicationLoggingCategoryModel::GeneratedToolTipRole)), QByteArray("generatedToolTip"));
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
    const QModelIndex generatedToolTipIndex = model.index(0, KDEApplicationLoggingCategoryModel::GeneratedToolTipRole);

    QCOMPARE(model.data(descriptionIndex, Qt::DisplayRole).toString(), QStringLiteral("desc"));
    QCOMPARE(model.data(typeIndex, Qt::DisplayRole).value<LoggingCategory::LoggingType>(), LoggingCategory::Warning);
    QCOMPARE(model.data(categoryIndex, Qt::DisplayRole).value<LoggingCategory>(), cat);
    QCOMPARE(model.data(typeStrIndex, Qt::DisplayRole).toString(),
             model.data(descriptionIndex, qmlRole(KDEApplicationLoggingCategoryModel::LoggingTypeStrRole)).toString());

    QCOMPARE(model.data(generatedToolTipIndex, Qt::DisplayRole).toString(),
             model.data(descriptionIndex, qmlRole(KDEApplicationLoggingCategoryModel::GeneratedToolTipRole)).toString());

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

void KDEApplicationLoggingCategoryModelTest::shouldNotifyTheWholeRowOnTypeChange()
{
    KDEApplicationLoggingCategoryModel model;
    LoggingCategory cat(QStringLiteral("desc"), QStringLiteral("org.kde.test"), LoggingCategory::Warning, QStringLiteral("ident"), true);
    model.setLoggingCategories({cat});

    QSignalSpy spy(&model, &QAbstractItemModel::dataChanged);
    const QModelIndex typeIndex = model.index(0, KDEApplicationLoggingCategoryModel::LoggingTypeRole);
    QVERIFY(model.setData(typeIndex, QVariant::fromValue(LoggingCategory::Critical), Qt::EditRole));
    QCOMPARE(spy.count(), 1);

    const QModelIndex topLeft = spy.at(0).at(0).toModelIndex();
    const QModelIndex bottomRight = spy.at(0).at(1).toModelIndex();
    const QList<int> roles = spy.at(0).at(2).value<QList<int>>();

    // The first column must be included: QML delegates only read column 0.
    QCOMPARE(topLeft.column(), static_cast<int>(KDEApplicationLoggingCategoryModel::DescriptionRole));
    QCOMPARE(bottomRight.column(), static_cast<int>(KDEApplicationLoggingCategoryModel::LastColumn));
    QCOMPARE(topLeft.row(), 0);
    QCOMPARE(bottomRight.row(), 0);

    // Real role ids must be advertised and not the column enum values, otherwise
    // the views are told that unrelated roles changed.
    QVERIFY(roles.contains(Qt::DisplayRole));
    QVERIFY(roles.contains(qmlRole(KDEApplicationLoggingCategoryModel::LoggingTypeRole)));
    QVERIFY(roles.contains(qmlRole(KDEApplicationLoggingCategoryModel::LoggingTypeStrRole)));
    QVERIFY(!roles.contains(Qt::DecorationRole));
}

#include "moc_kdeapplicationloggingcategorymodeltest.cpp"
