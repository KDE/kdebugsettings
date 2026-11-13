/*
    SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#pragma once
#include "kdebugsettingsloadingcategories.h"
#include "libkdebugsettingscore_export.h"
#include <QObject>
class KDirWatch;
class CategoryTypeModel;
class CustomLoggingCategoryModel;
class CustomLoggingCategoryProxyModel;
class KDEApplicationLoggingCategoryModel;
class KDEApplicationLoggingCategoryProxyModel;
class LIBKDEBUGSETTINGSCORE_EXPORT LoggingManager : public QObject
{
    Q_OBJECT
    Q_MOC_INCLUDE("model/categorytypemodel.h")
    Q_MOC_INCLUDE("model/customloggingcategorymodel.h")
    Q_MOC_INCLUDE("model/customloggingcategoryproxymodel.h")
    Q_MOC_INCLUDE("model/kdeapplicationloggingcategorymodel.h")
    Q_MOC_INCLUDE("model/kdeapplicationloggingcategoryproxymodel.h")
    Q_PROPERTY(CustomLoggingCategoryModel *customCategoryModel READ customCategoryModel CONSTANT)
    Q_PROPERTY(CustomLoggingCategoryProxyModel *customLoggingCategoryProxyModel READ customLoggingCategoryProxyModel CONSTANT)
    Q_PROPERTY(KDEApplicationLoggingCategoryModel *qtKdeCategoryModel READ qtKdeCategoryModel CONSTANT)
    Q_PROPERTY(KDEApplicationLoggingCategoryProxyModel *kdeApplicationLoggingCategoryProxyModel READ kdeApplicationLoggingCategoryProxyModel CONSTANT)
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

    void readCategoriesFiles(const QString &path);

    [[nodiscard]] KdeLoggingCategory::List categoriesList() const;

    void readQtLoggingFile();
    void updateLoggingCategories();

    [[nodiscard]] Q_INVOKABLE bool saveInQtLogging() const;

    [[nodiscard]] Q_INVOKABLE bool saveRules(const QString &path, bool forceSavingAllRules = false) const;

    [[nodiscard]] KDEApplicationLoggingCategoryProxyModel *kdeApplicationLoggingCategoryProxyModel() const;

    [[nodiscard]] CustomLoggingCategoryProxyModel *customLoggingCategoryProxyModel() const;

    [[nodiscard]] QString generateRules() const;

Q_SIGNALS:
    void customLoggingChanged();
    void qtFileNameChanged();

private:
    LIBKDEBUGSETTINGSCORE_NO_EXPORT explicit LoggingManager(QObject *parent = nullptr);
    LIBKDEBUGSETTINGSCORE_NO_EXPORT void slotQtLoggingFileChanged();
    [[nodiscard]] LIBKDEBUGSETTINGSCORE_NO_EXPORT QString readQtLoggingFileContent() const;
    mutable QString mLastKnownQtLoggingContent;
    CustomLoggingCategoryModel *const mCustomCategoryModel;
    CustomLoggingCategoryProxyModel *const mCustomLoggingCategoryProxyModel;
    KDEApplicationLoggingCategoryModel *const mQtKdeCategoryModel;
    CategoryTypeModel *const mCategoryTypeModel;
    KDEApplicationLoggingCategoryProxyModel *const mKdeApplicationLoggingCategoryProxyModel;
    KDebugSettingsLoadingCategories mLoggings;
    KDirWatch *const mDirWatch;
};
