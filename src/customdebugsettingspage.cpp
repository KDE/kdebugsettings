/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "customdebugsettingspage.h"
#include "configurecustomsettingdialog.h"
#include "kdebugsettingsutil.h"
#include <KListWidgetSearchLine>
#include <KLocalizedString>
#include <KMessageBox>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QListWidget>
#include <QMenu>
#include <QPointer>
#include <QPushButton>
#include <QVBoxLayout>
#include <kwidgetsaddons_version.h>

CustomDebugSettingsPage::CustomDebugSettingsPage(QWidget *parent)
    : QWidget(parent)
    , mListWidget(new QListWidget(this))
    , mAddRule(new QPushButton(i18n("Add..."), this))
    , mEditRule(new QPushButton(i18n("Edit..."), this))
    , mRemoveRule(new QPushButton(i18n("Remove..."), this))
{
    auto mainLayout = new QVBoxLayout(this);

    auto lab = new QLabel(i18n("Rules:"), this);
    lab->setObjectName(QStringLiteral("custom_label"));
    mainLayout->addWidget(lab);

    auto horizontalLayout = new QHBoxLayout;
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(horizontalLayout);

    auto vbox = new QVBoxLayout;
    horizontalLayout->addLayout(vbox);

    mListWidget->setObjectName(QStringLiteral("custom_listwidget"));
    mListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    mListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mListWidget, &QListWidget::itemSelectionChanged, this, &CustomDebugSettingsPage::updateButtons);
    connect(mListWidget, &QListWidget::itemDoubleClicked, this, &CustomDebugSettingsPage::slotEditRule);
    connect(mListWidget, &QListWidget::customContextMenuRequested, this, &CustomDebugSettingsPage::slotCustomContextMenu);
    mTreeListWidgetSearchLine = new KListWidgetSearchLine(this, mListWidget);
    mTreeListWidgetSearchLine->setObjectName(QStringLiteral("searchline"));
    mTreeListWidgetSearchLine->setPlaceholderText(i18n("Search..."));
    vbox->addWidget(mTreeListWidgetSearchLine);
    vbox->addWidget(mListWidget);

    auto buttonLayout = new QVBoxLayout;
    horizontalLayout->addLayout(buttonLayout);

    mAddRule->setObjectName(QStringLiteral("add_rule"));
    buttonLayout->addWidget(mAddRule);
    connect(mAddRule, &QAbstractButton::clicked, this, &CustomDebugSettingsPage::slotAddRule);

    mEditRule->setObjectName(QStringLiteral("edit_rule"));
    buttonLayout->addWidget(mEditRule);
    connect(mEditRule, &QAbstractButton::clicked, this, &CustomDebugSettingsPage::slotEditRule);

    mRemoveRule->setObjectName(QStringLiteral("remove_rule"));
    buttonLayout->addWidget(mRemoveRule);
    buttonLayout->addStretch();
    connect(mRemoveRule, &QAbstractButton::clicked, this, &CustomDebugSettingsPage::slotRemoveRules);
    updateButtons();
    mTreeListWidgetSearchLine->installEventFilter(this);
}

CustomDebugSettingsPage::~CustomDebugSettingsPage() = default;

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

void CustomDebugSettingsPage::slotCustomContextMenu(const QPoint &pos)
{
    QMenu menu(this);
    const auto selectedItemCount{mListWidget->selectedItems().count()};
    menu.addAction(QIcon::fromTheme(QStringLiteral("list-add")), i18n("Add Rule..."), this, &CustomDebugSettingsPage::slotAddRule);
    if (selectedItemCount == 1) {
        menu.addAction(QIcon::fromTheme(QStringLiteral("document-edit")), i18n("Edit Rule"), this, &CustomDebugSettingsPage::slotEditRule);
    }
    if (selectedItemCount > 0) {
        menu.addSeparator();
        menu.addAction(QIcon::fromTheme(QStringLiteral("list-remove")), i18n("Remove Rule"), this, &CustomDebugSettingsPage::slotRemoveRules);
    }
    menu.exec(mListWidget->viewport()->mapToGlobal(pos));
}

void CustomDebugSettingsPage::updateButtons()
{
    mEditRule->setEnabled(mListWidget->selectedItems().count() == 1);
    mRemoveRule->setEnabled(!mListWidget->selectedItems().isEmpty());
}

void CustomDebugSettingsPage::fillList(const LoggingCategory::List &list)
{
    for (const LoggingCategory &cat : list) {
        QString ruleStr;
        ruleStr = cat.categoryName;
        switch (cat.loggingType) {
        case LoggingCategory::Undefined:
        case LoggingCategory::All:
            break;
        case LoggingCategory::Info:
            ruleStr += QStringLiteral(".info");
            break;
        case LoggingCategory::Warning:
            ruleStr += QStringLiteral(".warning");
            break;
        case LoggingCategory::Debug:
            ruleStr += QStringLiteral(".debug");
            break;
        case LoggingCategory::Critical:
            ruleStr += QStringLiteral(".critical");
            break;
        case LoggingCategory::Off:
            break;
        }
        if (cat.enabled) {
            ruleStr += QStringLiteral("=true");
        } else {
            ruleStr += QStringLiteral("=false");
        }
        new QListWidgetItem(ruleStr, mListWidget);
    }
}

LoggingCategory::List CustomDebugSettingsPage::rules() const
{
    LoggingCategory::List lst;
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
    return lst;
}

void CustomDebugSettingsPage::slotRemoveRules()
{
    const QList<QListWidgetItem *> lst = mListWidget->selectedItems();
    if (lst.isEmpty()) {
        return;
    }
    const QString str = i18np("Do you want to remove this rule?", "Do you want to remove these %1 rules?", lst.count());

    if (KMessageBox::ButtonCode::SecondaryAction
        == KMessageBox::warningTwoActions(this, str, i18n("Remove Rule"), KStandardGuiItem::remove(), KStandardGuiItem::cancel())) {
        return;
    }
    for (int i = 0; i < lst.count(); ++i) {
        QListWidgetItem *item = lst.at(i);
        delete item;
    }
}

void CustomDebugSettingsPage::slotEditRule()
{
    if (mListWidget->selectedItems().count() == 1) {
        QListWidgetItem *item = mListWidget->selectedItems().at(0);
        if (item) {
            QPointer<ConfigureCustomSettingDialog> dlg = new ConfigureCustomSettingDialog(this);
            dlg->setRule(item->text());
            if (dlg->exec()) {
                const QString ruleStr = dlg->rule();
                if (!ruleStr.isEmpty()) {
                    item->setText(dlg->rule());
                }
            }
            delete dlg;
        }
    }
}

void CustomDebugSettingsPage::slotAddRule()
{
    QPointer<ConfigureCustomSettingDialog> dlg = new ConfigureCustomSettingDialog(this);
    if (dlg->exec()) {
        const QString ruleStr = dlg->rule();
        if (!ruleStr.isEmpty()) {
            bool alreadyAdded = false;
            const int number(mListWidget->count());
            for (int i = 0; i < number; ++i) {
                if (ruleStr == mListWidget->item(i)->text()) {
                    alreadyAdded = true;
                    break;
                }
            }
            if (!alreadyAdded) {
                mListWidget->addItem(ruleStr);
            }
        }
    }
    delete dlg;
}
