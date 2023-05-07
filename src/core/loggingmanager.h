/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#pragma once
#include "libkdebugsettingscore_export.h"
#include "model/loggingcategorymodel.h"

#include <QObject>
class LIBKDEBUGSETTINGSCORE_EXPORT LoggingManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LoggingCategoryModel *customCategoryModel READ customCategoryModel CONSTANT)

public:
    explicit LoggingManager(QObject *parent = nullptr);
    ~LoggingManager() override;

    Q_REQUIRED_RESULT LoggingCategoryModel *customCategoryModel() const;

private:
    LoggingCategoryModel *const mCustomCategoryModel;
};
