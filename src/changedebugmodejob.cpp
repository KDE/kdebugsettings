/*
  Copyright (c) 2019 Montel Laurent <montel@kde.org>

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

#include "changedebugmodejob.h"
#include "kdebugsettingsloadingcategories.h"
#include "kdebugsettings_debug.h"
#include "saverulesjob.h"
#include "kdebugsettingsutil.h"

ChangeDebugModeJob::ChangeDebugModeJob()
{
}

ChangeDebugModeJob::~ChangeDebugModeJob()
{
}

bool ChangeDebugModeJob::canStart() const
{
    if (debugModeIsValid(mDebugMode)) {
        return true;
    }
    if (mWithoutArguments) {
        return true;
    }
    if (mLoggingCategoriesName.isEmpty()) {
        return false;
    }
    return true;
}

bool ChangeDebugModeJob::start()
{
    if (!canStart()) {
        return false;
    }
    KDebugSettingsLoadingCategories loading;
    loading.readQtLoggingFile();
    const LoggingCategory::LoggingType type = convertDebugModeToLoggingType(mDebugMode);
    LoggingCategory::List customCategories = loading.customCategories();
    for (int i = 0; i < customCategories.count(); ++i) {
        LoggingCategory cat = customCategories[i];
        if (mWithoutArguments) {
            cat.loggingType = type;
            customCategories[i] = cat;
        } else {
            for (const QString &categoryName : qAsConst(mLoggingCategoriesName)) {
                if (cat.categoryName.contains(categoryName)) {
                    cat.loggingType = type;
                    customCategories[i] = cat;
                }
            }
        }
    }
    LoggingCategory::List qtKdeCategories = loading.qtKdeCategories();
    for (int i = 0; i < qtKdeCategories.count(); ++i) {
        LoggingCategory cat = qtKdeCategories[i];
        if (mWithoutArguments) {
            cat.loggingType = type;
            qtKdeCategories[i] = cat;
        } else {
            for (const QString &categoryName : qAsConst(mLoggingCategoriesName)) {
                if (cat.categoryName.contains(categoryName)) {
                    cat.loggingType = type;
                    qtKdeCategories[i] = cat;
                }
            }
        }
    }
    SaveRulesJob job;
    job.setFileName(KDebugSettingsUtil::qtFileName());
    job.setListKde(qtKdeCategories);
    job.setListCustom(customCategories);
    if (!job.start()) {
        qCWarning(KDEBUGSETTINGS_LOG) << "Impossible to save in file " << job.fileName();
    }
    return true;
}

LoggingCategory::LoggingType ChangeDebugModeJob::convertDebugModeToLoggingType(const QString &value)
{
    if (value == QLatin1String("Full")) {
        return LoggingCategory::LoggingType::All;
    } else if (value == QLatin1String("Info")) {
        return LoggingCategory::LoggingType::Info;
    } else if (value == QLatin1String("Warning")) {
        return LoggingCategory::LoggingType::Warning;
    } else if(value == QLatin1String("Critical")) {
        return LoggingCategory::LoggingType::Critical;
    } else if (value == QLatin1String("Off")) {
        return LoggingCategory::LoggingType::Off;
    }
    return LoggingCategory::LoggingType::Undefined;
}

void ChangeDebugModeJob::setWithoutArguments(bool b)
{
    mWithoutArguments = b;
}

bool ChangeDebugModeJob::withoutArguments() const
{
    return mWithoutArguments;
}

void ChangeDebugModeJob::setDebugMode(const QString &mode)
{
    mDebugMode = mode;
}

QString ChangeDebugModeJob::debugMode() const
{
    return mDebugMode;
}

QStringList ChangeDebugModeJob::loggingCategoriesName() const
{
    return mLoggingCategoriesName;
}

void ChangeDebugModeJob::setLoggingCategoriesName(const QStringList &loggingCategoryName)
{
    mLoggingCategoriesName = loggingCategoryName;
}

bool ChangeDebugModeJob::debugModeIsValid(const QString &value) const
{
    if (value == QLatin1String("Full") || value == QLatin1String("Info") || value == QLatin1String("Warning") || value == QLatin1String("Critical") || value == QLatin1String("Off")) {
        return true;
    }
    return false;
}
