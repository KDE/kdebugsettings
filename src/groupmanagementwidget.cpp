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

#include "groupmanagementwidget.h"
#include "loadgroupmenu.h"
#include <KLocalizedString>
#include <QDir>
#include <QListWidget>
#include <QVBoxLayout>
GroupManagementWidget::GroupManagementWidget(QWidget *parent)
    : QWidget(parent)
    , mListWidget(new QListWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mListWidget->setObjectName(QStringLiteral("mListWidget"));
    mainLayout->addWidget(mListWidget);
    mListWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    init();
}

GroupManagementWidget::~GroupManagementWidget()
{

}

void GroupManagementWidget::init()
{
    const QString groupPath = LoadGroupMenu::defaultGroupPath();
    if (groupPath.isEmpty()) {
        return;
    }
    QDir dir(groupPath);
    const QStringList groups = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    if (groups.isEmpty()) {
        return;
    }
    for (const QString &file : groups) {
        QListWidgetItem *item = new QListWidgetItem(file, mListWidget);
        const QString fullPath = groupPath + QLatin1Char('/') + file;
        item->setData(FullPathRole, fullPath);
    }
}
