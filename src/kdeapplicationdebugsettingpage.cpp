/*
  Copyright (c) 2015-2019 Montel Laurent <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

*/

#include "kdeapplicationdebugsettingpage.h"
#include "kdeapplicationtreelistwidget.h"
#include <KLocalizedString>
#include <QPushButton>
#include <QVBoxLayout>
#include <QEvent>
#include <QKeyEvent>
#include <ktreewidgetsearchline.h>

KDEApplicationDebugSettingPage::KDEApplicationDebugSettingPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mTreeListWidget = new KDEApplicationTreeListWidget(this);
    mTreeListWidget->setObjectName(QStringLiteral("listwidget"));

    mTreeListWidgetSearchLine = new KTreeWidgetSearchLine(this, mTreeListWidget);
    mTreeListWidgetSearchLine->setPlaceholderText(i18n("Search..."));
    mTreeListWidgetSearchLine->setObjectName(QStringLiteral("searchline"));
    mTreeListWidgetSearchLine->setSearchColumns(mTreeListWidget->searchColumns());
    mainLayout->addWidget(mTreeListWidgetSearchLine);

    mainLayout->addWidget(mTreeListWidget);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    mainLayout->addLayout(buttonLayout);

    mEnableDebug = new QPushButton(i18n("Enable All Debug"), this);
    mEnableDebug->setObjectName(QStringLiteral("selectall"));
    buttonLayout->addWidget(mEnableDebug);
    connect(mEnableDebug, &QAbstractButton::clicked, this, &KDEApplicationDebugSettingPage::slotSelectAllDebug);

    mTurnOffDebug = new QPushButton(i18n("Turn Off Debug"), this);
    mTurnOffDebug->setObjectName(QStringLiteral("deselectall"));
    buttonLayout->addWidget(mTurnOffDebug);
    connect(mTurnOffDebug, &QAbstractButton::clicked, this, &KDEApplicationDebugSettingPage::slotDeselectAllDebug);

    mTurnOffAllMessages = new QPushButton(i18n("Turn Off All Messages"), this);
    mTurnOffAllMessages->setObjectName(QStringLiteral("deselectallmessage"));
    buttonLayout->addWidget(mTurnOffAllMessages);
    connect(mTurnOffAllMessages, &QAbstractButton::clicked, this, &KDEApplicationDebugSettingPage::slotDeselectAllMessages);

    mTreeListWidgetSearchLine->installEventFilter(this);
}

KDEApplicationDebugSettingPage::~KDEApplicationDebugSettingPage()
{
}

void KDEApplicationDebugSettingPage::forceFocus()
{
    mTreeListWidgetSearchLine->setFocus();
}

bool KDEApplicationDebugSettingPage::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress && obj == mTreeListWidgetSearchLine) {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
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
