/*
    SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "kdeloggingcategory.h"
#include "libkdebugsettings_export.h"
#include "loggingcategory.h"
#include "renamecategory.h"
#include <QString>

class LIBKDEBUGSETTINGS_EXPORT KDebugSettingsLoadingCategories
{
public:
    KDebugSettingsLoadingCategories();
    ~KDebugSettingsLoadingCategories();

    void readQtLoggingFile();

    Q_REQUIRED_RESULT QString environmentrules() const;
    Q_REQUIRED_RESULT RenameCategory::List renameCategoriesList() const;
    Q_REQUIRED_RESULT KdeLoggingCategory::List categoriesList() const;
    Q_REQUIRED_RESULT LoggingCategory::List customCategories() const;
    Q_REQUIRED_RESULT LoggingCategory::List qtKdeCategories() const;
    Q_REQUIRED_RESULT bool foundOverrideRule() const;

    void readCategoriesFiles(const QString &path);

private:
    KdeLoggingCategory::List mCategoriesList;
    RenameCategory::List mRenameCategoriesList;
    QString mEnvironmentrules;

    LoggingCategory::List mCustomCategories;
    LoggingCategory::List mQtKdeCategories;
    bool mFoundOverrideRule = false;
};

