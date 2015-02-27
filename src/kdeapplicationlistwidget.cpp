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

#include "kdeapplicationlistwidget.h"
#include <QDebug>

KDeApplicationListWidget::KDeApplicationListWidget(QWidget *parent)
    : QListWidget(parent)
{

}

KDeApplicationListWidget::~KDeApplicationListWidget()
{

}

QStringList KDeApplicationListWidget::rules()
{
    QStringList lst;
    for (int i = 0; i < count(); ++i) {
        QString rule;
        KDeApplicationListWidgetItem *listWidgetItem = static_cast<KDeApplicationListWidgetItem *>(item(i));
        rule = listWidgetItem->category() + QStringLiteral("=%1").arg((listWidgetItem->checkState() == Qt::Checked) ? QStringLiteral("true") : QStringLiteral("false"));
        lst.append(rule);
    }
    return lst;
}

void KDeApplicationListWidget::selectAllDebugCategories()
{
    for (int i = 0; i < count(); ++i) {
        QListWidgetItem *itemWidget = item(i);
        itemWidget->setCheckState(Qt::Checked);
    }
}

void KDeApplicationListWidget::deSelectAllDebugCategories()
{
    for (int i = 0; i < count(); ++i) {
        QListWidgetItem *itemWidget = item(i);
        itemWidget->setCheckState(Qt::Unchecked);
    }
}

void KDeApplicationListWidget::fillList(const Category::List &list)
{
    Q_FOREACH( const Category &cat, list) {
        KDeApplicationListWidgetItem *item = new KDeApplicationListWidgetItem(this);
        item->setText(cat.description);
        item->setCategory(cat.logName);
        item->setCheckState(cat.enabled ? Qt::Checked : Qt::Unchecked);
    }
}

KDeApplicationListWidgetItem::KDeApplicationListWidgetItem(QListWidget *parent)
    : QListWidgetItem(parent)
{
    setFlags(flags() | Qt::ItemIsUserCheckable);
}

KDeApplicationListWidgetItem::~KDeApplicationListWidgetItem()
{

}

QString KDeApplicationListWidgetItem::category() const
{
    return mCategory;
}

void KDeApplicationListWidgetItem::setCategory(const QString &category)
{
    mCategory = category;
}
