/*
    SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#include "savetoolbutton.h"
using namespace Qt::Literals::StringLiterals;

#include <KLocalizedString>
#include <QAction>
#include <QMenu>

SaveToolButton::SaveToolButton(QWidget *parent)
    : QToolButton(parent)
{
    setText(i18n("Save As…"));
    setPopupMode(QToolButton::InstantPopup);
    auto mainMenu = new QMenu(this);
    setMenu(mainMenu);

    QAction *act = mainMenu->addAction(i18nc("@action", "Save As File…"));
    connect(act, &QAction::triggered, this, &SaveToolButton::saveAsFile);

    QAction *actGroup = mainMenu->addAction(i18nc("@action", "Save As Group…"));
    connect(actGroup, &QAction::triggered, this, &SaveToolButton::saveAsGroup);
}

SaveToolButton::~SaveToolButton() = default;

#include "moc_savetoolbutton.cpp"
