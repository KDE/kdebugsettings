/*
    SPDX-FileCopyrightText: 2020-2022 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

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
