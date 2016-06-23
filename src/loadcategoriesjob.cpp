/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

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

#include "loadcategoriesjob.h"
#include "kdebugsettingsutil.h"

LoadCategoriesJob::LoadCategoriesJob()
    : mFoundOverrideRule(false)
{

}

void LoadCategoriesJob::setFileName(const QString &filename)
{
    mFileName = filename;
}

bool LoadCategoriesJob::foundOverrideRule() const
{
    return mFoundOverrideRule;
}

LoggingCategory::LoggingType updateLoggingType(const LoggingCategory &cat)
{
    if (!cat.enabled) {
        return LoggingCategory::Off;
    }
    return cat.loggingType;
}

void LoadCategoriesJob::start()
{
    if (mFileName.isEmpty()) {
        return;
    }
    mCustomCategories.clear();
    mQtKdeCategories.clear();
    mFoundOverrideRule = false;

    const QString envPath = mFileName;

    if (!envPath.isEmpty()) {
        const int number(mCategories.count());
        QList<KDebugSettingsUtil::LoadLoggingCategory> qtCategories = KDebugSettingsUtil::readLoggingQtCategories(envPath);
#if 0 //FIXME
        for (int i = 0; i < number; ++i) {
            KdeLoggingCategory kdeCat = mCategories.at(i);
            bool foundInConfigFile = false;
            Q_FOREACH (const LoggingCategory &cat, qtCategories) {
                if (cat.logName == kdeCat.logName) {
                    //TODO optimization ?
                    LoggingCategory tmp(cat);
                    tmp.loggingType = updateLoggingType(tmp);
                    tmp.description = kdeCat.description;
                    mQtKdeCategories.append(tmp);
                    foundInConfigFile = true;
                    qtCategories.removeAll(cat);
                    break;
                }
                if (cat.logName == QLatin1String("*")) {
                    mFoundOverrideRule = true;
                }
            }
            if (!foundInConfigFile) {
                LoggingCategory tmp;
                tmp.description = kdeCat.description;
                tmp.logName = kdeCat.logName;
                tmp.loggingType = updateLoggingType(tmp);
                mQtKdeCategories.append(tmp);
            }
        }
        qDebug()<<" KEEP "<< qtCategories.count();
        Q_FOREACH (const LoggingCategory &cat, qtCategories) {
            LoggingCategory tmp;
            qDebug() << "KEEP" << "cat.description "<< cat.description << " cat.logName" << cat.logName << " cat.logging" << cat.loggingType << " enbable "<< cat.enabled;
            tmp.description = cat.description;
            tmp.logName = cat.logName;
            tmp.loggingType = cat.loggingType;
            tmp.enabled = cat.enabled;
            mCustomCategories.append(tmp);
        }
#endif
    }
}

void LoadCategoriesJob::setCategories(const KdeLoggingCategory::List &categories)
{
    mCategories = categories;
}

LoggingCategory::List LoadCategoriesJob::customCategories() const
{
    return mCustomCategories;
}

LoggingCategory::List LoadCategoriesJob::qtKdeCategories() const
{
    return mQtKdeCategories;
}
