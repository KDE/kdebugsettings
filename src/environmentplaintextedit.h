/*
    SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef ENVIRONMENTPLAINTEXTEDIT_H
#define ENVIRONMENTPLAINTEXTEDIT_H

#include <QTextEdit>
#include "libkdebugsettings_export.h"
class QPaintEvent;
class LIBKDEBUGSETTINGS_EXPORT EnvironmentPlainTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit EnvironmentPlainTextEdit(QWidget *parent = nullptr);
    ~EnvironmentPlainTextEdit() override;

protected:
    void paintEvent(QPaintEvent *event) override;

    void contextMenuEvent(QContextMenuEvent *event) override;
private:
    void slotGeneralPaletteChanged();

    QColor mTextColor;
};

#endif // ENVIRONMENTPLAINTEXTEDIT_H
