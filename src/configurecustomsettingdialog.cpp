/*
    SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "configurecustomsettingdialog.h"
#include "configurecustomsettingwidget.h"

#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

ConfigureCustomSettingDialog::ConfigureCustomSettingDialog(QWidget *parent)
    : QDialog(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    setWindowTitle(i18nc("@title:window", "Add custom rule"));

    mCustomSettingWidget = new ConfigureCustomSettingWidget(this);
    mCustomSettingWidget->setObjectName(QStringLiteral("customsettingwidget"));
    mainLayout->addWidget(mCustomSettingWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    QPushButton *buttonOk = buttonBox->button(QDialogButtonBox::Ok);
    buttonOk->setEnabled(false);
    connect(mCustomSettingWidget, &ConfigureCustomSettingWidget::enableButton, buttonOk, &QWidget::setEnabled);
    mainLayout->addWidget(buttonBox);
}

ConfigureCustomSettingDialog::~ConfigureCustomSettingDialog()
{
}

void ConfigureCustomSettingDialog::setRule(const QString &rule)
{
    setWindowTitle(i18nc("@title:window", "Edit custom rule"));
    mCustomSettingWidget->setRule(rule);
}

QString ConfigureCustomSettingDialog::rule() const
{
    return mCustomSettingWidget->rule();
}
