/*
  Copyright (c) 2015-2018 Montel Laurent <montel@kde.org>

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

#ifndef KDEAPPLICATIONTREELISTWIDGET_H
#define KDEAPPLICATIONTREELISTWIDGET_H

#include <QTreeWidget>
#include "loggingcategory.h"
class CategoryTypeComboBox;
class KDEApplicationTreeListWidgetItem : public QTreeWidgetItem
{
public:
    enum ColumnType {
        Description = 0,
        CategoryType = 1
    };

    KDEApplicationTreeListWidgetItem(const QString &logName, QTreeWidget *parent);
    ~KDEApplicationTreeListWidgetItem();

    QString logName() const;
    void setLogName(const QString &category);
    void setType(LoggingCategory::LoggingType type);

    LoggingCategory rule() const;
private:
    QString mCategory;
    CategoryTypeComboBox *mCategoryTypeCombobox = nullptr;
};

class KDEApplicationTreeListWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit KDEApplicationTreeListWidget(QWidget *parent = nullptr);
    ~KDEApplicationTreeListWidget();

    void deSelectAllDebugCategories();
    void selectAllDebugCategories();

    void fillList(const LoggingCategory::List &list);
    void insertCategories(const LoggingCategory::List &list);
    LoggingCategory::List rules() const;
private:
    void addListItems(const LoggingCategory::List &list, bool clearList);
};

#endif // KDEAPPLICATIONTREELISTWIDGET_H
