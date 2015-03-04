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

#include "kdeapplicationdebugsettingpage.h"
#include "kdeapplicationlistwidget.h"
#include <KLocalizedString>
#include <KListWidgetSearchLine>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QEvent>
#include <QKeyEvent>

KDEApplicationDebugSettingPage::KDEApplicationDebugSettingPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    mListWidget = new KDEApplicationListWidget;
    mListWidget->setObjectName(QStringLiteral("listwidget"));

    mListWidgetSearchLine = new KListWidgetSearchLine(this, mListWidget);
    mListWidgetSearchLine->setClickMessage(i18n("Search..."));
    mListWidgetSearchLine->setObjectName(QStringLiteral("searchline"));
    mainLayout->addWidget(mListWidgetSearchLine);

    mainLayout->addWidget(mListWidget);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    mainLayout->addLayout(buttonLayout);

    mSelectAll = new QPushButton(i18n("Select All"));
    mSelectAll->setObjectName(QStringLiteral("selectall"));
    buttonLayout->addWidget(mSelectAll);
    connect(mSelectAll, &QAbstractButton::clicked, this, &KDEApplicationDebugSettingPage::slotSelectAll);

    mDeselectAll = new QPushButton(i18n("Deselect All"));
    mDeselectAll->setObjectName(QStringLiteral("deselectall"));
    buttonLayout->addWidget(mDeselectAll);
    connect(mDeselectAll, &QAbstractButton::clicked, this, &KDEApplicationDebugSettingPage::slotDeselectAll);
    mListWidgetSearchLine->installEventFilter(this);
}

KDEApplicationDebugSettingPage::~KDEApplicationDebugSettingPage()
{

}

bool KDEApplicationDebugSettingPage::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress && obj == mListWidgetSearchLine) {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        if((key->key() == Qt::Key_Enter) || (key->key() == Qt::Key_Return))
        {
            event->accept();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void KDEApplicationDebugSettingPage::slotSelectAll()
{
    mListWidget->selectAllDebugCategories();
}

void KDEApplicationDebugSettingPage::slotDeselectAll()
{
    mListWidget->deSelectAllDebugCategories();
}

void KDEApplicationDebugSettingPage::fillList(const Category::List &list)
{
    mListWidget->fillList(list);
}

Category::List KDEApplicationDebugSettingPage::rules()
{
    return mListWidget->rules();
}
