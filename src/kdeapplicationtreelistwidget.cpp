/*
  Copyright (c) 2015 Montel Laurent <montel@kde.org>

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

#include "kdeapplicationtreelistwidget.h"
#include "categorytypecombobox.h"
#include <QHeaderView>

KDEApplicationTreeListWidgetItem::KDEApplicationTreeListWidgetItem(const QString &category, QTreeWidget *parent)
    : QTreeWidgetItem(parent),
      mCategory(category)
{
    setCheckState(Description, Qt::Checked);
    mCategoryTypeCombobox = new CategoryTypeComboBox;
    treeWidget()->setItemWidget(this, CategoryType, mCategoryTypeCombobox);
}

KDEApplicationTreeListWidgetItem::~KDEApplicationTreeListWidgetItem()
{

}

void KDEApplicationTreeListWidgetItem::setType(const QString &type)
{
    mCategoryTypeCombobox->setType(type);
}

QString KDEApplicationTreeListWidgetItem::logName() const
{
    return mCategory;
}

void KDEApplicationTreeListWidgetItem::setLogName(const QString &category)
{
    mCategory = category;
}

LoggingCategory KDEApplicationTreeListWidgetItem::rule()
{
    LoggingCategory cat;
    cat.enabled = checkState(Description) == Qt::Checked;
    cat.logName = mCategory;
    cat.type = mCategoryTypeCombobox->type();
    return cat;
}

KDEApplicationTreeListWidget::KDEApplicationTreeListWidget(QWidget *parent)
    : QTreeWidget(parent)
{
    setColumnCount(2);
    setRootIsDecorated(false);
    header()->hide();
}

KDEApplicationTreeListWidget::~KDEApplicationTreeListWidget()
{

}

void KDEApplicationTreeListWidget::selectAllDebugCategories()
{
    for (int i = 0; i < topLevelItemCount(); ++i) {
        QTreeWidgetItem *itemWidget = topLevelItem(i);
        itemWidget->setCheckState(KDEApplicationTreeListWidgetItem::Description, Qt::Checked);
    }
}

void KDEApplicationTreeListWidget::deSelectAllDebugCategories()
{
    for (int i = 0; i < topLevelItemCount(); ++i) {
        QTreeWidgetItem *itemWidget = topLevelItem(i);
        itemWidget->setCheckState(KDEApplicationTreeListWidgetItem::Description, Qt::Unchecked);
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
    Q_FOREACH (const LoggingCategory &cat, list) {
        KDEApplicationTreeListWidgetItem *item = new KDEApplicationTreeListWidgetItem(cat.logName, this);
        item->setText(KDEApplicationTreeListWidgetItem::Description, cat.description);
        item->setCheckState(KDEApplicationTreeListWidgetItem::Description, cat.enabled ? Qt::Checked : Qt::Unchecked);
        item->setType(cat.type);
    }
    resizeColumnToContents(KDEApplicationTreeListWidgetItem::Description);
}

void KDEApplicationTreeListWidget::insertCategories(const LoggingCategory::List &list)
{
    addListItems(list, false);
}

LoggingCategory::List KDEApplicationTreeListWidget::rules()
{
    LoggingCategory::List lst;
    for (int i = 0; i < topLevelItemCount(); ++i) {
        KDEApplicationTreeListWidgetItem *listWidgetItem = static_cast<KDEApplicationTreeListWidgetItem *>(topLevelItem(i));
        LoggingCategory cat = listWidgetItem->rule();
        if (cat.isValid()) {
            lst.append(cat);
        }
    }
    return lst;
}

