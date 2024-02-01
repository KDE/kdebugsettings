/*
    SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "environmentsettingsrulespage.h"
#include "environmentplaintextedit.h"
#include <KLocalizedString>
#include <QVBoxLayout>

EnvironmentSettingsRulesPage::EnvironmentSettingsRulesPage(QWidget *parent)
    : QWidget(parent)
    , mRichTextEdit(new EnvironmentPlainTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mRichTextEdit->setReadOnly(true);
    mRichTextEdit->setObjectName(QLatin1StringView("richtext"));
    mainLayout->addWidget(mRichTextEdit);
}

EnvironmentSettingsRulesPage::~EnvironmentSettingsRulesPage() = default;

void EnvironmentSettingsRulesPage::setRules(const QString &rules)
{
    const QString information = QLatin1StringView("<qt><b>")
        + i18n("These rules cannot be edited with this application. You need to set them in QT_LOGGING_RULES variable directly.")
        + QLatin1StringView("</b><qt>");
    QString newRules = rules;
    mRichTextEdit->setHtml(information + i18n("Current rules:") + QStringLiteral("<br>") + newRules.replace(QLatin1Char('\n'), QLatin1StringView("<br>")));
}

#include "moc_environmentsettingsrulespage.cpp"
