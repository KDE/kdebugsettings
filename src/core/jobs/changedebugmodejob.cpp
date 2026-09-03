/*
    SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "changedebugmodejob.h"

#include "kdebugsettingscore_debug.h"
#include "kdebugsettingsloadingcategories.h"
#include "kdebugsettingsutil.h"
#include "saverulesjob.h"

using namespace Qt::Literals::StringLiterals;
ChangeDebugModeJob::ChangeDebugModeJob() = default;

ChangeDebugModeJob::~ChangeDebugModeJob() = default;

bool ChangeDebugModeJob::canStart() const
{
    if (!debugModeIsValid(mDebugMode)) {
        return false;
    }
    if (mWithoutArguments) {
        return true;
    }
    if (mLoggingCategoriesName.isEmpty()) {
        return false;
    }
    return true;
}

bool ChangeDebugModeJob::start() const
{
    if (!canStart()) {
        return false;
    }
    KDebugSettingsLoadingCategories loading;
    loading.readQtLoggingFile();
    const LoggingCategory::LoggingType type = convertDebugModeToLoggingType(mDebugMode);
    // The category names are matched exactly: a substring match would make
    // "--debug-mode Full foo" change foobar too.
    bool foundCategory = mWithoutArguments;
    LoggingCategory::List customCategories = loading.customCategories();
    for (int i = 0, total = customCategories.count(); i < total; ++i) {
        LoggingCategory cat = customCategories[i];
        if (mWithoutArguments) {
            cat.loggingType = type;
            customCategories[i] = std::move(cat);
        } else if (mLoggingCategoriesName.contains(cat.categoryName)) {
            cat.loggingType = type;
            customCategories[i] = std::move(cat);
            foundCategory = true;
        }
    }
    LoggingCategory::List qtKdeCategories = loading.qtKdeCategories();
    for (int i = 0, total = qtKdeCategories.count(); i < total; ++i) {
        LoggingCategory cat = qtKdeCategories[i];
        if (mWithoutArguments) {
            cat.loggingType = type;
            qtKdeCategories[i] = std::move(cat);
        } else if (mLoggingCategoriesName.contains(cat.categoryName)) {
            cat.loggingType = type;
            qtKdeCategories[i] = std::move(cat);
            foundCategory = true;
        }
    }
    if (!foundCategory) {
        qCWarning(KDEBUGSETTINGSCORE_LOG) << "No logging category found for" << mLoggingCategoriesName;
        return false;
    }

    // Only the categories which differ from their default severity are saved,
    // as the GUI does: otherwise changing a single category on the command line
    // would freeze the defaults of all the known categories in qtlogging.ini.
    LoggingCategory::List kdeRules;
    kdeRules.reserve(qtKdeCategories.count());
    for (const LoggingCategory &cat : std::as_const(qtKdeCategories)) {
        if (!cat.hasDefaultSeverity() && cat.isValid()) {
            kdeRules.append(cat);
        }
    }

    SaveRulesJob job;
    job.setFileName(KDebugSettingsUtil::qtFileName());
    job.setListKde(kdeRules);
    job.setListCustom(customCategories);
    if (!job.start()) {
        qCWarning(KDEBUGSETTINGSCORE_LOG) << "Impossible to save in file " << job.fileName();
        return false;
    }
    return true;
}

LoggingCategory::LoggingType ChangeDebugModeJob::convertDebugModeToLoggingType(const QString &value) const
{
    if (value == "Full"_L1) {
        return LoggingCategory::LoggingType::All;
    } else if (value == "Info"_L1) {
        return LoggingCategory::LoggingType::Info;
    } else if (value == "Warning"_L1) {
        return LoggingCategory::LoggingType::Warning;
    } else if (value == "Critical"_L1) {
        return LoggingCategory::LoggingType::Critical;
    } else if (value == "Off"_L1) {
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
    if (convertDebugModeToLoggingType(value) == LoggingCategory::LoggingType::Undefined) {
        return false;
    }
    return true;
}
