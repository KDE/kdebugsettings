/*
    SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdeapplicationdebugsettingpage.h"
#include "kdeapplicationtreelistwidget.h"
#include <KLocalizedString>
#include <KTreeWidgetSearchLine>
#include <QEvent>
#include <QKeyEvent>
#include <QPushButton>
#include <QVBoxLayout>

KDEApplicationDebugSettingPage::KDEApplicationDebugSettingPage(QWidget *parent)
    : QWidget(parent)
    , mTreeListWidget(new KDEApplicationTreeListWidget(this))
    , mTreeListWidgetSearchLine(new KTreeWidgetSearchLine(this, mTreeListWidget))
    , mEnableDebug(new QPushButton(i18n("Enable All Debug"), this))
    , mTurnOffDebug(new QPushButton(i18n("Turn Off Debug"), this))
    , mTurnOffAllMessages(new QPushButton(i18n("Turn Off All Messages"), this))
{
    auto mainLayout = new QVBoxLayout(this);

    mTreeListWidget->setObjectName(QStringLiteral("listwidget"));

    mTreeListWidgetSearchLine->setPlaceholderText(i18n("Search..."));
    mTreeListWidgetSearchLine->setObjectName(QStringLiteral("searchline"));
    mTreeListWidgetSearchLine->setSearchColumns(mTreeListWidget->searchColumns());
    mainLayout->addWidget(mTreeListWidgetSearchLine);

    mainLayout->addWidget(mTreeListWidget);

    auto buttonLayout = new QHBoxLayout;
    mainLayout->addLayout(buttonLayout);

    mEnableDebug->setObjectName(QStringLiteral("selectall"));
    buttonLayout->addWidget(mEnableDebug);
    connect(mEnableDebug, &QAbstractButton::clicked, this, &KDEApplicationDebugSettingPage::slotSelectAllDebug);

    mTurnOffDebug->setObjectName(QStringLiteral("deselectall"));
    buttonLayout->addWidget(mTurnOffDebug);
    connect(mTurnOffDebug, &QAbstractButton::clicked, this, &KDEApplicationDebugSettingPage::slotDeselectAllDebug);

    mTurnOffAllMessages->setObjectName(QStringLiteral("deselectallmessage"));
    buttonLayout->addWidget(mTurnOffAllMessages);
    connect(mTurnOffAllMessages, &QAbstractButton::clicked, this, &KDEApplicationDebugSettingPage::slotDeselectAllMessages);

    mTreeListWidgetSearchLine->installEventFilter(this);
}

KDEApplicationDebugSettingPage::~KDEApplicationDebugSettingPage() = default;

void KDEApplicationDebugSettingPage::forceFocus()
{
    mTreeListWidgetSearchLine->setFocus();
}

bool KDEApplicationDebugSettingPage::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress && obj == mTreeListWidgetSearchLine) {
        auto key = static_cast<QKeyEvent *>(event);
        if ((key->key() == Qt::Key_Enter) || (key->key() == Qt::Key_Return)) {
            event->accept();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void KDEApplicationDebugSettingPage::slotSelectAllDebug()
{
    mTreeListWidget->selectAllDebugCategories();
}

void KDEApplicationDebugSettingPage::slotDeselectAllDebug()
{
    mTreeListWidget->deSelectAllDebugCategories();
}

void KDEApplicationDebugSettingPage::slotDeselectAllMessages()
{
    mTreeListWidget->deSelectAllMessagesCategories();
}

void KDEApplicationDebugSettingPage::fillList(const LoggingCategory::List &list)
{
    mTreeListWidget->fillList(list);
}

LoggingCategory::List KDEApplicationDebugSettingPage::rules(bool forceSavingAllRules) const
{
    return mTreeListWidget->rules(forceSavingAllRules);
}

void KDEApplicationDebugSettingPage::insertCategories(const LoggingCategory::List &list)
{
    mTreeListWidget->insertCategories(list);
}

void KDEApplicationDebugSettingPage::restoreToDefault()
{
    mTreeListWidget->restoreToDefault();
}
