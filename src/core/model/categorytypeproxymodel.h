/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "libkdebugsettingscore_export.h"
#include <QSortFilterProxyModel>

class LIBKDEBUGSETTINGSCORE_EXPORT CategoryTypeProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit CategoryTypeProxyModel(QObject *parent = nullptr);
    ~CategoryTypeProxyModel() override;
};
