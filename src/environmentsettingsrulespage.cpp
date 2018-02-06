/*
  Copyright (c) 2015-2018 Montel Laurent <montel@kde.org>

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
    mRichTextEdit = new EnvironmentPlainTextEdit(this);
    mRichTextEdit->setReadOnly(true);
    mRichTextEdit->setObjectName(QStringLiteral("richtext"));
    mainLayout->addWidget(lab);
    mainLayout->addWidget(mRichTextEdit);
}

EnvironmentSettingsRulesPage::~EnvironmentSettingsRulesPage()
{

}

void EnvironmentSettingsRulesPage::setRules(const QString &rules)
{
    const QString information = QStringLiteral("<qt><b>") + i18n("These rules cannot be edited with this application. You need to set them in QT_LOGGING_RULES variable directly.") + QStringLiteral("</b><qt>");
    QString newRules = rules;
    mRichTextEdit->setHtml(information + i18n("Current rules:") + QStringLiteral("<br>") + newRules.replace(QLatin1String("\n"), QLatin1String("<br>")));
}
