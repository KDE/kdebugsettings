/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "qtloggingfilechangedwarning.h"
#include <KLocalizedString>
using namespace Qt::Literals::StringLiterals;
QtLoggingFileChangedWarning::QtLoggingFileChangedWarning(QWidget *parent)
    : KMessageWidget(parent)
{
    setVisible(false);
    setMessageType(KMessageWidget::Warning);
    setText(i18n("qtlogging.ini was changed. Do you want to reload it?"));
    setWordWrap(true);

    auto reloadAction = new QAction(i18n("Reload"), this);
    reloadAction->setObjectName("reloadAction"_L1);
    connect(reloadAction, &QAction::triggered, this, &QtLoggingFileChangedWarning::reload);
    addAction(reloadAction);
}

QtLoggingFileChangedWarning::~QtLoggingFileChangedWarning() = default;
#include "moc_qtloggingfilechangedwarning.cpp"
