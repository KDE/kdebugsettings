/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "previewgeneratedfiledialog.h"
#include "previewgeneratedfilewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QScreen>
#include <QVBoxLayout>
#include <QWindow>

namespace
{
static const char myGroupPreviewDialogName[] = "PreviewDialog";
}

using namespace Qt::Literals::StringLiterals;
PreviewGeneratedFileDialog::PreviewGeneratedFileDialog(QWidget *parent)
    : QDialog(parent)
    , mPreviewGeneratedFileWidget(new PreviewGeneratedFileWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Preview Generated File"));
    mPreviewGeneratedFileWidget->setObjectName("mPreviewGeneratedFileWidget"_L1);
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    buttonBox->setObjectName("buttonBox"_L1);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &PreviewGeneratedFileDialog::reject);
    mainLayout->addWidget(mPreviewGeneratedFileWidget);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

PreviewGeneratedFileDialog::~PreviewGeneratedFileDialog()
{
    writeConfig();
}

void PreviewGeneratedFileDialog::readConfig()
{
    create(); // ensure a window is created
    const qreal scaleFactor = windowHandle()->screen()->devicePixelRatio();
    windowHandle()->resize(QSize(400 * scaleFactor, 300 * scaleFactor));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myGroupPreviewDialogName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void PreviewGeneratedFileDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myGroupPreviewDialogName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_previewgeneratedfiledialog.cpp"
