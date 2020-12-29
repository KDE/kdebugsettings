/*
    SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdebugsettingsutil.h"
#include "kdebugsettings_debug.h"
#include <QFile>
#include <QRegularExpression>
#include <KLocalizedString>
#include <QStandardPaths>
#include <QDir>

RenameCategory KDebugSettingsUtil::parseRenameCategory(QString line, const QString &filename)
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
        qCWarning(KDEBUGSETTINGS_LOG) << "Invalid categories file. Missing space. Syntax is logname<space>description + optional element. Line: "
                                      << line << " from file:" << filename
                                 #if (QT_VERSION < QT_VERSION_CHECK(5, 15, 0))
            << endl
                                 #else
            << Qt::endl
                                 #endif
        ;
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
            const RenameCategory category = parseRenameCategory(data, filename);
            if (category.isValid()) {
                insertCategories.append(category);
            }
        }
    }
    return insertCategories;
}

KdeLoggingCategory KDebugSettingsUtil::parseLineKdeLoggingCategory(QString line, const QString &filename)
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
        qCWarning(KDEBUGSETTINGS_LOG) << "Invalid categories file. Missing space. Syntax is logname<space>description + optional element. Line: "
                                      << line << " from file:" << filename
                                 #if (QT_VERSION < QT_VERSION_CHECK(5, 15, 0))
            << endl
                                 #else
            << Qt::endl
                                 #endif
        ;
        return category;
    }
    QString logName;
    QString description;
    QString defaultSeverity;
    QString identifier;

#if 1

    //TODO create an unique regularexpression

    static const QRegularExpression regularExpressionUser(QStringLiteral("^([\\w._-]+)\\s*(.*)$"));
    QRegularExpressionMatch match = regularExpressionUser.match(line);
    if (match.hasMatch()) {
        logName = match.captured(1);
        description = match.captured(2);
    }

    bool newFormatFound = false;
    static const QRegularExpression regularExpressionDefaultSeverityNewFormat(QStringLiteral("^(.*)\\s+DEFAULT_SEVERITY\\s+\\[(DEBUG|INFO|WARNING|CRITICAL)\\](?:\\s+(.*))?"));
    QRegularExpressionMatch match3 = regularExpressionDefaultSeverityNewFormat.match(description);
    QString defaultSeverityCaptured;
    QString potentialIdentifier;
    if (match3.hasMatch()) {
        newFormatFound = true;
        const QString descriptionCaptured = match3.captured(1);
        defaultSeverityCaptured = match3.captured(2);
        potentialIdentifier = match3.captured(3);
        if (!descriptionCaptured.isEmpty() && !defaultSeverityCaptured.isEmpty()) {
            description = descriptionCaptured;
            defaultSeverity = defaultSeverityCaptured;
            //qDebug() << " match.captured(1);" << descriptionCaptured;
            //qDebug() << " match.captured(2);" << defaultCategoryCaptured;
        }
    }

    if (potentialIdentifier.isEmpty()) {
        static const QRegularExpression regularExpressionDefaultIdentifierNewFormat(QStringLiteral("^(.*)\\s+IDENTIFIER\\s+\\[(.*)\\]"));
        QRegularExpressionMatch match4 = regularExpressionDefaultIdentifierNewFormat.match(description);
        if (match4.hasMatch()) {
            newFormatFound = true;
            const QString descriptionCaptured = match4.captured(1);
            const QString identifierCaptured = match4.captured(2);
            if (!descriptionCaptured.isEmpty() && !identifierCaptured.isEmpty()) {
                description = descriptionCaptured;
                identifier = identifierCaptured;
                //qDebug() << " match.captured(1);" << descriptionCaptured;
                //qDebug() << " match.captured(2);" << identifierCaptured;
            }
        }
    } else {
        static const QRegularExpression regularExpressionDefaultIdentifierNewFormat2(QStringLiteral("IDENTIFIER\\s+\\[(.*)\\]"));
        QRegularExpressionMatch match4 = regularExpressionDefaultIdentifierNewFormat2.match(potentialIdentifier);
        if (match4.hasMatch()) {
            newFormatFound = true;
            const QString identifierCaptured = match4.captured(1);
            if (!identifierCaptured.isEmpty()) {
                identifier = identifierCaptured;
            }
        }
    }

    if (!newFormatFound) {
        //Old format.
        static const QRegularExpression regularExpressionDefaultSeverityOldFormat(QStringLiteral("^(.*)\\s+\\[(DEBUG|INFO|WARNING|CRITICAL)\\]"));
        QRegularExpressionMatch match2 = regularExpressionDefaultSeverityOldFormat.match(description);
        if (match2.hasMatch()) {
            const QString descriptionCaptured = match2.captured(1);
            defaultSeverityCaptured = match2.captured(2);
            if (!descriptionCaptured.isEmpty() && !defaultSeverityCaptured.isEmpty()) {
                description = descriptionCaptured;
                defaultSeverity = defaultSeverityCaptured;
                //qDebug() << " match.captured(1);" << descriptionCaptured;
                //qDebug() << " match.captured(2);" << defaultCategoryCaptured;
                qCWarning(KDEBUGSETTINGS_LOG) << "In this file: " << filename << " this line " << line << " still use old format. We need to port it";
            }
        } else {
            qCWarning(KDEBUGSETTINGS_LOG) << "In this file: " << filename << " this line " << line << " still use old format. We need to port it";
        }
    }
#else
    static const QRegularExpression regularExpressionUser(QStringLiteral("^([\\w._-]+)\\s*([\\w._-\\(\\)\\s*]+)\\s*(?:\\[(DEBUG|INFO|WARNING|CRITICAL)\\])?$"));
    QRegularExpressionMatch match = regularExpressionUser.match(line);
    if (match.hasMatch()) {
        logName = match.captured(1);
        description = match.captured(2);
        defaultSeverity = match.captured(3);
        identifier = match.captured(4);
    }

#endif
    category.categoryName = logName;
    category.description = description;
    category.defaultSeverity = defaultSeverity;
    category.identifierName = identifier;
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
            const KdeLoggingCategory category = parseLineKdeLoggingCategory(data, filename);
            if (category.isValid()) {
                bool needToAppend = true;
                for (const KdeLoggingCategory &cat : qAsConst(categoriesList)) {
                    if (cat == category) {
                        needToAppend = false;
                        break;
                    } else if (cat.categoryName == category.categoryName) {
                        qCWarning(KDEBUGSETTINGS_LOG) << "Duplicate categories, it's a bug. Please verify: category:" << cat.categoryName << " filename : "<< filename;
                        needToAppend = false;
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
            const KdeLoggingCategory category = parseLineKdeLoggingCategory(data, filename);
            if (category.isValid()) {
                if (checkCategoryList) {
                    bool needToAppend = true;
                    for (const KdeLoggingCategory &cat : qAsConst(categoriesList)) {
                        if (cat == category) {
                            needToAppend = false;
                            break;
                        } else if (cat.categoryName == category.categoryName) {
                            qCWarning(KDEBUGSETTINGS_LOG) << "Duplicate categories, it's a bug. Please verify: category:" << cat.categoryName << " filename : "<< filename;
                            needToAppend = false;
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

LoggingCategory::LoggingType KDebugSettingsUtil::convertCategoryTypeFromString(const QString &str)
{
    if (str.isEmpty()) {
        return LoggingCategory::Info; //Default
    } else if (str == QLatin1String("DEBUG")) {
        return LoggingCategory::Debug;
    } else if (str == QLatin1String("INFO")) {
        return LoggingCategory::Info;
    } else if (str == QLatin1String("WARNING")) {
        return LoggingCategory::Warning;
    } else if (str == QLatin1String("CRITICAL")) {
        return LoggingCategory::Critical;
    }
    qCWarning(KDEBUGSETTINGS_LOG) << "Default category is unknown: " << str;
    return LoggingCategory::Info;
}

QString KDebugSettingsUtil::convertCategoryTypeToString(LoggingCategory::LoggingType type)
{
    QString str;
    switch (type) {
    case LoggingCategory::All:
        str = i18n("All Debug Messages");
        break;
    case LoggingCategory::Info:
        str = i18n("Info Messages");
        break;
    case LoggingCategory::Warning:
        str = i18n("Warning Messages");
        break;
    case LoggingCategory::Debug:
        str = i18n("Debug Messages");
        break;
    case LoggingCategory::Critical:
        str = i18n("Critical Messages");
        break;
    case LoggingCategory::Off:
        str = i18n("No Debug Messages");
        break;
    case LoggingCategory::Undefined:
        str = i18n("Undefined");
        break;
    }
    return str;
}

QString KDebugSettingsUtil::qtFileName()
{
    const QString envPath = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + QLatin1String("/QtProject");
    QDir().mkpath(envPath);
    const QString qtloggingFileName = envPath + QStringLiteral("/qtlogging.ini");
    return qtloggingFileName;
}
