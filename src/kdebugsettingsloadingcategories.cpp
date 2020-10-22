/*
  Copyright (c) 2019-2020 Laurent Montel <montel@kde.org>

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

#include "kdebugsettingsloadingcategories.h"
#include "kdebugsettings_debug.h"
#include "kdebugsettingsutil.h"
#include "loadcategoriesjob.h"
#include <QStandardPaths>
#include <QLibraryInfo>
#include <QDir>

KDebugSettingsLoadingCategories::KDebugSettingsLoadingCategories()
{
}

KDebugSettingsLoadingCategories::~KDebugSettingsLoadingCategories()
{
}

void KDebugSettingsLoadingCategories::readQtLoggingFile()
{
    mCategoriesList.clear();
    const QString envPath = QStandardPaths::locate(QStandardPaths::GenericConfigLocation, QStringLiteral("QtProject/qtlogging.ini"));
    if (!envPath.isEmpty()) {
        readCategoriesFiles(envPath);
    } else {
        const QString dataPath = QDir(QLibraryInfo::location(QLibraryInfo::DataPath)).absoluteFilePath(QStringLiteral("qtlogging.ini"));
        readCategoriesFiles(dataPath);
    }
}

void KDebugSettingsLoadingCategories::readCategoriesFiles(const QString &path)
{
    // KDE debug categories area
    const QString confAreasFile = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral("qlogging-categories5/kde.categories"));
    if (confAreasFile.isEmpty()) {
        qCWarning(KDEBUGSETTINGS_LOG) << "Impossible to find kde.categories file";
    } else {
        KDebugSettingsUtil::readLoggingCategories(confAreasFile, mCategoriesList, false);
    }

    mRenameCategoriesList.clear();
    // Load *.renamecategories file in QStandardPaths::ConfigLocation for kde apps.
    const QStringList dirs = QStandardPaths::locateAll(QStandardPaths::ConfigLocation, QString(), QStandardPaths::LocateDirectory)
                             +QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, QStringLiteral("qlogging-categories5/"), QStandardPaths::LocateDirectory);
    for (const QString &dir : dirs) {
        const QStringList fileNames = QDir(dir).entryList(QStringList() << QStringLiteral("*.renamecategories"));
        for (const QString &file : fileNames) {
            mRenameCategoriesList.append(KDebugSettingsUtil::readRenameCategories(dir + file));
        }
    }
    //TODO add load rename file from external kde apps.
    const QStringList dirs2 = QStandardPaths::locateAll(QStandardPaths::GenericConfigLocation, QStringLiteral("qdebug.categories/"), QStandardPaths::LocateDirectory);
    //qDebug() << " dirs 2 " << dirs2;
    for (const QString &dir : dirs2) {
        const QStringList fileNames = QDir(dir).entryList(QStringList() << QStringLiteral("*.renamecategories"));
        for (const QString &file : fileNames) {
            mRenameCategoriesList.append(KDebugSettingsUtil::readRenameCategories(dir + file));
        }
    }

    // Load *.categories file in QStandardPaths::ConfigLocation for kde apps.
    for (const QString &dir : dirs) {
        const QStringList fileNames = QDir(dir).entryList(QStringList() << QStringLiteral("*.categories"));
        for (const QString &file : fileNames) {
            if (file != QLatin1String("kde.categories")) {
                KDebugSettingsUtil::readLoggingCategories(dir + file, mCategoriesList, true);
            }
        }
    }

    // Load *.categories files. in qdebug.categories for external kde apps.
    for (const QString &dir : dirs2) {
        const QStringList fileNames = QDir(dir).entryList(QStringList() << QStringLiteral("*.categories"));
        for (const QString &file : fileNames) {
            KDebugSettingsUtil::readLoggingCategories(dir + QLatin1Char('/') + file, mCategoriesList, true);
        }
    }

    const QByteArray rulesFilePath = qgetenv("QT_LOGGING_CONF");
    if (!rulesFilePath.isEmpty()) {
        //const QList<KDebugSettingsUtil::LoadLoggingCategory> envCategories = KDebugSettingsUtil::readLoggingQtCategories(QString::fromLatin1(rulesFilePath));
        //TODO
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
