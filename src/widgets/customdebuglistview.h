/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "libkdebugsettings_export.h"
#include <QListView>
class CustomLoggingCategoryModel;
class CustomLoggingCategoryProxyModel;
class LIBKDEBUGSETTINGS_EXPORT CustomDebugListView : public QListView
{
    Q_OBJECT
public:
    explicit CustomDebugListView(QWidget *parent = nullptr);
    ~CustomDebugListView() override;

    void slotAddRule();
    void removeRules();
    void editRule();

    Q_REQUIRED_RESULT CustomLoggingCategoryModel *loggingCategoryModel() const;
    void setLoggingCategoryModel(CustomLoggingCategoryModel *newLoggingCategoryModel);

    void setFilterRuleStr(const QString &str);

private:
    void slotEditRule(const QModelIndex &index);
    void slotRemoveRules(const QModelIndexList &selectedIndexes);
    void slotCustomContextMenuRequested(const QPoint &pos);
    CustomLoggingCategoryModel *mCustomLoggingCategoryModel = nullptr;
    CustomLoggingCategoryProxyModel *const mCustomLoggingCategoryProxyModel;
};
