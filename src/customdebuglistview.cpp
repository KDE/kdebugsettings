/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "customdebuglistview.h"
#include "model/customdebugmodel.h"

#include <KLocalizedString>

#include <QAction>
#include <QMenu>

CustomDebugListView::CustomDebugListView(QWidget *parent)
    : QListView(parent)
    , mCustomDebugModel(new CustomDebugModel(this))
{
    // TODO add proxymodel
    setModel(mCustomDebugModel);
    setContextMenuPolicy(Qt::DefaultContextMenu);
}

CustomDebugListView::~CustomDebugListView() = default;

void CustomDebugListView::setLoggingCategories(const LoggingCategory::List &list)
{
    mCustomDebugModel->setLoggingCategories(list);
}

void CustomDebugListView::contextMenuEvent(QContextMenuEvent *event)
{
#if 0
    QMenu menu(this);
    auto clearRecent = new QAction(i18n("Clear Recents"), &menu);
    connect(clearRecent, &QAction::triggered, this, &EmoticonListView::clearHistory);
    menu.addAction(clearRecent);
    menu.exec(event->globalPos());
#endif
    // TODO
}
