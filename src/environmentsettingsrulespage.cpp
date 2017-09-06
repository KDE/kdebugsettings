/*
  Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

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

#include "environmentsettingsrulespage.h"
#include "environmentplaintextedit.h"
#include <QVBoxLayout>
#include <QLabel>
#include <KLocalizedString>

EnvironmentSettingsRulesPage::EnvironmentSettingsRulesPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLabel *lab = new QLabel(i18n("Rules:"), this);
    lab->setObjectName(QStringLiteral("label"));
    mPlainTextEdit = new EnvironmentPlainTextEdit(this);
    mPlainTextEdit->setReadOnly(true);
    mPlainTextEdit->setObjectName(QStringLiteral("plaintext"));
    mainLayout->addWidget(lab);
    mainLayout->addWidget(mPlainTextEdit);
}

EnvironmentSettingsRulesPage::~EnvironmentSettingsRulesPage()
{

}

void EnvironmentSettingsRulesPage::setRules(const QString &rules)
{
    QString information = i18n("These rules cannot be edited with this application. You need to set them in QT_LOGGING_RULES variable directly.");
    mPlainTextEdit->setPlainText(information + QLatin1Char('\n') + QLatin1Char('\n') + rules);
}
