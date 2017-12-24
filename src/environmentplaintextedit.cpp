/*
  Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

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
