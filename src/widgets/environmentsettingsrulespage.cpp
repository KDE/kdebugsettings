/*
    SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "environmentsettingsrulespage.h"
using namespace Qt::Literals::StringLiterals;

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
    mRichTextEdit->setObjectName("richtext"_L1);
    mainLayout->addWidget(mRichTextEdit);
}

EnvironmentSettingsRulesPage::~EnvironmentSettingsRulesPage() = default;

void EnvironmentSettingsRulesPage::setRules(const QString &rules)
{
    const QString information =
        "<qt><b>"_L1 + i18n("These rules cannot be edited with this application. You need to set them in QT_LOGGING_RULES variable directly.") + "</b><qt>"_L1;
    QString newRules = rules;
    mRichTextEdit->setHtml(information + i18n("Current rules:") + u"<br>"_s + newRules.replace(u'\n', "<br>"_L1));
}

#include "moc_environmentsettingsrulespage.cpp"
