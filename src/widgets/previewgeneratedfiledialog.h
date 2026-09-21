/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "libkdebugsettings_private_export.h"
#include <QDialog>
class PreviewGeneratedFileWidget;
class LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT PreviewGeneratedFileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PreviewGeneratedFileDialog(QWidget *parent = nullptr);
    ~PreviewGeneratedFileDialog() override;

private:
    LIBKDEBUGSETTINGS_NO_EXPORT void readConfig();
    LIBKDEBUGSETTINGS_NO_EXPORT void writeConfig();
    PreviewGeneratedFileWidget *const mPreviewGeneratedFileWidget;
};
