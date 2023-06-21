/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "categorywarning.h"
#include <KLocalizedString>

CategoryWarning::CategoryWarning(QWidget *parent)
    : KMessageWidget(parent)
{
    setVisible(false);
    setMessageType(KMessageWidget::Warning);
    setText(i18n("You have a rule as \'*=true\' or \'*=false\' which will override all your specific rule. Better to remove it."));
    setWordWrap(true);
}

CategoryWarning::~CategoryWarning() = default;

#include "moc_categorywarning.cpp"
