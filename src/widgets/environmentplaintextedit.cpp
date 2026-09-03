/*
    SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

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

EnvironmentPlainTextEdit::~EnvironmentPlainTextEdit() = default;

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

        // Don't cache the color: on a theme change the viewport palette is updated after this widget
        // gets its own QEvent::PaletteChange, so a cached value would lag one theme behind.
        QColor color = viewport()->palette().text().color();
        color.setAlpha(128);
        p.setPen(color);

        p.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, i18n("No rules have been defined in the environment variable \"QT_LOGGING_RULES\"."));
    } else {
        QTextEdit::paintEvent(event);
    }
}

#include "moc_environmentplaintextedit.cpp"
