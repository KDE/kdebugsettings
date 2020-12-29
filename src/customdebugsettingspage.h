/*
    SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef CUSTOMDEBUGSETTINGSPAGE_H
#define CUSTOMDEBUGSETTINGSPAGE_H

#include <QWidget>
#include "loggingcategory.h"
#include "libkdebugsettings_export.h"
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

    QListWidget *mListWidget = nullptr;
    QPushButton *mAddRule = nullptr;
    QPushButton *mEditRule = nullptr;
    QPushButton *mRemoveRule = nullptr;
};

#endif // CUSTOMDEBUGSETTINGSPAGE_H
