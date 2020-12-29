/*
    SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef KDEAPPLICATIONDEBUGSETTINGPAGE_H
#define KDEAPPLICATIONDEBUGSETTINGPAGE_H

#include <QWidget>
#include "loggingcategory.h"
#include "libkdebugsettings_export.h"
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

    KDEApplicationTreeListWidget *mTreeListWidget = nullptr;
    KTreeWidgetSearchLine *mTreeListWidgetSearchLine = nullptr;
    QPushButton *mEnableDebug = nullptr;
    QPushButton *mTurnOffDebug = nullptr;
    QPushButton *mTurnOffAllMessages = nullptr;
};

#endif // KDEAPPLICATIONDEBUGSETTINGPAGE_H
