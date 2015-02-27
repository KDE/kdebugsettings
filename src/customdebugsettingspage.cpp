/*
  Copyright (c) 2015 Montel Laurent <montel@kde.org>

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

#include "customdebugsettingspage.h"
#include "configurecustomsettingdialog.h"
#include "kdebugsettingsutil.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QPointer>

CustomDebugSettingsPage::CustomDebugSettingsPage(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    setLayout(mainLayout);

    QVBoxLayout *vbox = new QVBoxLayout;
    mainLayout->addLayout(vbox);

    QLabel *lab = new QLabel(i18n("Custom:"));
    lab->setObjectName(QStringLiteral("custom_label"));
    vbox->addWidget(lab);

    mListWidget = new QListWidget;
    mListWidget->setObjectName(QStringLiteral("custom_listwidget"));
    connect(mListWidget, &QListWidget::itemSelectionChanged, this, &CustomDebugSettingsPage::updateButtons);
    connect(mListWidget, &QListWidget::itemDoubleClicked, this, &CustomDebugSettingsPage::slotEditRule);
    vbox->addWidget(mListWidget);

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    mainLayout->addLayout(buttonLayout);

    mAddRule = new QPushButton(i18n("Add..."));
    mAddRule->setObjectName(QStringLiteral("add_rule"));
    buttonLayout->addWidget(mAddRule);
    connect(mAddRule, &QAbstractButton::clicked, this, &CustomDebugSettingsPage::slotAddRule);

    mEditRule = new QPushButton(i18n("Edit..."));;
    mEditRule->setObjectName(QStringLiteral("edit_rule"));
    buttonLayout->addWidget(mEditRule);
    connect(mEditRule, &QAbstractButton::clicked, this, &CustomDebugSettingsPage::slotEditRule);

    mRemoveRule = new QPushButton(i18n("Remove..."));;
    mRemoveRule->setObjectName(QStringLiteral("remove_rule"));
    buttonLayout->addWidget(mRemoveRule);
    buttonLayout->addStretch();
    connect(mRemoveRule, &QAbstractButton::clicked, this, &CustomDebugSettingsPage::slotRemoveRule);
    updateButtons();
}

CustomDebugSettingsPage::~CustomDebugSettingsPage()
{

}

void CustomDebugSettingsPage::updateButtons()
{
    mEditRule->setEnabled(mListWidget->currentItem());
    mRemoveRule->setEnabled(mListWidget->currentItem());
}

void CustomDebugSettingsPage::fillList(const Category::List &list)
{
    Q_FOREACH (const Category &cat, list) {
        QString rule;
        rule = cat.logName;
        if (!cat.type.isEmpty()) {
            rule += QLatin1Char('.') + cat.type;
        }
        if (cat.enabled) {
            rule += QStringLiteral("=true");
        } else {
            rule += QStringLiteral("=false");
        }
        new QListWidgetItem(rule, mListWidget);
    }
}

Category::List CustomDebugSettingsPage::rules()
{
    Category::List lst;
    for (int i = 0; i < mListWidget->count(); ++i) {
        const Category cat = KDebugSettingsUtil::parseLineLoggingQtCategory(mListWidget->item(i)->text());
        if (cat.isValid()) {
            lst.append(cat);
        }
    }
    return lst;
}

void CustomDebugSettingsPage::slotRemoveRule()
{
    QListWidgetItem *item = mListWidget->currentItem();
    if (item) {
        if (KMessageBox::Yes == KMessageBox::warningYesNo(this, i18n("Do you want to remove this rule \"%1\"?", item->text()))) {
            delete item;
        }
    }
}

void CustomDebugSettingsPage::slotEditRule()
{
    QListWidgetItem *item = mListWidget->currentItem();
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

void CustomDebugSettingsPage::slotAddRule()
{
    QPointer<ConfigureCustomSettingDialog> dlg = new ConfigureCustomSettingDialog(this);
    if (dlg->exec()) {
        const QString ruleStr = dlg->rule();
        if (!ruleStr.isEmpty()) {
            mListWidget->addItem(ruleStr);
        }
    }
    delete dlg;
}
