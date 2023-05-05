/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "customdebuglistview.h"
#include "model/customdebugmodel.h"

#include <KLocalizedString>

#include <QAction>
#include <QMenu>

CustomDebugListView::CustomDebugListView(QWidget *parent)
    : QListView(parent)
    , mCustomDebugModel(new CustomDebugModel(this))
{
    mCustomDebugModel->setObjectName(QStringLiteral("mCustomDebugModel"));
    // TODO add proxymodel
    setModel(mCustomDebugModel);
    setContextMenuPolicy(Qt::DefaultContextMenu);
}

CustomDebugListView::~CustomDebugListView() = default;

void CustomDebugListView::setLoggingCategories(const LoggingCategory::List &list)
{
    mCustomDebugModel->setLoggingCategories(list);
}

void CustomDebugListView::contextMenuEvent(QContextMenuEvent *event)
{
#if 0
    QMenu menu(this);
    const auto selectedItemCount{mListWidget->selectedItems().count()};
    menu.addAction(QIcon::fromTheme(QStringLiteral("list-add")), i18n("Add Rule..."), this, &CustomDebugListView::slotAddRule);
    if (selectedItemCount == 1) {
        menu.addAction(QIcon::fromTheme(QStringLiteral("document-edit")), i18n("Edit Rule"), this, &CustomDebugListView::slotEditRule);
    }
    if (selectedItemCount > 0) {
        menu.addSeparator();
        menu.addAction(QIcon::fromTheme(QStringLiteral("list-remove")), i18n("Remove Rule"), this, &CustomDebugListView::slotRemoveRules);
    }
    menu.exec(mListWidget->viewport()->mapToGlobal(pos));

#endif
    // TODO
}

#if 0
void CustomDebugSettingsPage::slotRemoveRules()
{
    const QList<QListWidgetItem *> lst = mListWidget->selectedItems();
    if (lst.isEmpty()) {
        return;
    }
    const QString str = i18np("Do you want to remove this rule?", "Do you want to remove these %1 rules?", lst.count());

    if (KMessageBox::ButtonCode::SecondaryAction
        == KMessageBox::warningTwoActions(this, str, i18n("Remove Rule"), KStandardGuiItem::remove(), KStandardGuiItem::cancel())) {
        return;
    }
    for (int i = 0; i < lst.count(); ++i) {
        QListWidgetItem *item = lst.at(i);
        delete item;
    }
}

void CustomDebugSettingsPage::slotEditRule()
{
    if (mListWidget->selectedItems().count() == 1) {
        QListWidgetItem *item = mListWidget->selectedItems().at(0);
        if (item) {
            QPointer<ConfigureCustomSettingDialog> dlg = new ConfigureCustomSettingDialog(this);
            dlg->setRule(item->text());
            if (dlg->exec()) {
                const QString ruleStr = dlg->rule();
                if (!ruleStr.isEmpty()) {
                    item->setText(dlg->rule());
                }
            }
            delete dlg;
        }
    }
}

void CustomDebugSettingsPage::slotAddRule()
{
    QPointer<ConfigureCustomSettingDialog> dlg = new ConfigureCustomSettingDialog(this);
    if (dlg->exec()) {
        const QString ruleStr = dlg->rule();
        if (!ruleStr.isEmpty()) {
            bool alreadyAdded = false;
            const int number(mListWidget->count());
            for (int i = 0; i < number; ++i) {
                if (ruleStr == mListWidget->item(i)->text()) {
                    alreadyAdded = true;
                    break;
                }
            }
            if (!alreadyAdded) {
                mListWidget->addItem(ruleStr);
            }
        }
    }
    delete dlg;
}
#endif