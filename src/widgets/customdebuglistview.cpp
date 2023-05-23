/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "customdebuglistview.h"
#include "configurecustomsettingdialog.h"
#include "kdebugsettingsutil.h"
#include "model/customdebugproxymodel.h"
#include "model/loggingcategorymodel.h"

#include <KLocalizedString>
#include <KMessageBox>

#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>
#include <QPointer>

CustomDebugListView::CustomDebugListView(QWidget *parent)
    : QListView(parent)
    , mLoggingCategoryModel(new LoggingCategoryModel(this))
    , mCystomDebugProxyModel(new CustomDebugProxyModel(this))
{
    mLoggingCategoryModel->setObjectName(QStringLiteral("mLoggingCategoryModel"));
    mCystomDebugProxyModel->setSourceModel(mLoggingCategoryModel);
    setModel(mCystomDebugProxyModel);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &CustomDebugListView::customContextMenuRequested, this, &CustomDebugListView::slotCustomContextMenuRequested);
}

CustomDebugListView::~CustomDebugListView() = default;

void CustomDebugListView::setLoggingCategories(const LoggingCategory::List &list)
{
    mLoggingCategoryModel->setLoggingCategories(list);
}

void CustomDebugListView::slotCustomContextMenuRequested(const QPoint &pos)
{
    const QModelIndex index = indexAt(pos);
    QMenu menu(this);
    const QModelIndexList selectedIndexes = selectionModel()->selectedRows();
    const auto selectedItemCount{selectedIndexes.count()};
    menu.addAction(QIcon::fromTheme(QStringLiteral("list-add")), i18n("Add Rule..."), this, &CustomDebugListView::slotAddRule);
    if (index.isValid()) {
        menu.addAction(QIcon::fromTheme(QStringLiteral("document-edit")), i18n("Edit Rule"), this, [this, index]() {
            slotEditRule(index);
        });
    }
    if (selectedItemCount > 0) {
        menu.addSeparator();
        menu.addAction(QIcon::fromTheme(QStringLiteral("list-remove")), i18n("Remove Rule"), this, [this, selectedIndexes]() {
            slotRemoveRules(selectedIndexes);
        });
    }
    menu.exec(viewport()->mapToGlobal(pos));
}

void CustomDebugListView::slotRemoveRules(const QModelIndexList &selectedIndexes)
{
    if (selectedIndexes.isEmpty()) {
        return;
    }
    const QString str = i18np("Do you want to remove this rule?", "Do you want to remove these %1 rules?", selectedIndexes.count());

    if (KMessageBox::ButtonCode::SecondaryAction
        == KMessageBox::warningTwoActions(this, str, i18n("Remove Rule"), KStandardGuiItem::remove(), KStandardGuiItem::cancel())) {
        return;
    }
#if 0
    for (int i = 0; i < lst.count(); ++i) {
        QListWidgetItem *item = lst.at(i);
        delete item;
    }
#endif
}

void CustomDebugListView::slotEditRule(const QModelIndex &index)
{
    const QString rule = mLoggingCategoryModel->index(index.row(), LoggingCategoryModel::DisplayRuleRole).data().toString();
    QPointer<ConfigureCustomSettingDialog> dlg = new ConfigureCustomSettingDialog(this);
    dlg->setRule(rule);
    if (dlg->exec()) {
        const QString ruleStr = dlg->rule();
        if (!ruleStr.isEmpty()) {
            const LoggingCategory cat = KDebugSettingsUtil::convertRuleStrToLoggingCategory(ruleStr);
            // TODO mLoggingCategoryModel->insertCategories({tmp});
        }
    }
    delete dlg;
}

void CustomDebugListView::slotAddRule()
{
    QPointer<ConfigureCustomSettingDialog> dlg = new ConfigureCustomSettingDialog(this);
    if (dlg->exec()) {
        const QString ruleStr = dlg->rule();
        const LoggingCategory cat = KDebugSettingsUtil::convertRuleStrToLoggingCategory(ruleStr);
        if (mLoggingCategoryModel->addCategory(cat)) {
            qDebug() << " categorie already exist";
        }
    }

    delete dlg;
}
