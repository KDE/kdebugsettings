/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#pragma once

#include "libkdebugsettings_export.h"
#include "loggingcategory.h"
#include <QListView>
class LoggingCategoryModel;
class CustomDebugProxyModel;
class LIBKDEBUGSETTINGS_EXPORT CustomDebugListView : public QListView
{
    Q_OBJECT
public:
    explicit CustomDebugListView(QWidget *parent = nullptr);
    ~CustomDebugListView() override;
    void setLoggingCategories(const LoggingCategory::List &list);

private:
    void slotAddRule();
    void slotEditRule(const QModelIndex &index);
    void slotRemoveRules(const QModelIndexList &selectedIndexes);
    void slotCustomContextMenuRequested(const QPoint &pos);
    LoggingCategoryModel *const mLoggingCategoryModel;
    CustomDebugProxyModel *const mCystomDebugProxyModel;
};
