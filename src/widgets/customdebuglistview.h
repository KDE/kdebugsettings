/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#pragma once

#include "libkdebugsettings_export.h"
#include "loggingcategory.h"
#include <QListView>
class LoggingCategoryModel;
class LIBKDEBUGSETTINGS_EXPORT CustomDebugListView : public QListView
{
    Q_OBJECT
public:
    explicit CustomDebugListView(QWidget *parent = nullptr);
    ~CustomDebugListView() override;
    void setLoggingCategories(const LoggingCategory::List &list);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    void slotAddRule();
    void slotEditRule();
    void slotRemoveRules();
    LoggingCategoryModel *const mLoggingCategoryModel;
};
