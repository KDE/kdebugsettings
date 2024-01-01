/*
    SPDX-FileCopyrightText: 2020-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "groupmanagementwidget.h"
#include "kdebugsettingsutil.h"

#include <KLocalizedString>
#include <KMessageBox>

#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QListWidget>
#include <QMenu>
#include <QVBoxLayout>

GroupManagementWidget::GroupManagementWidget(QWidget *parent)
    : QWidget(parent)
    , mListWidget(new QListWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));

    mListWidget->setObjectName(QLatin1StringView("mListWidget"));
    mainLayout->addWidget(mListWidget);
    mListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    mListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mListWidget, &QListWidget::itemDoubleClicked, this, &GroupManagementWidget::renameGroup);
    connect(mListWidget, &QListWidget::customContextMenuRequested, this, &GroupManagementWidget::slotCustomContextMenu);
    init();
}

GroupManagementWidget::~GroupManagementWidget() = default;

void GroupManagementWidget::exportGroup(QListWidgetItem *item)
{
    if (!item) {
        return;
    }
    const QString fullPath = item->data(FullPathRole).toString();
    QFile f(fullPath);
    const QString newPath = QFileDialog::getSaveFileName(this, i18n("Export Group"), QDir::homePath() + QStringLiteral("/%1").arg(item->text()));
    if (!newPath.isEmpty()) {
        if (f.copy(newPath)) {
            KMessageBox::information(this, i18n("Group exported to %1", newPath), i18n("Export Group"));
        } else {
            KMessageBox::error(this, i18n("Impossible to export group \'%2\' to \'%1\'", newPath, item->text()), i18n("Export Group"));
        }
    }
}

void GroupManagementWidget::renameGroup(QListWidgetItem *item)
{
    if (!item) {
        return;
    }
    const QString fullPath = item->data(FullPathRole).toString();
    const QString currentName = item->text();
    QFile f(fullPath);
    const QString newName = QInputDialog::getText(this, i18n("Rename Group"), i18n("New Name:"));
    const QString newNameTrimmed = newName.trimmed();
    if (!newNameTrimmed.isEmpty() && (currentName != newNameTrimmed)) {
        const QString newFullPath{KDebugSettingsUtil::defaultWritableGroupPath() + QLatin1Char('/') + newNameTrimmed};
        if (!f.rename(newFullPath)) {
            KMessageBox::error(this, i18n("Impossible to rename group as \'%1\'.", newNameTrimmed), i18n("Rename Group"));
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
            menu.addAction(QIcon::fromTheme(QStringLiteral("edit")), i18n("Rename Group..."), this, [this, item]() {
                renameGroup(item);
            });
            menu.addSeparator();
            menu.addAction(QIcon::fromTheme(QStringLiteral("document-export")), i18n("Export Group..."), this, [this, item]() {
                exportGroup(item);
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
        const QString groupPath = KDebugSettingsUtil::defaultWritableGroupPath();
        for (const QString &file : groups) {
            auto item = new QListWidgetItem(file, mListWidget);
            const QString fullPath = groupPath + QLatin1Char('/') + file;
            item->setData(FullPathRole, fullPath);
        }
    }
}

#include "moc_groupmanagementwidget.cpp"
