/*
    SPDX-FileCopyrightText: 2020-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loadtoolbutton.h"
using namespace Qt::Literals::StringLiterals;

#include "loadgroupmenu.h"
#include <KLocalizedString>

LoadToolButton::LoadToolButton(QWidget *parent)
    : QToolButton(parent)
    , mLoadMenu(new LoadGroupMenu(this))
{
    setPopupMode(QToolButton::InstantPopup);
    setText(i18n("Load…"));
    auto mainMenu = new QMenu(this);
    setMenu(mainMenu);

    QAction *act = mainMenu->addAction(i18nc("@action", "Load From File…"));
    connect(act, &QAction::triggered, this, &LoadToolButton::loadFromFile);

    mLoadMenu->setObjectName("loadMenu"_L1);
    connect(mLoadMenu, &LoadGroupMenu::loadGroupRequested, this, &LoadToolButton::loadGroupRequested);
    connect(mLoadMenu, &LoadGroupMenu::manageGroupRequested, this, &LoadToolButton::manageGroupRequested);
    mainMenu->addMenu(mLoadMenu);
}

LoadToolButton::~LoadToolButton() = default;

void LoadToolButton::updateLoadGroupMenu()
{
    mLoadMenu->refreshMenu();
}

QStringList LoadToolButton::groupNames() const
{
    return mLoadMenu->groupNames();
}

#include "moc_loadtoolbutton.cpp"
