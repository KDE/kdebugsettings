/*
  Copyright (c) 2020 Laurent Montel <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

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
    QMenu *mainMenu = new QMenu(this);
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
