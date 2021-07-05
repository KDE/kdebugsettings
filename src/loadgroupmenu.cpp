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
    return QStandardPaths::locateAll(QStandardPaths::AppLocalDataLocation, QLatin1String("/groups/"), QStandardPaths::LocateDirectory);
}

void LoadGroupMenu::init()
{
    // Load all ?
    mGroupNames.clear();
    const QStringList groupPath = defaultReadableGroupPath();
    if (groupPath.isEmpty()) {
        setEnabled(false);
        return;
    }
    for (const QString &dirName : groupPath) {
        QDir dir(dirName);
        mGroupNames = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
        for (const QString &file : std::as_const(mGroupNames)) {
            QAction *act = addAction(file);
            const QString fullPath = dirName + QLatin1Char('/') + file;
            connect(act, &QAction::triggered, this, [this, fullPath] {
                Q_EMIT loadGroupRequested(fullPath);
            });
        }
    }
    if (isEmpty()) {
        setEnabled(false);
        return;
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
