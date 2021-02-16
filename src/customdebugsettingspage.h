/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef CUSTOMDEBUGSETTINGSPAGE_H
#define CUSTOMDEBUGSETTINGSPAGE_H

#include "libkdebugsettings_export.h"
#include "loggingcategory.h"
#include <QWidget>
class QListWidget;
class QPushButton;
class LIBKDEBUGSETTINGS_EXPORT CustomDebugSettingsPage : public QWidget
{
    Q_OBJECT
public:
    explicit CustomDebugSettingsPage(QWidget *parent = nullptr);
    ~CustomDebugSettingsPage() override;

    void fillList(const LoggingCategory::List &list);
    Q_REQUIRED_RESULT LoggingCategory::List rules() const;

private:
    void slotRemoveRules();
    void slotAddRule();
    void slotEditRule();
    void updateButtons();
    void slotCustomContextMenu(const QPoint &pos);

    QListWidget *const mListWidget;
    QPushButton *const mAddRule;
    QPushButton *const mEditRule;
    QPushButton *const mRemoveRule;
};

#endif // CUSTOMDEBUGSETTINGSPAGE_H
