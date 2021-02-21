/*
    SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loadgroupmenu.h"

#include <KLocalizedString>

#include <QDir>
#include <QStandardPaths>

LoadGroupMenu::LoadGroupMenu(QWidget *parent)
    : QMenu(parent)
{
    setTitle(i18n("Load Group"));
    init();
}

LoadGroupMenu::~LoadGroupMenu()
{
}

void LoadGroupMenu::refreshMenu()
{
    clear();
    init();
}

QString LoadGroupMenu::defaultWritableGroupPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + QLatin1String("/groups");
}

QStringList LoadGroupMenu::defaultReadableGroupPath() const
{
    return QStandardPaths::locateAll(QStandardPaths::AppLocalDataLocation, QLatin1String("/groups"), QStandardPaths::LocateFile);
}

void LoadGroupMenu::init()
{
    // Load all ?
    mGroupNames.clear();
    const QString groupPath = LoadGroupMenu::defaultWritableGroupPath();
    if (groupPath.isEmpty()) {
        setEnabled(false);
        return;
    }
    QDir dir(groupPath);
    mGroupNames = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    if (mGroupNames.isEmpty()) {
        setEnabled(false);
        return;
    }
    setEnabled(true);
    for (const QString &file : mGroupNames) {
        QAction *act = addAction(file);
        const QString fullPath = groupPath + QLatin1Char('/') + file;
        connect(act, &QAction::triggered, this, [this, fullPath] {
            Q_EMIT loadGroupRequested(fullPath);
        });
    }
    addSeparator();
    QAction *manageGroup = addAction(i18n("Manage Group"));
    connect(manageGroup, &QAction::triggered, this, &LoadGroupMenu::manageGroupRequested);
}

QStringList LoadGroupMenu::groupNames() const
{
    return mGroupNames;
}

void LoadGroupMenu::setGroupNames(const QStringList &groupNames)
{
    mGroupNames = groupNames;
}
