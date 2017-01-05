/*
  Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

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
    mCategoryTypeCombobox = new CategoryTypeComboBox(false);
    treeWidget()->setItemWidget(this, CategoryType, mCategoryTypeCombobox);
}

KDEApplicationTreeListWidgetItem::~KDEApplicationTreeListWidgetItem()
{

}

void KDEApplicationTreeListWidgetItem::setType(LoggingCategory::LoggingType type)
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
    cat.enabled = false;
    cat.logName = mCategory;
    cat.loggingType = mCategoryTypeCombobox->type();
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
        KDEApplicationTreeListWidgetItem *itemWidget = static_cast<KDEApplicationTreeListWidgetItem *>(topLevelItem(i));
        itemWidget->setType(LoggingCategory::Info);
    }
}

void KDEApplicationTreeListWidget::deSelectAllDebugCategories()
{
    for (int i = 0; i < topLevelItemCount(); ++i) {
        KDEApplicationTreeListWidgetItem *itemWidget = static_cast<KDEApplicationTreeListWidgetItem *>(topLevelItem(i));
        itemWidget->setType(LoggingCategory::Off);
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
        KDEApplicationTreeListWidgetItem *item = new KDEApplicationTreeListWidgetItem(cat.logName, this);
        item->setText(KDEApplicationTreeListWidgetItem::Description, cat.description);
        item->setType(cat.loggingType);
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

