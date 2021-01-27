/*
    SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "groupmanagementdialog.h"
#include "groupmanagementwidget.h"

#include <KLocalizedString>

#include <KConfigGroup>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>

namespace
{
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
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    connect(buttonBox, &QDialogButtonBox::rejected, this, &GroupManagementDialog::reject);
    mainLayout->addWidget(mGroupManagementWidget);
    mainLayout->addWidget(buttonBox);
    readConfig();
    connect(mGroupManagementWidget, &GroupManagementWidget::groupsChanged, this, &GroupManagementDialog::groupsChanged);
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
