/*
  Copyright (c) 2015 Montel Laurent <montel@kde.org>

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

KdeLoggingCategory KDebugSettingsUtil::parseLineKdeLoggingCategory(QString line)
{
    KdeLoggingCategory category;
    int pos = line.indexOf(QStringLiteral("#"));
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

    const QString logName = line.left(space);

    const QString description = line.mid(space).simplified();
    category.logName = logName;
    category.description = description;
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
                Q_FOREACH (const KdeLoggingCategory &cat, categoriesList) {
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
                    Q_FOREACH (const KdeLoggingCategory &cat, categoriesList) {
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

LoggingCategory KDebugSettingsUtil::parseLineLoggingQtCategory(const QString &line)
{
    LoggingCategory cat;
    int equalPos = line.indexOf(QLatin1Char('='));
    if ((equalPos != -1)
            && (line.lastIndexOf(QLatin1Char('=')) == equalPos)) {

        const QString pattern = line.left(equalPos);
        const QString valueStr = line.mid(equalPos + 1);
        if (valueStr == QLatin1String("true")) {
            cat.enabled = true;
        } else if (valueStr == QLatin1String("false")) {
            cat.enabled = false;
        } else {
            return cat;
        }

        QString p;
        if (pattern.endsWith(QLatin1String(".debug"))) {
            p = pattern.left(pattern.length() - 6); // strlen(".debug")
            cat.type = QStringLiteral("debug");
            cat.logName = p;
        } else if (pattern.endsWith(QLatin1String(".warning"))) {
            p = pattern.left(pattern.length() - 8); // strlen(".warning")
            cat.type = QStringLiteral("warning");
            cat.logName = p;
        } else if (pattern.endsWith(QLatin1String(".critical"))) {
            p = pattern.left(pattern.length() - 9); // strlen(".critical")
            cat.type = QStringLiteral("critical");
            cat.logName = p;
        } else {
            p = pattern;
            cat.logName = p;
        }
    }
    return cat;
}

LoggingCategory::List KDebugSettingsUtil::readLoggingQtCategories(const QString &filename)
{
    //Code based on src/corelib/io/qloggingregistry.cpp
    LoggingCategory::List categories;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qCWarning(KDEBUGSETTINGS_LOG) << "Couldn't open" << filename;
    } else {
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
                LoggingCategory cat = parseLineLoggingQtCategory(line);
                if (cat.isValid()) {
                    categories.append(cat);
                }
            }
        }
    }
    return categories;
}
