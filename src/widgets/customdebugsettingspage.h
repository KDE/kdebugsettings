/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "libkdebugsettings_export.h"
#include "loggingcategory.h"
#include <QWidget>
class QPushButton;
class CustomDebugListView;
class QLineEdit;
class LIBKDEBUGSETTINGS_EXPORT CustomDebugSettingsPage : public QWidget
{
    Q_OBJECT
public:
    explicit CustomDebugSettingsPage(QWidget *parent = nullptr);
    ~CustomDebugSettingsPage() override;

    [[nodiscard]] LoggingCategory::List rules() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    LIBKDEBUGSETTINGS_NO_EXPORT void updateButtons();

    QPushButton *const mEditRule;
    QPushButton *const mRemoveRule;
    QLineEdit *const mSearchLineEdit;
    CustomDebugListView *const mCustomDebugListView;
};
