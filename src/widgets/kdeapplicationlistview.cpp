/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdeapplicationlistview.h"
#include <QHeaderView>

KDEApplicationListView::KDEApplicationListView(QWidget *parent)
    : QTreeView(parent)
{
    header()->hide();
}

KDEApplicationListView::~KDEApplicationListView() = default;
