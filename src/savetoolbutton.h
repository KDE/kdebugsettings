/*
    SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef SAVETOOLBUTTON_H
#define SAVETOOLBUTTON_H

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

#endif // SAVETOOLBUTTON_H
