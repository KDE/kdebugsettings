/*
    SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef GROUPMANAGEMENTDIALOG_H
#define GROUPMANAGEMENTDIALOG_H

#include <QDialog>

#include "libkdebugsettings_private_export.h"
class GroupManagementWidget;
class LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT GroupManagementDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GroupManagementDialog(QWidget *parent = nullptr);
    ~GroupManagementDialog() override;

Q_SIGNALS:
    void groupsChanged();

private:
    void writeConfig();
    void readConfig();
    GroupManagementWidget *const mGroupManagementWidget;
};

#endif // GROUPMANAGEMENTDIALOG_H
