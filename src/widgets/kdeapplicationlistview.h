/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "libkdebugsettings_export.h"
#include <QListView>

class LIBKDEBUGSETTINGS_EXPORT KDEApplicationListView : public QListView
{
    Q_OBJECT
public:
    explicit KDEApplicationListView(QWidget *parent = nullptr);
    ~KDEApplicationListView() override;
};
