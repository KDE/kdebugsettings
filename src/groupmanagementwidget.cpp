/*
    SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "groupmanagementwidget.h"
#include "kdebugsettingsutil.h"
#include "loadgroupmenu.h"

#include <KLocalizedString>
#include <KMessageBox>

#include <QDir>
#include <QInputDialog>
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
    mListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    mListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mListWidget, &QListWidget::itemDoubleClicked, this, &GroupManagementWidget::renameGroup);
    connect(mListWidget, &QListWidget::customContextMenuRequested, this, &GroupManagementWidget::slotCustomContextMenu);
    init();
}

GroupManagementWidget::~GroupManagementWidget() = default;

void GroupManagementWidget::renameGroup(QListWidgetItem *item)
{
    if (!item) {
        return;
    }
    const QString fullPath = item->data(FullPathRole).toString();
    QFile f(fullPath);
    const QString newName = QInputDialog::getText(this, i18n("Rename Group"), i18n("New Name:"));
    const QString newNameTrimmed = newName.trimmed();
    if (!newNameTrimmed.isEmpty()) {
        const QString newFullPath{LoadGroupMenu::defaultWritableGroupPath() + QLatin1Char('/') + newNameTrimmed};
        if (!f.rename(newFullPath)) {
            KMessageBox::error(this, i18n("Impossible to rename group as \'%1\'", newNameTrimmed), i18n("Rename Group"));
        } else {
            item->setText(newNameTrimmed);
            item->setData(FullPathRole, newFullPath);
            Q_EMIT groupsChanged();
        }
    }
}

void GroupManagementWidget::slotCustomContextMenu()
{
    const auto items = mListWidget->selectedItems();
    if (!items.isEmpty()) {
        QMenu menu(this);
        if (mListWidget->selectedItems().count() == 1) {
            const auto item = items.at(0);
            menu.addAction(QIcon::fromTheme(QStringLiteral("edit")), i18n("Rename Groups"), this, [this, item]() {
                renameGroup(item);
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
    const QStringList groups = KDebugSettingsUtil::groupFileList();
    if (!groups.isEmpty()) {
        const QString groupPath = LoadGroupMenu::defaultWritableGroupPath();
        for (const QString &file : groups) {
            auto item = new QListWidgetItem(file, mListWidget);
            const QString fullPath = groupPath + QLatin1Char('/') + file;
            item->setData(FullPathRole, fullPath);
        }
    }
}
