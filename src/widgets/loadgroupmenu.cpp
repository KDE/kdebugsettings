/*
    SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loadgroupmenu.h"
using namespace Qt::Literals::StringLiterals;

#include "kdebugsettingsutil.h"

#include <KLocalizedString>

#include <QDir>
#include <QStandardPaths>

LoadGroupMenu::LoadGroupMenu(QWidget *parent)
    : QMenu(parent)
{
    setTitle(i18n("Load Group"));
    init();
}

LoadGroupMenu::~LoadGroupMenu() = default;

void LoadGroupMenu::refreshMenu()
{
    clear();
    init();
}

QString LoadGroupMenu::defaultWritableGroupPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/groups"_L1;
}

QStringList LoadGroupMenu::defaultReadableGroupPath() const
{
    return QStandardPaths::locateAll(QStandardPaths::AppLocalDataLocation, u"/groups/"_s, QStandardPaths::LocateDirectory);
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
        const QStringList dirNameList = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
        mGroupNames += dirNameList;
        for (const QString &file : dirNameList) {
            QAction *act = addAction(file);
            const QString fullPath = dirName + u'/' + file;
            connect(act, &QAction::triggered, this, [this, fullPath] {
                Q_EMIT loadGroupRequested(fullPath);
            });
        }
    }
    if (isEmpty()) {
        setEnabled(false);
        return;
    }
    if (KDebugSettingsUtil::hasWritableGroups()) {
        addSeparator();
        QAction *manageGroup = addAction(i18nc("@action", "Manage Group"));
        connect(manageGroup, &QAction::triggered, this, &LoadGroupMenu::manageGroupRequested);
    }
}

QStringList LoadGroupMenu::groupNames() const
{
    return mGroupNames;
}

void LoadGroupMenu::setGroupNames(const QStringList &groupNames)
{
    mGroupNames = groupNames;
}

#include "moc_loadgroupmenu.cpp"
