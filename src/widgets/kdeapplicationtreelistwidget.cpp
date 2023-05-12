/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdeapplicationtreelistwidget.h"
#include "categorytypecombobox.h"
#include <KLocalizedString>
#include <QHeaderView>

KDEApplicationTreeListWidgetItem::KDEApplicationTreeListWidgetItem(const QString &category, QTreeWidget *parent)
    : QTreeWidgetItem(parent)
    , mCategory(category)
    , mCategoryTypeCombobox(new CategoryTypeComboBox(false))
{
    treeWidget()->setItemWidget(this, CategoryType, mCategoryTypeCombobox);
}

KDEApplicationTreeListWidgetItem::~KDEApplicationTreeListWidgetItem() = default;

void KDEApplicationTreeListWidgetItem::restoreToDefault()
{
    mCategoryTypeCombobox->restoreToDefault();
}

void KDEApplicationTreeListWidgetItem::setType(LoggingCategory::LoggingType type)
{
    mCategoryTypeCombobox->setType(type);
}

void KDEApplicationTreeListWidgetItem::setDefaultCategory(LoggingCategory::LoggingType type)
{
    mCategoryTypeCombobox->setDefaultCategories(type);
}

QString KDEApplicationTreeListWidgetItem::logName() const
{
    return mCategory;
}

void KDEApplicationTreeListWidgetItem::setLogName(const QString &category)
{
    mCategory = category;
}

LoggingCategory KDEApplicationTreeListWidgetItem::rule(bool forceSavingAllRules) const
{
    LoggingCategory cat;
    if (mCategoryTypeCombobox->loggingCategoryIsNotDefault() || forceSavingAllRules) {
        cat.enabled = false;
        cat.categoryName = mCategory;
        cat.loggingType = mCategoryTypeCombobox->type();
    }
    return cat;
}

KDEApplicationTreeListWidget::KDEApplicationTreeListWidget(QWidget *parent)
    : QTreeWidget(parent)
{
    setColumnCount(4);
    setRootIsDecorated(false);
    setUniformRowHeights(true);
    setColumnHidden(KDEApplicationTreeListWidgetItem::LogName, true);
    setColumnHidden(KDEApplicationTreeListWidgetItem::IdentifierName, true);
    header()->hide();
}

KDEApplicationTreeListWidget::~KDEApplicationTreeListWidget() = default;

QList<int> KDEApplicationTreeListWidget::searchColumns() const
{
    return {KDEApplicationTreeListWidgetItem::Description, KDEApplicationTreeListWidgetItem::LogName, KDEApplicationTreeListWidgetItem::IdentifierName};
}

void KDEApplicationTreeListWidget::selectAllDebugCategories()
{
    for (int i = 0; i < topLevelItemCount(); ++i) {
        auto itemWidget = static_cast<KDEApplicationTreeListWidgetItem *>(topLevelItem(i));
        if (!itemWidget->isHidden()) {
            itemWidget->setType(LoggingCategory::Debug);
        }
    }
}

void KDEApplicationTreeListWidget::deSelectAllDebugCategories()
{
    for (int i = 0; i < topLevelItemCount(); ++i) {
        auto itemWidget = static_cast<KDEApplicationTreeListWidgetItem *>(topLevelItem(i));
        if (!itemWidget->isHidden()) {
            itemWidget->setType(LoggingCategory::Info);
        }
    }
}

void KDEApplicationTreeListWidget::deSelectAllMessagesCategories()
{
    for (int i = 0; i < topLevelItemCount(); ++i) {
        auto itemWidget = static_cast<KDEApplicationTreeListWidgetItem *>(topLevelItem(i));
        if (!itemWidget->isHidden()) {
            itemWidget->setType(LoggingCategory::Off);
        }
    }
}

void KDEApplicationTreeListWidget::fillList(const LoggingCategory::List &list)
{
    addListItems(list, true);
}

void KDEApplicationTreeListWidget::addListItems(const LoggingCategory::List &list, bool clearList)
{
    if (clearList) {
        clear();
    }
    for (const LoggingCategory &cat : list) {
        auto item = new KDEApplicationTreeListWidgetItem(cat.categoryName, this);
        item->setToolTip(0, cat.generateToolTip());
        item->setText(KDEApplicationTreeListWidgetItem::Description, cat.description);
        item->setType(cat.loggingType);
        item->setDefaultCategory(cat.defaultSeverityType);
        item->setText(KDEApplicationTreeListWidgetItem::LogName, cat.categoryName);
        item->setText(KDEApplicationTreeListWidgetItem::IdentifierName, cat.identifierName);
    }
    resizeColumnToContents(KDEApplicationTreeListWidgetItem::Description);
}

void KDEApplicationTreeListWidget::insertCategories(const LoggingCategory::List &list)
{
    addListItems(list, false);
}

LoggingCategory::List KDEApplicationTreeListWidget::rules(bool forceSavingAllRules) const
{
    LoggingCategory::List lst;
    for (int i = 0; i < topLevelItemCount(); ++i) {
        auto listWidgetItem = static_cast<KDEApplicationTreeListWidgetItem *>(topLevelItem(i));
        const LoggingCategory cat = listWidgetItem->rule(forceSavingAllRules);
        if (cat.isValid()) {
            lst.append(cat);
        }
    }
    return lst;
}

void KDEApplicationTreeListWidget::restoreToDefault()
{
    for (int i = 0; i < topLevelItemCount(); ++i) {
        auto itemWidget = static_cast<KDEApplicationTreeListWidgetItem *>(topLevelItem(i));
        itemWidget->restoreToDefault();
    }
}
