/*
    SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "groupmanagementdialog.h"
#include "groupmanagementwidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>

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
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), myGroupManagementDialogGroupName);
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void GroupManagementDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myGroupManagementDialogGroupName);
    KWindowConfig::saveWindowSize(windowHandle(), group);
}
