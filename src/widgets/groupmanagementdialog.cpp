/*
    SPDX-FileCopyrightText: 2020-2024 Laurent Montel <montel@kde.org>

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
    mGroupManagementWidget->setObjectName(QLatin1StringView("mGroupManagementWidget"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    buttonBox->setObjectName(QLatin1StringView("buttonBox"));
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
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(myGroupManagementDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void GroupManagementDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(myGroupManagementDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_groupmanagementdialog.cpp"
