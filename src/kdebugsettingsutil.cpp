/*
  Copyright (c) 2015-2018 Montel Laurent <montel@kde.org>

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

#include "kdebugsettingsutil.h"
#include "kdebugsettings_debug.h"
#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>

RenameCategory KDebugSettingsUtil::parseRenameCategory(QString line)
{
    RenameCategory category;
    int pos = line.indexOf(QLatin1Char('#'));
    if (pos != -1) {
        line.truncate(pos);
        line = line.simplified();
    }

    if (line.isEmpty()) {
        return category;
    }
    line = line.simplified();
    const int space = line.indexOf(QLatin1Char(' '));
    if (space == -1) {
        qCWarning(KDEBUGSETTINGS_LOG) << "No space:" << line << endl;
        return category;
    }

    const QString originalName = line.left(space);

    const QString newName = line.mid(space).simplified();
    category.originalName = originalName;
    category.newName = newName;
    return category;
}

RenameCategory::List KDebugSettingsUtil::readRenameCategories(const QString &filename)
{
    RenameCategory::List insertCategories;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qCWarning(KDEBUGSETTINGS_LOG) << "Couldn't open" << filename;
    } else {
        QString data;
        QTextStream ts(&file);
        ts.setCodec("ISO-8859-1");
        while (!ts.atEnd()) {
            data = ts.readLine().simplified();
            const RenameCategory category = parseRenameCategory(data);
            if (category.isValid()) {
                insertCategories.append(category);
            }
        }
    }
    return insertCategories;
}

KdeLoggingCategory KDebugSettingsUtil::parseLineKdeLoggingCategory(QString line)
{
    KdeLoggingCategory category;
    const int pos = line.indexOf(QLatin1Char('#'));
    if (pos != -1) {
        line.truncate(pos);
        line = line.simplified();
    }

    if (line.isEmpty()) {
        return category;
    }
    line = line.simplified();
    const int space = line.indexOf(QLatin1Char(' '));
    if (space == -1) {
        qCWarning(KDEBUGSETTINGS_LOG) << "No space:" << line << endl;
        return category;
    }
#if 0
    //log linux (foo)

    const QString logName = line.left(space);

    const QString description = line.mid(space).simplified();
#else
    QString logName;
    QString description;
    static const QRegularExpression regularExpressionUser(QStringLiteral("^([\\w._-]+)\\s*(.*)$"));
    QRegularExpressionMatch match = regularExpressionUser.match(line);
    if (match.hasMatch()) {
        logName = match.captured(1);
        description = match.captured(2);
        //qDebug() << " logName"<<logName<<" description " << description << " line " << line;
    }
#endif

    category.logName = logName;
    category.description = description;
    //TODO add default categories ?
    return category;
}

KdeLoggingCategory::List KDebugSettingsUtil::readLoggingCategoriesForInserting(const QString &filename, KdeLoggingCategory::List &categoriesList)
{
    KdeLoggingCategory::List insertCategories;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qCWarning(KDEBUGSETTINGS_LOG) << "Couldn't open" << filename;
    } else {
        QString data;
        QTextStream ts(&file);
        ts.setCodec("ISO-8859-1");
        while (!ts.atEnd()) {
            data = ts.readLine().simplified();
            const KdeLoggingCategory category = parseLineKdeLoggingCategory(data);
            if (category.isValid()) {
                bool needToAppend = true;
                for (const KdeLoggingCategory &cat : qAsConst(categoriesList)) {
                    if (cat == category) {
                        needToAppend = false;
                        break;
                    }
                }
                if (needToAppend) {
                    categoriesList.append(category);
                    insertCategories.append(category);
                }
            }
        }
    }
    return insertCategories;
}

void KDebugSettingsUtil::readLoggingCategories(const QString &filename, KdeLoggingCategory::List &categoriesList, bool checkCategoryList)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qCWarning(KDEBUGSETTINGS_LOG) << "Couldn't open" << filename;
    } else {
        QString data;
        QTextStream ts(&file);
        ts.setCodec("ISO-8859-1");
        while (!ts.atEnd()) {
            data = ts.readLine().simplified();
            const KdeLoggingCategory category = parseLineKdeLoggingCategory(data);
            if (category.isValid()) {
                if (checkCategoryList) {
                    bool needToAppend = true;
                    for (const KdeLoggingCategory &cat : qAsConst(categoriesList)) {
                        if (cat == category) {
                            needToAppend = false;
                            break;
                        }
                    }
                    if (needToAppend) {
                        categoriesList.append(category);
                    }
                } else {
                    categoriesList.append(category);
                }
            }
        }
    }
}

KDebugSettingsUtil::LineLoggingQtCategory KDebugSettingsUtil::parseLineLoggingQtCategory(const QString &line)
{
    LineLoggingQtCategory lineCategory;
    int equalPos = line.indexOf(QLatin1Char('='));
    if ((equalPos != -1)
            && (line.lastIndexOf(QLatin1Char('=')) == equalPos)) {

        const QString pattern = line.left(equalPos);
        const QString valueStr = line.mid(equalPos + 1);
        if (valueStr == QLatin1String("true")) {
            lineCategory.enabled = true;
        } else {
            lineCategory.enabled = false;
        }
        QString p;
        if (pattern.endsWith(QLatin1String(".debug"))) {
            p = pattern.left(pattern.length() - 6); // strlen(".debug")
            lineCategory.logName = p;
            lineCategory.type = LineLoggingQtCategory::Debug;
        } else if (pattern.endsWith(QLatin1String(".warning"))) {
            p = pattern.left(pattern.length() - 8); // strlen(".warning")
            lineCategory.logName = p;
            lineCategory.type = LineLoggingQtCategory::Warning;
        } else if (pattern.endsWith(QLatin1String(".critical"))) {
            p = pattern.left(pattern.length() - 9); // strlen(".critical")
            lineCategory.logName = p;
            lineCategory.type = LineLoggingQtCategory::Critical;
        } else if (pattern.endsWith(QLatin1String(".info"))) {
            p = pattern.left(pattern.length() - 5); // strlen(".info")
            lineCategory.logName = p;
            lineCategory.type = LineLoggingQtCategory::Info;
        } else {
            p = pattern;
            lineCategory.logName = p;
            lineCategory.type = LineLoggingQtCategory::All;
        }
    } else {
        lineCategory.enabled = false;
    }
    return lineCategory;
}

QList<KDebugSettingsUtil::LoadLoggingCategory> KDebugSettingsUtil::readLoggingQtCategories(const QString &filename)
{
    if (filename.isEmpty()) {
        qCWarning(KDEBUGSETTINGS_LOG) << "Empty file name";
        return {};
    }
    //Code based on src/corelib/io/qloggingregistry.cpp
    QFile file(filename);
    QMap<QString, KDebugSettingsUtil::LoadLoggingCategory> hashLoadLoggingCategories;
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream ts(&file);
        QString _section;
        bool rulesSections = false;
        while (!ts.atEnd()) {
            QString line = ts.readLine();

            // Remove all whitespace from line
            line = line.simplified();
            line.remove(QLatin1Char(' '));

            // comment
            if (line.startsWith(QLatin1Char(';'))) {
                continue;
            }

            if (line.startsWith(QLatin1Char('[')) && line.endsWith(QLatin1Char(']'))) {
                // new section
                _section = line.mid(1, line.size() - 2);
                rulesSections = (_section == QLatin1String("Rules"));
                continue;
            }
            if (rulesSections) {
                KDebugSettingsUtil::LineLoggingQtCategory cat = parseLineLoggingQtCategory(line);
                //qDebug() << " line " << line;
                //qDebug() << "enable " << cat.enabled << " valid : " << cat.isValid();
                if (cat.isValid()) {
                    KDebugSettingsUtil::LoadLoggingCategory nextCat = hashLoadLoggingCategories.value(cat.logName);
                    if (nextCat.isValid()) {
                        LoadLoggingCategory::LogType type;
                        switch (cat.type) {
                        case LineLoggingQtCategory::Unknown:
                            type = LoadLoggingCategory::Unknown;
                            break;
                        case LineLoggingQtCategory::Info:
                            type = LoadLoggingCategory::Info;
                            break;
                        case LineLoggingQtCategory::Warning:
                            type = LoadLoggingCategory::Warning;
                            break;
                        case LineLoggingQtCategory::Debug:
                            type = LoadLoggingCategory::Debug;
                            break;
                        case LineLoggingQtCategory::Critical:
                            type = LoadLoggingCategory::Critical;
                            break;
                        case LineLoggingQtCategory::All:
                            type = LoadLoggingCategory::All;
                            break;
                        }

                        if (nextCat.loggingTypes.contains(type)) {
                            nextCat.loggingTypes[type] = cat.enabled ? LoadLoggingCategory::Enabled : LoadLoggingCategory::Disabled;
                        } else {
                            nextCat.loggingTypes.insert(type, cat.enabled ? LoadLoggingCategory::Enabled : LoadLoggingCategory::Disabled);
                        }
                        hashLoadLoggingCategories[cat.logName] = nextCat;
                    } else {
                        nextCat.logName = cat.logName;
                        switch (cat.type) {
                        case LineLoggingQtCategory::Unknown:
                            nextCat.loggingTypes.insert(LoadLoggingCategory::Unknown, cat.enabled ? LoadLoggingCategory::Enabled : LoadLoggingCategory::Disabled);
                            break;
                        case LineLoggingQtCategory::Info:
                            nextCat.loggingTypes.insert(LoadLoggingCategory::Info, cat.enabled ? LoadLoggingCategory::Enabled : LoadLoggingCategory::Disabled);
                            break;
                        case LineLoggingQtCategory::Warning:
                            nextCat.loggingTypes.insert(LoadLoggingCategory::Warning, cat.enabled ? LoadLoggingCategory::Enabled : LoadLoggingCategory::Disabled);
                            break;
                        case LineLoggingQtCategory::Debug:
                            nextCat.loggingTypes.insert(LoadLoggingCategory::Debug, cat.enabled ? LoadLoggingCategory::Enabled : LoadLoggingCategory::Disabled);
                            break;
                        case LineLoggingQtCategory::Critical:
                            nextCat.loggingTypes.insert(LoadLoggingCategory::Critical, cat.enabled ? LoadLoggingCategory::Enabled : LoadLoggingCategory::Disabled);
                            break;
                        case LineLoggingQtCategory::All:
                            nextCat.loggingTypes.insert(LoadLoggingCategory::All, cat.enabled ? LoadLoggingCategory::Enabled : LoadLoggingCategory::Disabled);
                            break;
                        }
                        hashLoadLoggingCategories.insert(cat.logName, nextCat);
                    }
                }
            }
        }
    } else {
        qCWarning(KDEBUGSETTINGS_LOG) << "Impossible to open file: " << filename;
    }

    return hashLoadLoggingCategories.values();
}
