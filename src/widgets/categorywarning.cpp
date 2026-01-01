/*
    SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "categorywarning.h"
#include <KLocalizedString>

CategoryWarning::CategoryWarning(QWidget *parent)
    : KMessageWidget(parent)
{
    setVisible(false);
    setMessageType(KMessageWidget::Warning);
    setText(i18n("A custom rule \'*=true\' or \'*=false\' is present, which may override more specific rules. It is better to remove it."));
    setWordWrap(true);
}

CategoryWarning::~CategoryWarning() = default;

#include "moc_categorywarning.cpp"
