/*
    SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loadgroupmenu.h"
#include "loadtoolbutton.h"
#include <KLocalizedString>

LoadToolButton::LoadToolButton(QWidget *parent)
    : QToolButton(parent)
    , mLoadMenu(new LoadGroupMenu(this))
{
    setPopupMode(QToolButton::InstantPopup);
    setText(i18n("Load..."));
    auto mainMenu = new QMenu(this);
    setMenu(mainMenu);

    QAction *act = mainMenu->addAction(i18n("Load From File..."));
    connect(act, &QAction::triggered, this, &LoadToolButton::loadFromFile);

    mLoadMenu->setObjectName(QStringLiteral("loadMenu"));
    connect(mLoadMenu, &LoadGroupMenu::loadGroupRequested, this, &LoadToolButton::loadGroupRequested);
    connect(mLoadMenu, &LoadGroupMenu::manageGroupRequested, this, &LoadToolButton::manageGroupRequested);
    mainMenu->addMenu(mLoadMenu);
}

LoadToolButton::~LoadToolButton()
{
}

void LoadToolButton::updateLoadGroupMenu()
{
    mLoadMenu->refreshMenu();
}

QStringList LoadToolButton::groupNames() const
{
    return mLoadMenu->groupNames();
}
