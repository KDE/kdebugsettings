/*
    SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "libkdebugsettings_export.h"
#include <QTextEdit>
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
    LIBKDEBUGSETTINGS_NO_EXPORT void slotGeneralPaletteChanged();

    QColor mTextColor;
};
