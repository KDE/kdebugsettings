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

    void slotAddRule();

    Q_REQUIRED_RESULT LoggingCategoryModel *loggingCategoryModel() const;
    void setLoggingCategoryModel(LoggingCategoryModel *newLoggingCategoryModel);

private:
    void slotEditRule(const QModelIndex &index);
    void slotRemoveRules(const QModelIndexList &selectedIndexes);
    void slotCustomContextMenuRequested(const QPoint &pos);
    LoggingCategoryModel *mLoggingCategoryModel = nullptr;
    CustomDebugProxyModel *mCustomDebugProxyModel = nullptr;
};
