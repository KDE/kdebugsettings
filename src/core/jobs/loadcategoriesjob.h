/*
    SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "kdeloggingcategory.h"
#include "libkdebugsettingscore_export.h"
#include "loggingcategory.h"
#include "renamecategory.h"

class LIBKDEBUGSETTINGSCORE_EXPORT LoadCategoriesJob
{
public:
    LoadCategoriesJob();
    void start();
    void setCategories(const KdeLoggingCategory::List &categories);
    void setRenamedCategories(const RenameCategory::List &renameCategories);

    [[nodiscard]] LoggingCategory::List customCategories() const;

    [[nodiscard]] LoggingCategory::List qtKdeCategories() const;

    void setFileName(const QString &filename);
    [[nodiscard]] bool foundOverrideRule() const;

private:
    KdeLoggingCategory::List mCategories;
    LoggingCategory::List mCustomCategories;
    LoggingCategory::List mQtKdeCategories;
    RenameCategory::List mRenameCategories;
    QString mFileName;
    bool mFoundOverrideRule = false;
};
