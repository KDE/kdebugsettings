/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "customdebugsettingspage.h"
#include "customdebuglistview.h"
#include "loggingmanager.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

CustomDebugSettingsPage::CustomDebugSettingsPage(QWidget *parent)
    : QWidget(parent)
    , mEditRule(new QPushButton(i18n("Edit..."), this))
    , mRemoveRule(new QPushButton(i18n("Remove..."), this))
    , mSearchLineEdit(new QLineEdit(this))
    , mCustomDebugListView(new CustomDebugListView(this))
{
    auto mainLayout = new QVBoxLayout(this);

    auto horizontalLayout = new QHBoxLayout;
    horizontalLayout->setContentsMargins({});
    mainLayout->addLayout(horizontalLayout);

    auto vbox = new QVBoxLayout;
    horizontalLayout->addLayout(vbox);

    vbox->addWidget(mSearchLineEdit);
    mSearchLineEdit->setObjectName(QStringLiteral("mSearchLineEdit"));
    vbox->addWidget(mCustomDebugListView);
    mCustomDebugListView->setObjectName(QStringLiteral("mCustomDebugListView"));

    mCustomDebugListView->setLoggingCategoryModel(LoggingManager::self().customCategoryModel());
    auto buttonLayout = new QVBoxLayout;
    horizontalLayout->addLayout(buttonLayout);

    auto addRulePushButton = new QPushButton(i18n("Add..."), this);
    addRulePushButton->setObjectName(QStringLiteral("add_rule"));
    buttonLayout->addWidget(addRulePushButton);
    connect(addRulePushButton, &QAbstractButton::clicked, mCustomDebugListView, &CustomDebugListView::slotAddRule);

    mEditRule->setObjectName(QStringLiteral("edit_rule"));
    buttonLayout->addWidget(mEditRule);
    // connect(mEditRule, &QAbstractButton::clicked, this, &CustomDebugSettingsPage::slotEditRule);

    mRemoveRule->setObjectName(QStringLiteral("remove_rule"));
    buttonLayout->addWidget(mRemoveRule);
    buttonLayout->addStretch();
    // connect(mRemoveRule, &QAbstractButton::clicked, this, &CustomDebugSettingsPage::slotRemoveRules);
    updateButtons();
    // mTreeListWidgetSearchLine->installEventFilter(this);
}

CustomDebugSettingsPage::~CustomDebugSettingsPage() = default;

/*
bool CustomDebugSettingsPage::eventFilter(QObject *obj, QEvent *event)
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
*/

void CustomDebugSettingsPage::updateButtons()
{
    // mEditRule->setEnabled(mListWidget->selectedItems().count() == 1);
    // mRemoveRule->setEnabled(!mListWidget->selectedItems().isEmpty());
}

LoggingCategory::List CustomDebugSettingsPage::rules() const
{
    LoggingCategory::List lst;
    /*
    const int number(mListWidget->count());
    for (int i = 0; i < number; ++i) {
        const KDebugSettingsUtil::LineLoggingQtCategory cat = KDebugSettingsUtil::parseLineLoggingQtCategory(mListWidget->item(i)->text());
        if (cat.isValid()) {
            LoggingCategory tmp;
            tmp.categoryName = cat.logName;
            tmp.enabled = cat.enabled;
            switch (cat.type) {
            case KDebugSettingsUtil::LineLoggingQtCategory::Unknown:
                break;
            case KDebugSettingsUtil::LineLoggingQtCategory::Info:
                tmp.loggingType = LoggingCategory::Info;
                break;
            case KDebugSettingsUtil::LineLoggingQtCategory::Warning:
                tmp.loggingType = LoggingCategory::Warning;
                break;
            case KDebugSettingsUtil::LineLoggingQtCategory::Debug:
                tmp.loggingType = LoggingCategory::Debug;
                break;
            case KDebugSettingsUtil::LineLoggingQtCategory::Critical:
                tmp.loggingType = LoggingCategory::Critical;
                break;
            case KDebugSettingsUtil::LineLoggingQtCategory::All:
                tmp.loggingType = LoggingCategory::All;
                break;
            }
            lst.append(tmp);
        }
    }
    */
    return lst;
}
