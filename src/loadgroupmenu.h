/*
    SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef LOADGROUPMENU_H
#define LOADGROUPMENU_H

#include "libkdebugsettings_private_export.h"
#include <QMenu>
class LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT LoadGroupMenu : public QMenu
{
    Q_OBJECT
public:
    explicit LoadGroupMenu(QWidget *parent = nullptr);
    ~LoadGroupMenu() override;

    void refreshMenu();

    static Q_REQUIRED_RESULT QString defaultWritableGroupPath();

    Q_REQUIRED_RESULT QStringList groupNames() const;
    void setGroupNames(const QStringList &groupNames);

Q_SIGNALS:
    void loadGroupRequested(const QString &filePath);
    void manageGroupRequested();

private:
    void init();
    QStringList mGroupNames;
};

#endif // LOADGROUPMENU_H
