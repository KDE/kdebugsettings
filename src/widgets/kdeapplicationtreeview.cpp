/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdeapplicationtreeview.h"
#include "kdeapplicationlistviewdelegate.h"
#include "model/kdeapplicationloggingcategorymodel.h"
#include "model/kdeapplicationloggingcategoryproxymodel.h"
#include <QHeaderView>

KDEApplicationTreeView::KDEApplicationTreeView(QWidget *parent)
    : QTreeView(parent)
    , mKdeApplicationLoggingCategoryProxyModel(new KDEApplicationLoggingCategoryProxyModel(this))
{
    header()->hide();
    setRootIsDecorated(false);
    setAlternatingRowColors(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(ExtendedSelection);
    setEditTriggers(AllEditTriggers);
    setUniformRowHeights(true);
}

KDEApplicationTreeView::~KDEApplicationTreeView() = default;

void KDEApplicationTreeView::setLoggingCategoryModel(KDEApplicationLoggingCategoryModel *newLoggingCategoryModel)
{
    mKdeApplicationLoggingCategoryModel = newLoggingCategoryModel;
    mKdeApplicationLoggingCategoryModel->setObjectName(QLatin1StringView("mKdeApplicationLoggingCategoryModel"));

    mKdeApplicationLoggingCategoryProxyModel->setSourceModel(mKdeApplicationLoggingCategoryModel);
    setModel(mKdeApplicationLoggingCategoryProxyModel);
    // Hide column when we have model.
    hideColumn(KDEApplicationLoggingCategoryModel::LoggingTypeRole);
    hideColumn(KDEApplicationLoggingCategoryModel::CategoryRole);
    setItemDelegateForColumn(KDEApplicationLoggingCategoryModel::LoggingTypeStrRole, new KDEApplicationListViewDelegate(this));
    resizeColumnToContents(KDEApplicationLoggingCategoryModel::DescriptionRole);
}

void KDEApplicationTreeView::setFilterRuleStr(const QString &str)
{
    mKdeApplicationLoggingCategoryProxyModel->setFilterText(str);
}

void KDEApplicationTreeView::selectAllDebugCategories()
{
    LoggingCategory::List lst;
    for (int i = 0; i < mKdeApplicationLoggingCategoryProxyModel->rowCount(); ++i) {
        QModelIndex index = mKdeApplicationLoggingCategoryProxyModel->mapToSource(
            mKdeApplicationLoggingCategoryProxyModel->index(i, KDEApplicationLoggingCategoryModel::CategoryRole));
        auto cat = index.data().value<LoggingCategory>();
        cat.loggingType = LoggingCategory::All;
        lst.append(cat);
    }
    if (!lst.isEmpty()) {
        mKdeApplicationLoggingCategoryModel->replaceCategories(lst);
    }
}

void KDEApplicationTreeView::deSelectAllDebugCategories()
{
    LoggingCategory::List lst;
    for (int i = 0; i < mKdeApplicationLoggingCategoryProxyModel->rowCount(); ++i) {
        const QModelIndex index = mKdeApplicationLoggingCategoryProxyModel->mapToSource(
            mKdeApplicationLoggingCategoryProxyModel->index(i, KDEApplicationLoggingCategoryModel::CategoryRole));
        auto cat = index.data().value<LoggingCategory>();
        cat.loggingType = LoggingCategory::Info;
        lst.append(cat);
    }
    if (!lst.isEmpty()) {
        mKdeApplicationLoggingCategoryModel->replaceCategories(lst);
    }
}

void KDEApplicationTreeView::deSelectAllMessagesCategories()
{
    LoggingCategory::List lst;
    for (int i = 0; i < mKdeApplicationLoggingCategoryProxyModel->rowCount(); ++i) {
        const QModelIndex index = mKdeApplicationLoggingCategoryProxyModel->mapToSource(
            mKdeApplicationLoggingCategoryProxyModel->index(i, KDEApplicationLoggingCategoryModel::CategoryRole));
        auto cat = index.data().value<LoggingCategory>();
        cat.loggingType = LoggingCategory::Off;
        lst.append(cat);
    }
    if (!lst.isEmpty()) {
        mKdeApplicationLoggingCategoryModel->replaceCategories(lst);
    }
}

void KDEApplicationTreeView::insertCategories(const LoggingCategory::List &list)
{
    mKdeApplicationLoggingCategoryModel->insertCategories(list);
}

void KDEApplicationTreeView::restoreToDefault()
{
    LoggingCategory::List lst;
    for (int i = 0; i < mKdeApplicationLoggingCategoryProxyModel->rowCount(); ++i) {
        const QModelIndex index = mKdeApplicationLoggingCategoryProxyModel->mapToSource(
            mKdeApplicationLoggingCategoryProxyModel->index(i, KDEApplicationLoggingCategoryModel::CategoryRole));
        auto cat = index.data().value<LoggingCategory>();
        cat.loggingType = cat.defaultSeverityType;
        lst.append(cat);
    }
    if (!lst.isEmpty()) {
        mKdeApplicationLoggingCategoryModel->replaceCategories(lst);
    }
}

LoggingCategory::List KDEApplicationTreeView::rules(bool forceSavingAllRules) const
{
    LoggingCategory::List lst;
    for (int i = 0; i < mKdeApplicationLoggingCategoryProxyModel->rowCount(); ++i) {
        const QModelIndex index = mKdeApplicationLoggingCategoryProxyModel->mapToSource(
            mKdeApplicationLoggingCategoryProxyModel->index(i, KDEApplicationLoggingCategoryModel::CategoryRole));
        auto cat = index.data().value<LoggingCategory>();
        if (forceSavingAllRules || (cat.loggingType != cat.defaultSeverityType)) {
            cat.enabled = false;
            if (cat.isValid()) {
                lst.append(cat);
            }
        }
    }
    return lst;
}

#include "moc_kdeapplicationtreeview.cpp"
