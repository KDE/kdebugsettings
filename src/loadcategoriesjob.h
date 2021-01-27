/*
    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef LOADCATEGORIESJOB_H
#define LOADCATEGORIESJOB_H

#include "kdeloggingcategory.h"
#include "libkdebugsettings_private_export.h"
#include "loggingcategory.h"
#include "renamecategory.h"

class LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT LoadCategoriesJob
{
public:
    LoadCategoriesJob();
    void start();
    void setCategories(const KdeLoggingCategory::List &categories);
    void setRenamedCategories(const RenameCategory::List &renameCategories);

    Q_REQUIRED_RESULT LoggingCategory::List customCategories() const;

    Q_REQUIRED_RESULT LoggingCategory::List qtKdeCategories() const;

    void setFileName(const QString &filename);
    Q_REQUIRED_RESULT bool foundOverrideRule() const;

private:
    KdeLoggingCategory::List mCategories;
    LoggingCategory::List mCustomCategories;
    LoggingCategory::List mQtKdeCategories;
    RenameCategory::List mRenameCategories;
    QString mFileName;
    bool mFoundOverrideRule = false;
};

#endif // LOADCATEGORIESJOB_H
