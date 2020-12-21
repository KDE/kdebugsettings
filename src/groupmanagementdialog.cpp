/*
  Copyright (c) 2020 Laurent Montel <montel@kde.org>

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

#include "groupmanagementdialog.h"
#include "groupmanagementwidget.h"

#include <KLocalizedString>

#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <KConfigGroup>
#include <KSharedConfig>

namespace {
static const char myGroupManagementDialogGroupName[] = "GroupManagementDialog";
}

GroupManagementDialog::GroupManagementDialog(QWidget *parent)
    : QDialog(parent)
    , mGroupManagementWidget(new GroupManagementWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Manage Group"));
    mGroupManagementWidget->setObjectName(QStringLiteral("mGroupManagementWidget"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &GroupManagementDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &GroupManagementDialog::reject);
    mainLayout->addWidget(mGroupManagementWidget);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

GroupManagementDialog::~GroupManagementDialog()
{
    writeConfig();
}

void GroupManagementDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), myGroupManagementDialogGroupName);
    const QSize sizeDialog = group.readEntry("Size", QSize(400, 300));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void GroupManagementDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), myGroupManagementDialogGroupName);
    group.writeEntry("Size", size());
}
