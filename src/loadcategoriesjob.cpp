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

LoggingCategory::LoggingType canDisplayType(const QMap<KDebugSettingsUtil::LoadLoggingCategory::LogType, KDebugSettingsUtil::LoadLoggingCategory::Status> &types)
{
    KDebugSettingsUtil::LoadLoggingCategory::Status warning = types.value(KDebugSettingsUtil::LoadLoggingCategory::Warning);
    KDebugSettingsUtil::LoadLoggingCategory::Status debug = types.value(KDebugSettingsUtil::LoadLoggingCategory::Debug);
    KDebugSettingsUtil::LoadLoggingCategory::Status critical = types.value(KDebugSettingsUtil::LoadLoggingCategory::Critical);
    KDebugSettingsUtil::LoadLoggingCategory::Status info = types.value(KDebugSettingsUtil::LoadLoggingCategory::Info);
    KDebugSettingsUtil::LoadLoggingCategory::Status all = types.value(KDebugSettingsUtil::LoadLoggingCategory::All);

    if (all == KDebugSettingsUtil::LoadLoggingCategory::Enabled) {
        return LoggingCategory::All;
    } else if (all == KDebugSettingsUtil::LoadLoggingCategory::Disabled) {
        return LoggingCategory::Off;
    } else if (warning == KDebugSettingsUtil::LoadLoggingCategory::Enabled &&
               debug == KDebugSettingsUtil::LoadLoggingCategory::Enabled &&
               critical == KDebugSettingsUtil::LoadLoggingCategory::Enabled &&
               info == KDebugSettingsUtil::LoadLoggingCategory::Enabled) {
        return LoggingCategory::All;
    } else if (debug == KDebugSettingsUtil::LoadLoggingCategory::Enabled &&
               warning == KDebugSettingsUtil::LoadLoggingCategory::Enabled &&
               critical == KDebugSettingsUtil::LoadLoggingCategory::Enabled) {
        return LoggingCategory::Debug;
    } else if (info == KDebugSettingsUtil::LoadLoggingCategory::Enabled &&
               warning == KDebugSettingsUtil::LoadLoggingCategory::Enabled &&
               critical == KDebugSettingsUtil::LoadLoggingCategory::Enabled) {
        return LoggingCategory::Info;
    } else if (warning == KDebugSettingsUtil::LoadLoggingCategory::Enabled &&
               critical == KDebugSettingsUtil::LoadLoggingCategory::Enabled) {
        return LoggingCategory::Warning;
    } else if (critical == KDebugSettingsUtil::LoadLoggingCategory::Enabled) {
        return LoggingCategory::Critical;
    } else if (info == KDebugSettingsUtil::LoadLoggingCategory::Enabled &&
               warning == KDebugSettingsUtil::LoadLoggingCategory::UnknownStatus &&
               debug == KDebugSettingsUtil::LoadLoggingCategory::UnknownStatus &&
               critical == KDebugSettingsUtil::LoadLoggingCategory::UnknownStatus) {
        return LoggingCategory::Undefined;
    } else if (warning == KDebugSettingsUtil::LoadLoggingCategory::Enabled &&
               info == KDebugSettingsUtil::LoadLoggingCategory::UnknownStatus &&
               debug == KDebugSettingsUtil::LoadLoggingCategory::UnknownStatus &&
               critical == KDebugSettingsUtil::LoadLoggingCategory::UnknownStatus) {
        return LoggingCategory::Undefined;
    } else if (debug == KDebugSettingsUtil::LoadLoggingCategory::Enabled &&
               info == KDebugSettingsUtil::LoadLoggingCategory::UnknownStatus &&
               warning == KDebugSettingsUtil::LoadLoggingCategory::UnknownStatus &&
               critical == KDebugSettingsUtil::LoadLoggingCategory::UnknownStatus) {
        return LoggingCategory::Undefined;
    } else {
        return LoggingCategory::Off;
    }
}

void LoadCategoriesJob::start()
{
    if (mFileName.isEmpty()) {
        return;
    }
    mCustomCategories.clear();
    mQtKdeCategories.clear();
    mFoundOverrideRule = false;
    const int number(mCategories.count());
    QList<KDebugSettingsUtil::LoadLoggingCategory> qtCategories = KDebugSettingsUtil::readLoggingQtCategories(mFileName);
    for (int i = 0; i < number; ++i) {
        KdeLoggingCategory kdeCat = mCategories.at(i);
        bool foundInConfigFile = false;
        Q_FOREACH (const KDebugSettingsUtil::LoadLoggingCategory &cat, qtCategories) {
            if (cat.logName == kdeCat.logName) {

                LoggingCategory tmp;
                LoggingCategory::LoggingType newType = canDisplayType(cat.loggingTypes);
                if (newType != LoggingCategory::Undefined) {
                    tmp.loggingType = canDisplayType(cat.loggingTypes);
                    if (tmp.loggingType == LoggingCategory::Off) {
                        tmp.enabled = false;
                    }
                    tmp.description = kdeCat.description;
                    tmp.logName = kdeCat.logName;

                    mQtKdeCategories.append(tmp);
                    foundInConfigFile = true;
                    qtCategories.removeAll(cat);
                    break;
                }
            }
            if (cat.logName == QLatin1String("*")) {
                mFoundOverrideRule = true;
            }
        }
        if (!foundInConfigFile) {
            LoggingCategory tmp;
            tmp.description = kdeCat.description;
            tmp.logName = kdeCat.logName;
            tmp.loggingType = LoggingCategory::Info;
            mQtKdeCategories.append(tmp);
        }
    }

    //qDebug()<<" KEEP "<< qtCategories.count();
    Q_FOREACH (const KDebugSettingsUtil::LoadLoggingCategory &cat, qtCategories) {

        QMapIterator<KDebugSettingsUtil::LoadLoggingCategory::LogType, KDebugSettingsUtil::LoadLoggingCategory::Status> i(cat.loggingTypes);
        while (i.hasNext()) {
            i.next();
            if (i.value() != KDebugSettingsUtil::LoadLoggingCategory::UnknownStatus) {
                LoggingCategory tmp;
                tmp.logName = cat.logName;
                switch (i.key()) {
                case KDebugSettingsUtil::LoadLoggingCategory::Unknown:
                    tmp.loggingType = LoggingCategory::Undefined;
                    break;
                case KDebugSettingsUtil::LoadLoggingCategory::Off:
                    tmp.loggingType = LoggingCategory::Off;
                    tmp.enabled = false;
                    break;
                case KDebugSettingsUtil::LoadLoggingCategory::Info:
                    tmp.loggingType = LoggingCategory::Info;
                    break;
                case KDebugSettingsUtil::LoadLoggingCategory::Warning:
                    tmp.loggingType = LoggingCategory::Warning;
                    break;
                case KDebugSettingsUtil::LoadLoggingCategory::Debug:
                    tmp.loggingType = LoggingCategory::Debug;
                    break;
                case KDebugSettingsUtil::LoadLoggingCategory::Critical:
                    tmp.loggingType = LoggingCategory::Critical;
                    break;
                case KDebugSettingsUtil::LoadLoggingCategory::All:
                    tmp.loggingType = LoggingCategory::All;
                    break;
                }
                tmp.enabled = (i.value() == KDebugSettingsUtil::LoadLoggingCategory::Enabled);
                mCustomCategories.append(tmp);

            }
        }
    }
}

void LoadCategoriesJob::setCategories(const KdeLoggingCategory::List &categories)
{
    mCategories = categories;
}

void LoadCategoriesJob::setRenamedCategories(const RenameCategory::List &renameCategories)
{
    mRenameCategories = renameCategories;
}

LoggingCategory::List LoadCategoriesJob::customCategories() const
{
    return mCustomCategories;
}

LoggingCategory::List LoadCategoriesJob::qtKdeCategories() const
{
    return mQtKdeCategories;
}
