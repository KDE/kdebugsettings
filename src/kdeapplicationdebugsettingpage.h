/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "libkdebugsettings_export.h"
#include "loggingcategory.h"
#include <QWidget>
class QPushButton;
class KDEApplicationTreeListWidget;
class KTreeWidgetSearchLine;
class LIBKDEBUGSETTINGS_EXPORT KDEApplicationDebugSettingPage : public QWidget
{
    Q_OBJECT
public:
    explicit KDEApplicationDebugSettingPage(QWidget *parent = nullptr);
    ~KDEApplicationDebugSettingPage() override;
    void fillList(const LoggingCategory::List &list);
    Q_REQUIRED_RESULT LoggingCategory::List rules(bool forceSavingAllRules) const;
    void insertCategories(const LoggingCategory::List &list);

    void restoreToDefault();

    void forceFocus();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void slotSelectAllDebug();
    void slotDeselectAllDebug();
    void slotDeselectAllMessages();

    KDEApplicationTreeListWidget *const mTreeListWidget;
    KTreeWidgetSearchLine *const mTreeListWidgetSearchLine;
    QPushButton *const mEnableDebug;
    QPushButton *const mTurnOffDebug;
    QPushButton *const mTurnOffAllMessages;
};

