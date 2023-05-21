/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#pragma once
#include "kdebugsettingsloadingcategories.h"
#include "libkdebugsettingscore_export.h"
#include "model/categorytypemodel.h"
#include "model/loggingcategorymodel.h"

#include <QObject>
class LIBKDEBUGSETTINGSCORE_EXPORT LoggingManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LoggingCategoryModel *customCategoryModel READ customCategoryModel CONSTANT)
    Q_PROPERTY(LoggingCategoryModel *qtKdeCategoryModel READ qtKdeCategoryModel CONSTANT)
    Q_PROPERTY(CategoryTypeModel *categoryTypeModel READ categoryTypeModel CONSTANT)
    Q_PROPERTY(bool foundOverrideRule READ foundOverrideRule CONSTANT)

public:
    static LoggingManager &self();

    ~LoggingManager() override;

    Q_REQUIRED_RESULT LoggingCategoryModel *customCategoryModel() const;

    Q_REQUIRED_RESULT LoggingCategoryModel *qtKdeCategoryModel() const;

    Q_REQUIRED_RESULT CategoryTypeModel *categoryTypeModel() const;

    Q_INVOKABLE Q_REQUIRED_RESULT QString environmentrules() const;

    Q_REQUIRED_RESULT bool foundOverrideRule() const;

private:
    LIBKDEBUGSETTINGSCORE_NO_EXPORT explicit LoggingManager(QObject *parent = nullptr);
    LIBKDEBUGSETTINGSCORE_NO_EXPORT void updateLoggingCategories();
    LoggingCategoryModel *const mCustomCategoryModel;
    LoggingCategoryModel *const mQtKdeCategoryModel;
    CategoryTypeModel *const mCategoryTypeModel;
    KDebugSettingsLoadingCategories mLoggings;
};
