/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "libkdebugsettings_export.h"
#include "loggingcategory.h"
#include <QTreeView>

class KDEApplicationLoggingCategoryModel;
class KDEApplicationLoggingCategoryProxyModel;
class LIBKDEBUGSETTINGS_EXPORT KDEApplicationTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit KDEApplicationTreeView(QWidget *parent = nullptr);
    ~KDEApplicationTreeView() override;

    void setLoggingCategoryModel(KDEApplicationLoggingCategoryModel *newLoggingCategoryModel);

    void setFilterRuleStr(const QString &str);

    void selectAllDebugCategories();
    void deSelectAllDebugCategories();
    void deSelectAllMessagesCategories();
    void restoreToDefault();

    void insertCategories(const LoggingCategory::List &list);

    Q_REQUIRED_RESULT LoggingCategory::List rules(bool forceSavingAllRules) const;

private:
    KDEApplicationLoggingCategoryModel *mKdeApplicationLoggingCategoryModel = nullptr;
    KDEApplicationLoggingCategoryProxyModel *const mKdeApplicationLoggingCategoryProxyModel;
};
