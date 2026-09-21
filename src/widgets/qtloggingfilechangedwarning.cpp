/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "qtloggingfilechangedwarning.h"
#include <KLocalizedString>

QtLoggingFileChangedWarning::QtLoggingFileChangedWarning(QWidget *parent)
    : KMessageWidget(parent)
{
    setVisible(false);
    setMessageType(KMessageWidget::Warning);
    setText(i18n("qtlogging.ini was changed. Do you want to reload it?"));
    setWordWrap(true);
}

QtLoggingFileChangedWarning::~QtLoggingFileChangedWarning() = default;
#include "moc_qtloggingfilechangedwarning.cpp"
