/*
    SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "libkdebugsettings_private_export.h"
#include "loggingcategory.h"
#include <QTreeView>

class KDEApplicationLoggingCategoryModel;
class KDEApplicationLoggingCategoryProxyModel;
class LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT KDEApplicationTreeView : public QTreeView
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

    [[nodiscard]] LoggingCategory::List rules(bool forceSavingAllRules) const;

private:
    KDEApplicationLoggingCategoryModel *mKdeApplicationLoggingCategoryModel = nullptr;
    KDEApplicationLoggingCategoryProxyModel *const mKdeApplicationLoggingCategoryProxyModel;
};
