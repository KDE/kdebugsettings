/*
    SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QToolButton>

#include "libkdebugsettings_private_export.h"
class LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT SaveToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit SaveToolButton(QWidget *parent = nullptr);
    ~SaveToolButton() override;
Q_SIGNALS:
    void saveAsFile();
    void saveAsGroup();
};
