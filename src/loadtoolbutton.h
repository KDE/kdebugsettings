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

#ifndef LOADTOOLBUTTON_H
#define LOADTOOLBUTTON_H

#include <QToolButton>

#include "libkdebugsettings_private_export.h"
class LoadGroupMenu;
class LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT LoadToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit LoadToolButton(QWidget *parent = nullptr);
    ~LoadToolButton() override;

    void updateLoadGroupMenu();
Q_SIGNALS:
    void loadGroupRequested(const QString &fullPath);
    void loadFromFile();
    void manageGroupRequested();
private:
    LoadGroupMenu *const mLoadMenu;
};

#endif // LOADTOOLBUTTON_H
