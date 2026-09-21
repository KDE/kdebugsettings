/*
    SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "loggingmanager.h"
#include "jobs/saverulesjob.h"
#include "kdebugsettingsutil.h"
#include <KDirWatch>
#include <QFile>

LoggingManager::LoggingManager(QObject *parent)
    : QObject{parent}
    , mCustomCategoryModel(new CustomLoggingCategoryModel(this))
    , mCustomLoggingCategoryProxyModel(new CustomLoggingCategoryProxyModel(this))
    , mQtKdeCategoryModel(new KDEApplicationLoggingCategoryModel(this))
    , mCategoryTypeModel(new CategoryTypeModel(this))
    , mKdeApplicationLoggingCategoryProxyModel(new KDEApplicationLoggingCategoryProxyModel(this))
    , mDirWatch(new KDirWatch(this))
{
    mKdeApplicationLoggingCategoryProxyModel->setSourceModel(mQtKdeCategoryModel);
    mCustomLoggingCategoryProxyModel->setSourceModel(mCustomCategoryModel);
    mLoggings.readQtLoggingFile();
    updateLoggingCategories();

    connect(mCustomCategoryModel, &QAbstractItemModel::rowsInserted, this, &LoggingManager::customLoggingChanged);
    connect(mCustomCategoryModel, &QAbstractItemModel::rowsRemoved, this, &LoggingManager::customLoggingChanged);
    connect(mCustomCategoryModel, &QAbstractItemModel::dataChanged, this, &LoggingManager::customLoggingChanged);

    connect(mQtKdeCategoryModel,
            &QAbstractItemModel::dataChanged,
            this,
            [this]([[maybe_unused]] const QModelIndex &topLeft, [[maybe_unused]] const QModelIndex &, const QList<int> &roles) {
                if (roles.isEmpty() || roles.contains(KDEApplicationLoggingCategoryModel::qmlRole(KDEApplicationLoggingCategoryModel::LoggingTypeRole))) {
                    Q_EMIT customLoggingChanged();
                }
            });

    const QString qtFileName = KDebugSettingsUtil::qtFileName();
    mDirWatch->addFile(qtFileName);
    connect(mDirWatch, &KDirWatch::dirty, this, &LoggingManager::slotQtLoggingFileChanged);
    connect(mDirWatch, &KDirWatch::created, this, &LoggingManager::slotQtLoggingFileChanged);
    connect(mDirWatch, &KDirWatch::deleted, this, &LoggingManager::slotQtLoggingFileChanged);
    mLastKnownQtLoggingContent = readQtLoggingFileContent();
}

CustomLoggingCategoryProxyModel *LoggingManager::customLoggingCategoryProxyModel() const
{
    return mCustomLoggingCategoryProxyModel;
}

KDEApplicationLoggingCategoryProxyModel *LoggingManager::kdeApplicationLoggingCategoryProxyModel() const
{
    return mKdeApplicationLoggingCategoryProxyModel;
}

LoggingManager &LoggingManager::self()
{
    static LoggingManager c;
    return c;
}

LoggingManager::~LoggingManager() = default;

CustomLoggingCategoryModel *LoggingManager::customCategoryModel() const
{
    return mCustomCategoryModel;
}

KDEApplicationLoggingCategoryModel *LoggingManager::qtKdeCategoryModel() const
{
    return mQtKdeCategoryModel;
}

CategoryTypeModel *LoggingManager::categoryTypeModel() const
{
    return mCategoryTypeModel;
}

QString LoggingManager::environmentrules() const
{
    return mLoggings.environmentrules();
}

bool LoggingManager::foundOverrideRule() const
{
    return mLoggings.foundOverrideRule();
}

void LoggingManager::updateLoggingCategories()
{
    mCustomCategoryModel->setLoggingCategories(mLoggings.customCategories());
    mQtKdeCategoryModel->setLoggingCategories(mLoggings.qtKdeCategories());
}

bool LoggingManager::saveInQtLogging() const
{
    return saveRules(KDebugSettingsUtil::qtFileName());
}

QString LoggingManager::generateRules() const
{
    SaveRulesJob job;
    job.setListCustom(customCategoryModel()->loggingCategories());
    job.setListKde(kdeApplicationLoggingCategoryProxyModel()->rules(false));
    return job.generateRules();
}

bool LoggingManager::saveRules(const QString &path, bool forceSavingAllRules) const
{
    SaveRulesJob job;
    job.setFileName(path);
    job.setListCustom(customCategoryModel()->loggingCategories());
    job.setListKde(kdeApplicationLoggingCategoryProxyModel()->rules(forceSavingAllRules));
    if (!job.start()) {
        return false;
    }
    if (path == KDebugSettingsUtil::qtFileName()) {
        // We need to refresh if it's qtFileName not when we saveAs...
        mLastKnownQtLoggingContent = readQtLoggingFileContent();
    }
    return true;
}

QString LoggingManager::readQtLoggingFileContent() const
{
    QFile f(KDebugSettingsUtil::qtFileName());
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return {};
    }
    return QString::fromUtf8(f.readAll());
}

void LoggingManager::slotQtLoggingFileChanged()
{
    const QString content = readQtLoggingFileContent();
    if (content == mLastKnownQtLoggingContent) {
        return;
    }
    mLastKnownQtLoggingContent = content;
    Q_EMIT qtFileNameChanged();
}

void LoggingManager::readCategoriesFiles(const QString &path)
{
    mLoggings.readCategoriesFiles(path);
}

KdeLoggingCategory::List LoggingManager::categoriesList() const
{
    return mLoggings.categoriesList();
}

void LoggingManager::readQtLoggingFile()
{
    mLoggings.readQtLoggingFile();
}

#include "moc_loggingmanager.cpp"
