/*
    SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "configurecustomsettingdialog.h"
using namespace Qt::Literals::StringLiterals;

#include "configurecustomsettingwidget.h"

#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

ConfigureCustomSettingDialog::ConfigureCustomSettingDialog(QWidget *parent)
    : QDialog(parent)
    , mCustomSettingWidget(new ConfigureCustomSettingWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    setWindowTitle(i18nc("@title:window", "Add custom rule"));

    mCustomSettingWidget->setObjectName("customsettingwidget"_L1);
    mainLayout->addWidget(mCustomSettingWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName("buttonbox"_L1);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    QPushButton *buttonOk = buttonBox->button(QDialogButtonBox::Ok);
    buttonOk->setEnabled(false);
    connect(mCustomSettingWidget, &ConfigureCustomSettingWidget::enableButton, buttonOk, &QWidget::setEnabled);
    mainLayout->addWidget(buttonBox);
}

ConfigureCustomSettingDialog::~ConfigureCustomSettingDialog() = default;

void ConfigureCustomSettingDialog::setRule(const QString &rule)
{
    setWindowTitle(i18nc("@title:window", "Edit custom rule"));
    mCustomSettingWidget->setRule(rule);
}

QString ConfigureCustomSettingDialog::rule() const
{
    return mCustomSettingWidget->rule();
}

#include "moc_configurecustomsettingdialog.cpp"
