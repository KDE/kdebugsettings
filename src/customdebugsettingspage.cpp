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
#include <KLocalizedString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>

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
    vbox->addWidget(mListWidget);
}

CustomDebugSettingsPage::~CustomDebugSettingsPage()
{

}

void CustomDebugSettingsPage::fillList()
{
    //TODO
}

