/*
    SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "libkdebugsettings_private_export.h"
#include <QListView>
class CustomLoggingCategoryModel;
class CustomLoggingCategoryProxyModel;
class LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT CustomDebugListView : public QListView
{
    Q_OBJECT
public:
    explicit CustomDebugListView(QWidget *parent = nullptr);
    ~CustomDebugListView() override;

    void slotAddRule();
    void removeRules();
    void editRule();

    [[nodiscard]] CustomLoggingCategoryModel *loggingCategoryModel() const;
    void setLoggingCategoryModel(CustomLoggingCategoryModel *newLoggingCategoryModel);

    void setFilterRuleStr(const QString &str);

Q_SIGNALS:
    void updateButtonsRequested();

private:
    LIBKDEBUGSETTINGS_NO_EXPORT void slotEditRule(const QModelIndex &index);
    LIBKDEBUGSETTINGS_NO_EXPORT void slotRemoveRules(const QModelIndexList &selectedIndexes);
    LIBKDEBUGSETTINGS_NO_EXPORT void slotCustomContextMenuRequested(const QPoint &pos);
    CustomLoggingCategoryModel *mCustomLoggingCategoryModel = nullptr;
    CustomLoggingCategoryProxyModel *const mCustomLoggingCategoryProxyModel;
};
