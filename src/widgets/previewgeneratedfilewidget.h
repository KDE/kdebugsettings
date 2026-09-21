/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QWidget>

#include "libkdebugsettings_private_export.h"
class LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT PreviewGeneratedFileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PreviewGeneratedFileWidget(QWidget *parent = nullptr);
    ~PreviewGeneratedFileWidget() override;
};
