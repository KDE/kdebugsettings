/*
    SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "customdebuglistview.h"
using namespace Qt::Literals::StringLiterals;

#include "configurecustomsettingdialog.h"
#include "kdebugsettings_debug.h"
#include "kdebugsettingsutil.h"
#include "model/customloggingcategorymodel.h"
#include "model/customloggingcategoryproxymodel.h"

#include <KLocalizedString>
#include <KMessageBox>

#include <QAction>
#include <QMenu>
#include <QPointer>

CustomDebugListView::CustomDebugListView(QWidget *parent)
    : QListView(parent)
    , mCustomLoggingCategoryProxyModel(new CustomLoggingCategoryProxyModel(this))
{
    mCustomLoggingCategoryProxyModel->setObjectName("mCustomDebugProxyModel"_L1);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    connect(this, &CustomDebugListView::customContextMenuRequested, this, &CustomDebugListView::slotCustomContextMenuRequested);
    connect(this, &CustomDebugListView::doubleClicked, this, &CustomDebugListView::slotEditRule);
}

CustomDebugListView::~CustomDebugListView() = default;

void CustomDebugListView::slotCustomContextMenuRequested(const QPoint &pos)
{
    const QModelIndex idx = indexAt(pos);
    const QModelIndex index = mCustomLoggingCategoryProxyModel->mapToSource(idx);
    QMenu menu(this);
    const QModelIndexList selectedIndexes = selectionModel()->selectedRows();
    const auto selectedItemCount{selectedIndexes.count()};
    menu.addAction(QIcon::fromTheme(u"list-add"_s), i18nc("@action", "Add Rule…"), this, &CustomDebugListView::slotAddRule);
    if (index.isValid() && selectedItemCount == 1) {
        menu.addAction(QIcon::fromTheme(u"document-edit"_s), i18nc("@action", "Edit Rule"), this, [this, index]() {
            slotEditRule(index);
        });
    }
    if (selectedItemCount > 0) {
        menu.addSeparator();
        menu.addAction(QIcon::fromTheme(u"list-remove"_s), i18np("Remove Rule", "Remove Rules", selectedItemCount), this, [this, selectedIndexes]() {
            slotRemoveRules(selectedIndexes);
        });
    }
    menu.exec(viewport()->mapToGlobal(pos));
}

CustomLoggingCategoryModel *CustomDebugListView::loggingCategoryModel() const
{
    return mCustomLoggingCategoryModel;
}

void CustomDebugListView::setLoggingCategoryModel(CustomLoggingCategoryModel *newLoggingCategoryModel)
{
    if (mCustomLoggingCategoryModel) {
        qCWarning(KDEBUGSETTINGS_LOG) << " There is a problem as there already has a model";
    }
    mCustomLoggingCategoryModel = newLoggingCategoryModel;
    mCustomLoggingCategoryModel->setObjectName("mLoggingCategoryModel"_L1);

    mCustomLoggingCategoryProxyModel->setSourceModel(mCustomLoggingCategoryModel);
    setModel(mCustomLoggingCategoryProxyModel);
    connect(mCustomLoggingCategoryModel, &QAbstractListModel::rowsRemoved, this, &CustomDebugListView::updateButtonsRequested);
    connect(mCustomLoggingCategoryModel, &QAbstractListModel::rowsInserted, this, &CustomDebugListView::updateButtonsRequested);
    connect(mCustomLoggingCategoryModel, &QAbstractListModel::modelReset, this, &CustomDebugListView::updateButtonsRequested);
}

void CustomDebugListView::slotRemoveRules(const QModelIndexList &selectedIndexes)
{
    if (selectedIndexes.isEmpty()) {
        return;
    }
    const auto numberOfRules{selectedIndexes.count()};
    const QString str = i18np("Do you want to remove this rule?", "Do you want to remove these %1 rules?", numberOfRules);

    if (KMessageBox::ButtonCode::SecondaryAction
        == KMessageBox::warningTwoActions(this,
                                          str,
                                          i18np("Remove Rule", "Remove Rules", numberOfRules),
                                          KStandardGuiItem::remove(),
                                          KStandardGuiItem::cancel())) {
        return;
    }
    LoggingCategory::List categories;
    for (const auto &index : selectedIndexes) {
        const auto cat = mCustomLoggingCategoryModel->index(index.row()).data(CustomLoggingCategoryModel::CategoryRole).value<LoggingCategory>();
        categories.append(cat);
    }
    mCustomLoggingCategoryModel->removeCategory(categories);
}

void CustomDebugListView::slotEditRule(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    const QString rule = mCustomLoggingCategoryModel->index(index.row()).data(CustomLoggingCategoryModel::DisplayRuleRole).toString();
    QPointer<ConfigureCustomSettingDialog> dlg = new ConfigureCustomSettingDialog(this);
    dlg->setRule(rule);
    if (dlg->exec()) {
        const QString ruleStr = dlg->rule();
        if (!ruleStr.isEmpty()) {
            const LoggingCategory cat = KDebugSettingsUtil::convertRuleStrToLoggingCategory(ruleStr);

            mCustomLoggingCategoryModel->setData(index, QVariant::fromValue(cat), CustomLoggingCategoryModel::CategoryRole);
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
        if (mCustomLoggingCategoryModel->addCategory(cat)) {
            qCDebug(KDEBUGSETTINGS_LOG) << " categorie already exist";
        }
    }

    delete dlg;
}

void CustomDebugListView::removeRules()
{
    const QModelIndexList selectedIndexes = selectionModel()->selectedRows();
    slotRemoveRules(selectedIndexes);
}

void CustomDebugListView::editRule()
{
    slotEditRule(selectionModel()->currentIndex());
}

void CustomDebugListView::setFilterRuleStr(const QString &str)
{
    mCustomLoggingCategoryProxyModel->setFilterText(str);
}

#include "moc_customdebuglistview.cpp"
