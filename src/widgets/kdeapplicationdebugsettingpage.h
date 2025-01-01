/*
    SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "libkdebugsettings_export.h"
#include "loggingcategory.h"
#include <QWidget>
class QPushButton;
class QLineEdit;
class KDEApplicationTreeView;
class LIBKDEBUGSETTINGS_EXPORT KDEApplicationDebugSettingPage : public QWidget
{
    Q_OBJECT
public:
    explicit KDEApplicationDebugSettingPage(QWidget *parent = nullptr);
    ~KDEApplicationDebugSettingPage() override;
    [[nodiscard]] LoggingCategory::List rules(bool forceSavingAllRules) const;
    void insertCategories(const LoggingCategory::List &list);

    void restoreToDefault();

    void forceFocus();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    LIBKDEBUGSETTINGS_NO_EXPORT void slotSelectAllDebug();
    LIBKDEBUGSETTINGS_NO_EXPORT void slotDeselectAllDebug();
    LIBKDEBUGSETTINGS_NO_EXPORT void slotDeselectAllMessages();

    QLineEdit *const mSearchLineEdit;
    QPushButton *const mEnableDebug;
    QPushButton *const mTurnOffDebug;
    QPushButton *const mTurnOffAllMessages;
    KDEApplicationTreeView *const mKdeApplicationTreeView;
};
