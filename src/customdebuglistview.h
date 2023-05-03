/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#pragma once

#include "loggingcategory.h"
#include <QListView>
class CustomDebugModel;
class CustomDebugListView : public QListView
{
    Q_OBJECT
public:
    explicit CustomDebugListView(QWidget *parent = nullptr);
    ~CustomDebugListView() override;
    void setLoggingCategories(const LoggingCategory::List &list);

private:
    CustomDebugModel *const mCustomDebugModel;
};
