/*
  Copyright (c) 2015-2020 Laurent Montel <montel@kde.org>

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

#include "configurecustomsettingdialog.h"
#include "configurecustomsettingwidget.h"

#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

ConfigureCustomSettingDialog::ConfigureCustomSettingDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setWindowTitle(i18nc("@title:window", "Add custom rule"));

    mCustomSettingWidget = new ConfigureCustomSettingWidget(this);
    mCustomSettingWidget->setObjectName(QStringLiteral("customsettingwidget"));
    mainLayout->addWidget(mCustomSettingWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
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
