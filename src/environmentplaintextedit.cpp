/*
    SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "environmentplaintextedit.h"
#include <KLocalizedString>
#include <QPaintEvent>
#include <QPainter>

EnvironmentPlainTextEdit::EnvironmentPlainTextEdit(QWidget *parent)
    : QTextEdit(parent)
{
}

EnvironmentPlainTextEdit::~EnvironmentPlainTextEdit()
{
}

void EnvironmentPlainTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    if (document()->isEmpty()) {
        return;
    }
    QTextEdit::contextMenuEvent(event);
}

void EnvironmentPlainTextEdit::paintEvent(QPaintEvent *event)
{
    if (document()->isEmpty()) {
        QPainter p(viewport());

        QFont font = p.font();
        font.setItalic(true);
        p.setFont(font);

        if (!mTextColor.isValid()) {
            slotGeneralPaletteChanged();
        }
        p.setPen(mTextColor);

        p.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, i18n("No rules have been defined in the environment variable \"QT_LOGGING_RULES\"."));
    } else {
        QTextEdit::paintEvent(event);
    }
}

void EnvironmentPlainTextEdit::slotGeneralPaletteChanged()
{
    const QPalette palette = viewport()->palette();
    QColor color = palette.text().color();
    color.setAlpha(128);
    mTextColor = color;
}
