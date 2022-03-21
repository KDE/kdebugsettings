/*
    SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "libkdebugsettings_private_export.h"
#include <KMessageWidget>
class LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT CategoryWarning : public KMessageWidget
{
    Q_OBJECT
public:
    explicit CategoryWarning(QWidget *parent = nullptr);
    ~CategoryWarning() override;
};
