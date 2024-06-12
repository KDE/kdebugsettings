/*
    SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#pragma once
#include "kdebugsettingsloadingcategories.h"
#include "libkdebugsettingscore_export.h"
#include "model/categorytypemodel.h"
#include "model/customloggingcategorymodel.h"
#include "model/kdeapplicationloggingcategorymodel.h"
#include <QObject>
class LIBKDEBUGSETTINGSCORE_EXPORT LoggingManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CustomLoggingCategoryModel *customCategoryModel READ customCategoryModel CONSTANT)
    Q_PROPERTY(KDEApplicationLoggingCategoryModel *qtKdeCategoryModel READ qtKdeCategoryModel CONSTANT)
    Q_PROPERTY(CategoryTypeModel *categoryTypeModel READ categoryTypeModel CONSTANT)
    Q_PROPERTY(bool foundOverrideRule READ foundOverrideRule CONSTANT)

public:
    static LoggingManager &self();

    ~LoggingManager() override;

    [[nodiscard]] CustomLoggingCategoryModel *customCategoryModel() const;

    [[nodiscard]] KDEApplicationLoggingCategoryModel *qtKdeCategoryModel() const;

    [[nodiscard]] CategoryTypeModel *categoryTypeModel() const;

    [[nodiscard]] Q_INVOKABLE QString environmentrules() const;

    [[nodiscard]] bool foundOverrideRule() const;

    // Remove it when we will port kdebugsettings to models.
    [[nodiscard]] KDebugSettingsLoadingCategories loggings() const;

    void readCategoriesFiles(const QString &path);

    [[nodiscard]] KdeLoggingCategory::List categoriesList() const;

    void readQtLoggingFile();
    void updateLoggingCategories();

private:
    LIBKDEBUGSETTINGSCORE_NO_EXPORT explicit LoggingManager(QObject *parent = nullptr);
    CustomLoggingCategoryModel *const mCustomCategoryModel;
    KDEApplicationLoggingCategoryModel *const mQtKdeCategoryModel;
    CategoryTypeModel *const mCategoryTypeModel;
    KDebugSettingsLoadingCategories mLoggings;
};
