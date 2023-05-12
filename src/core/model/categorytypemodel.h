/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "libkdebugsettingscore_export.h"
#include <QAbstractListModel>

class LIBKDEBUGSETTINGSCORE_EXPORT CategoryTypeModel : public QAbstractListModel
{
public:
    explicit CategoryTypeModel(QObject *parent = nullptr);
    ~CategoryTypeModel() override;
};
