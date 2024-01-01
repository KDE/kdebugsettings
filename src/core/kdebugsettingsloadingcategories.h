/*
    SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "kdeloggingcategory.h"
#include "libkdebugsettingscore_export.h"
#include "loggingcategory.h"
#include "renamecategory.h"
#include <QString>

class LIBKDEBUGSETTINGSCORE_EXPORT KDebugSettingsLoadingCategories
{
public:
    KDebugSettingsLoadingCategories();
    ~KDebugSettingsLoadingCategories();

    void readQtLoggingFile();

    [[nodiscard]] QString environmentrules() const;
    [[nodiscard]] RenameCategory::List renameCategoriesList() const;
    [[nodiscard]] KdeLoggingCategory::List categoriesList() const;
    [[nodiscard]] LoggingCategory::List customCategories() const;
    [[nodiscard]] LoggingCategory::List qtKdeCategories() const;
    [[nodiscard]] bool foundOverrideRule() const;

    void readCategoriesFiles(const QString &path);

private:
    KdeLoggingCategory::List mCategoriesList;
    RenameCategory::List mRenameCategoriesList;
    QString mEnvironmentrules;

    LoggingCategory::List mCustomCategories;
    LoggingCategory::List mQtKdeCategories;
    bool mFoundOverrideRule = false;
};
