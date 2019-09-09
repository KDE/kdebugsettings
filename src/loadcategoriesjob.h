/*
  Copyright (c) 2016-2019 Montel Laurent <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

*/

#ifndef LOADCATEGORIESJOB_H
#define LOADCATEGORIESJOB_H

#include "kdeloggingcategory.h"
#include "loggingcategory.h"
#include "renamecategory.h"
#include "kdebugsettingsprivate_export.h"

class KDEBUGSETTINGSPRIVATE_EXPORT LoadCategoriesJob
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
