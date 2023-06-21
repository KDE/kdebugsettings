/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdeapplicationdebugsettingpage.h"
#include "kdeapplicationtreeview.h"
#include "loggingmanager.h"
#include <KLocalizedString>
#include <QEvent>
#include <QKeyEvent>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

KDEApplicationDebugSettingPage::KDEApplicationDebugSettingPage(QWidget *parent)
    : QWidget(parent)
    , mSearchLineEdit(new QLineEdit(this))
    , mEnableDebug(new QPushButton(i18n("Enable All Debug"), this))
    , mTurnOffDebug(new QPushButton(i18n("Turn Off Debug"), this))
    , mTurnOffAllMessages(new QPushButton(i18n("Turn Off All Messages"), this))
    , mKdeApplicationTreeView(new KDEApplicationTreeView(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mSearchLineEdit->setObjectName(QStringLiteral("mSearchLineEdit"));
    mainLayout->addWidget(mSearchLineEdit);
    mSearchLineEdit->setPlaceholderText(i18n("Search..."));
    mSearchLineEdit->setClearButtonEnabled(true);

    mKdeApplicationTreeView->setObjectName(QStringLiteral("mKdeApplicationTreeView"));
    mainLayout->addWidget(mKdeApplicationTreeView);
    mKdeApplicationTreeView->setLoggingCategoryModel(LoggingManager::self().qtKdeCategoryModel());

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

    mSearchLineEdit->installEventFilter(this);
    connect(mSearchLineEdit, &QLineEdit::textChanged, mKdeApplicationTreeView, &KDEApplicationTreeView::setFilterRuleStr);
}

KDEApplicationDebugSettingPage::~KDEApplicationDebugSettingPage() = default;

void KDEApplicationDebugSettingPage::forceFocus()
{
    mSearchLineEdit->setFocus();
}

bool KDEApplicationDebugSettingPage::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress && obj == mSearchLineEdit) {
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
    mKdeApplicationTreeView->selectAllDebugCategories();
}

void KDEApplicationDebugSettingPage::slotDeselectAllDebug()
{
    mKdeApplicationTreeView->deSelectAllDebugCategories();
}

void KDEApplicationDebugSettingPage::slotDeselectAllMessages()
{
    mKdeApplicationTreeView->deSelectAllMessagesCategories();
}

LoggingCategory::List KDEApplicationDebugSettingPage::rules(bool forceSavingAllRules) const
{
    return mKdeApplicationTreeView->rules(forceSavingAllRules);
}

void KDEApplicationDebugSettingPage::insertCategories(const LoggingCategory::List &list)
{
    mKdeApplicationTreeView->insertCategories(list);
}

void KDEApplicationDebugSettingPage::restoreToDefault()
{
    mKdeApplicationTreeView->restoreToDefault();
}

#include "moc_kdeapplicationdebugsettingpage.cpp"
