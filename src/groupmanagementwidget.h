/*
    SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QWidget>

#include "libkdebugsettings_private_export.h"
class QListWidget;
class QListWidgetItem;
class LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT GroupManagementWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GroupManagementWidget(QWidget *parent = nullptr);
    ~GroupManagementWidget() override;

private Q_SLOTS:
    void slotCustomContextMenu();

Q_SIGNALS:
    void groupsChanged();

private:
    enum { FullPathRole = Qt::UserRole + 1 };
    void init();
    void renameGroup(QListWidgetItem *item);
    void exportGroup(QListWidgetItem *item);
    QListWidget *const mListWidget;
};
