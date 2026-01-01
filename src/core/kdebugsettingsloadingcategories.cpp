/*
    SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdebugsettingsloadingcategories.h"
using namespace Qt::Literals::StringLiterals;

#include "jobs/loadcategoriesjob.h"
#include "kdebugsettingsutil.h"
#include <QDir>
#include <QLibraryInfo>
#include <QStandardPaths>

KDebugSettingsLoadingCategories::KDebugSettingsLoadingCategories() = default;

KDebugSettingsLoadingCategories::~KDebugSettingsLoadingCategories() = default;

void KDebugSettingsLoadingCategories::readQtLoggingFile()
{
    mCategoriesList.clear();
    const QString envPath = QStandardPaths::locate(QStandardPaths::GenericConfigLocation, u"QtProject/qtlogging.ini"_s);
    if (!envPath.isEmpty()) {
        readCategoriesFiles(envPath);
    } else {
        const QString dataPath = QDir(QLibraryInfo::path(QLibraryInfo::DataPath)).absoluteFilePath(u"qtlogging.ini"_s);
        readCategoriesFiles(dataPath);
    }
}

void KDebugSettingsLoadingCategories::readCategoriesFiles(const QString &path)
{
    // KDE debug categories area
    const QString confAreasFile = QStandardPaths::locate(QStandardPaths::GenericDataLocation, u"qlogging-categories6/kde.categories"_s);
    if (!confAreasFile.isEmpty()) {
        KDebugSettingsUtil::readLoggingCategories(confAreasFile, mCategoriesList, false);
    }

    mRenameCategoriesList.clear();
    // Load *.renamecategories file in QStandardPaths::ConfigLocation for kde apps.
    const QStringList dirs = QStandardPaths::locateAll(QStandardPaths::ConfigLocation, QString(), QStandardPaths::LocateDirectory)
        + QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, u"qlogging-categories6/"_s, QStandardPaths::LocateDirectory);
    for (const QString &dir : dirs) {
        const QStringList fileNames = QDir(dir).entryList(QStringList() << u"*.renamecategories"_s);
        for (const QString &file : fileNames) {
            mRenameCategoriesList.append(KDebugSettingsUtil::readRenameCategories(dir + file));
        }
    }
    // TODO add load rename file from external kde apps.
    const QStringList dirs2 = QStandardPaths::locateAll(QStandardPaths::GenericConfigLocation, u"qdebug.categories/"_s, QStandardPaths::LocateDirectory);
    // qDebug() << " dirs 2 " << dirs2;
    for (const QString &dir : dirs2) {
        const QStringList fileNames = QDir(dir).entryList(QStringList() << u"*.renamecategories"_s);
        for (const QString &file : fileNames) {
            mRenameCategoriesList.append(KDebugSettingsUtil::readRenameCategories(dir + file));
        }
    }

    // Load *.categories file in QStandardPaths::ConfigLocation for kde apps.
    for (const QString &dir : dirs) {
        const QStringList fileNames = QDir(dir).entryList(QStringList() << u"*.categories"_s);
        for (const QString &file : fileNames) {
            if (file != "kde.categories"_L1) {
                KDebugSettingsUtil::readLoggingCategories(dir + file, mCategoriesList, true);
            }
        }
    }

    // Load *.categories files in qdebug.categories for external KDE apps.
    for (const QString &dir : dirs2) {
        const QStringList fileNames = QDir(dir).entryList(QStringList() << u"*.categories"_s);
        for (const QString &file : fileNames) {
            KDebugSettingsUtil::readLoggingCategories(dir + u'/' + file, mCategoriesList, true);
        }
    }

    const QByteArray rulesFilePath = qgetenv("QT_LOGGING_CONF");
    if (!rulesFilePath.isEmpty()) {
        // const QList<KDebugSettingsUtil::LoadLoggingCategory> envCategories = KDebugSettingsUtil::readLoggingQtCategories(QString::fromLatin1(rulesFilePath));
        // TODO
    }

    mEnvironmentrules = QString::fromLatin1(qgetenv("QT_LOGGING_RULES"));
    // qt logging.ini
    LoadCategoriesJob job;
    job.setFileName(path);
    job.setCategories(mCategoriesList);
    job.setRenamedCategories(mRenameCategoriesList);
    job.start();

    mCustomCategories = job.customCategories();
    mQtKdeCategories = job.qtKdeCategories();
    mFoundOverrideRule = job.foundOverrideRule();
}

bool KDebugSettingsLoadingCategories::foundOverrideRule() const
{
    return mFoundOverrideRule;
}

LoggingCategory::List KDebugSettingsLoadingCategories::qtKdeCategories() const
{
    return mQtKdeCategories;
}

LoggingCategory::List KDebugSettingsLoadingCategories::customCategories() const
{
    return mCustomCategories;
}

KdeLoggingCategory::List KDebugSettingsLoadingCategories::categoriesList() const
{
    return mCategoriesList;
}

RenameCategory::List KDebugSettingsLoadingCategories::renameCategoriesList() const
{
    return mRenameCategoriesList;
}

QString KDebugSettingsLoadingCategories::environmentrules() const
{
    return mEnvironmentrules;
}
