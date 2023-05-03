/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "customdebuglistview.h"
#include "model/customdebugmodel.h"

CustomDebugListView::CustomDebugListView(QWidget *parent)
    : QListView(parent)
{
    setModel(new CustomDebugModel(this));
}

CustomDebugListView::~CustomDebugListView()
{
}
