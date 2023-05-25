/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdeapplicationtreeview.h"
#include "kdeapplicationlistviewdelegate.h"
#include <QHeaderView>

KDEApplicationTreeView::KDEApplicationTreeView(QWidget *parent)
    : QTreeView(parent)
{
    header()->hide();
    setRootIsDecorated(false);
    setAlternatingRowColors(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setItemDelegateForColumn(1, new KDEApplicationListViewDelegate(this));
}

KDEApplicationTreeView::~KDEApplicationTreeView() = default;
