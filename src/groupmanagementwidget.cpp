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
#include <KMessageBox>

#include <QDir>
#include <QListWidget>
#include <QVBoxLayout>
#include <QInputDialog>

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
    mListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mListWidget, &QListWidget::customContextMenuRequested, this, &GroupManagementWidget::slotCustomContextMenu);
    init();
}

GroupManagementWidget::~GroupManagementWidget()
{
}

void GroupManagementWidget::slotCustomContextMenu()
{
    const auto items = mListWidget->selectedItems();
    if (!items.isEmpty()) {
        QMenu menu(this);
        if (mListWidget->selectedItems().count() == 1) {
            const auto item = items.at(0);
            menu.addAction(QIcon::fromTheme(QStringLiteral("edit")), i18n("Rename Groups"), this, [this, item]() {
                const QString fullPath = item->data(FullPathRole).toString();
                QFile f(fullPath);
                const QString newName = QInputDialog::getText(this, i18n("Rename Group"), i18n("New Name:"));
                const QString newNameTrimmed = newName.trimmed();
                if (!newNameTrimmed.isEmpty()) {
                    const QString newFullPath {LoadGroupMenu::defaultWritableGroupPath() + QLatin1Char('/') + newNameTrimmed};
                    if (!f.rename(newFullPath)) {
                        KMessageBox::error(this, i18n("Impossible to rename group as \'%1\'", newNameTrimmed), i18n("Rename Group"));
                    } else {
                        item->setText(newNameTrimmed);
                        item->setData(FullPathRole, newFullPath);
                    }
                }
            });
            menu.addSeparator();
        }
        menu.addAction(QIcon::fromTheme(QStringLiteral("edit-delete")), i18n("Remove Groups"), this, [this, items]() {
            for (auto item : items) {
                const QString fullPath = item->data(FullPathRole).toString();
                QFile f(fullPath);
                if (!f.remove()) {
                    KMessageBox::error(this, i18n("Impossible to remove \'%1\'", fullPath), i18n("Remove Group"));
                }
                delete item;
            }
        });
        menu.exec(QCursor::pos());
        Q_EMIT groupsChanged();
    }
}

void GroupManagementWidget::init()
{
    const QString groupPath = LoadGroupMenu::defaultWritableGroupPath();
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
