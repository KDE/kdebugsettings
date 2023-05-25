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
}

KDEApplicationTreeView::~KDEApplicationTreeView() = default;

void KDEApplicationTreeView::setLoggingCategoryModel(KDEApplicationLoggingCategoryModel *newLoggingCategoryModel)
{
    mKdeApplicationLoggingCategoryModel = newLoggingCategoryModel;
    mKdeApplicationLoggingCategoryModel->setObjectName(QStringLiteral("mKdeApplicationLoggingCategoryModel"));

    mKdeApplicationLoggingCategoryProxyModel->setSourceModel(mKdeApplicationLoggingCategoryModel);
    setModel(mKdeApplicationLoggingCategoryProxyModel);
    // Hide column when we have model.
    hideColumn(KDEApplicationLoggingCategoryModel::LoggingTypeRole);
    setItemDelegateForColumn(KDEApplicationLoggingCategoryModel::LoggingTypeStrRole, new KDEApplicationListViewDelegate(this));
}
