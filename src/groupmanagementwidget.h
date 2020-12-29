/*
    SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef GROUPMANAGEMENTWIDGET_H
#define GROUPMANAGEMENTWIDGET_H

#include <QWidget>

#include "libkdebugsettings_private_export.h"
class QListWidget;
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
    enum {
        FullPathRole = Qt::UserRole + 1
    };
    void init();
    QListWidget *const mListWidget;
};

#endif // GROUPMANAGEMENTWIDGET_H
