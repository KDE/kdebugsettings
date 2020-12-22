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
private:
    enum {
        FullPathRole = Qt::UserRole + 1
    };
    void init();
    QListWidget *const mListWidget;
};

#endif // GROUPMANAGEMENTWIDGET_H
