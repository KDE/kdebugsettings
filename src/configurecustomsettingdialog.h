/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "kdebugsettingsdialog.h"
#include "libkdebugsettings_export.h"
#include <QDialog>

class ConfigureCustomSettingWidget;
class LIBKDEBUGSETTINGS_EXPORT ConfigureCustomSettingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigureCustomSettingDialog(QWidget *parent = nullptr);
    ~ConfigureCustomSettingDialog() override;
    void setRule(const QString &rule);
    Q_REQUIRED_RESULT QString rule() const;

private:
    ConfigureCustomSettingWidget *const mCustomSettingWidget;
};

