/*
    SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

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
                        Q_EMIT groupsChanged();
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
            Q_EMIT groupsChanged();
        });
        menu.exec(QCursor::pos());
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
        auto item = new QListWidgetItem(file, mListWidget);
        const QString fullPath = groupPath + QLatin1Char('/') + file;
        item->setData(FullPathRole, fullPath);
    }
}
