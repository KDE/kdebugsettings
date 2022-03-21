/*
    SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "libkdebugsettings_private_export.h"
#include "loggingcategory.h"
#include <QTreeWidget>
class CategoryTypeComboBox;
class LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT KDEApplicationTreeListWidgetItem : public QTreeWidgetItem
{
public:
    enum ColumnType { Description = 0, CategoryType = 1, LogName = 2, IdentifierName = 3 };

    explicit KDEApplicationTreeListWidgetItem(const QString &logName, QTreeWidget *parent);
    ~KDEApplicationTreeListWidgetItem() override;

    Q_REQUIRED_RESULT QString logName() const;
    void setLogName(const QString &category);
    void setType(LoggingCategory::LoggingType type);
    void setDefaultCategory(LoggingCategory::LoggingType type);

    Q_REQUIRED_RESULT LoggingCategory rule(bool forceSavingAllRules) const;
    void restoreToDefault();

private:
    QString mCategory;
    CategoryTypeComboBox *const mCategoryTypeCombobox;
};

class LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT KDEApplicationTreeListWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit KDEApplicationTreeListWidget(QWidget *parent = nullptr);
    ~KDEApplicationTreeListWidget() override;

    void deSelectAllDebugCategories();
    void selectAllDebugCategories();
    void deSelectAllMessagesCategories();

    void fillList(const LoggingCategory::List &list);
    void insertCategories(const LoggingCategory::List &list);
    Q_REQUIRED_RESULT LoggingCategory::List rules(bool forceSavingAllRules) const;

    void restoreToDefault();

    QList<int> searchColumns() const;

private:
    void addListItems(const LoggingCategory::List &list, bool clearList);
    QString generateToolTip(const LoggingCategory &cat);
};
