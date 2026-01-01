/*
    SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdebugsettingsutil.h"
using namespace Qt::Literals::StringLiterals;

#include "kdebugsettingscore_debug.h"
#include <KLocalizedString>
#include <QDir>
#include <QFile>
#include <QRegularExpression>
#include <QStandardPaths>

RenameCategory KDebugSettingsUtil::parseRenameCategory(QString line, const QString &filename)
{
    RenameCategory category;
    int pos = line.indexOf(u'#');
    if (pos != -1) {
        line.truncate(pos);
        line = line.simplified();
    }

    if (line.isEmpty()) {
        return category;
    }
    line = line.simplified();
    const int space = line.indexOf(u' ');
    if (space == -1) {
        qCWarning(KDEBUGSETTINGSCORE_LOG) << "Invalid categories file. Missing space. Syntax is logname<space>description + optional element. Line: " << line
                                          << " from file:" << filename << Qt::endl;
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
        qCWarning(KDEBUGSETTINGSCORE_LOG) << "Couldn't open" << filename;
    } else {
        QString data;
        QTextStream ts(&file);
        ts.setEncoding(QStringConverter::Encoding::Latin1);
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
    const int pos = line.indexOf(u'#');
    if (pos != -1) {
        line.truncate(pos);
        line = line.simplified();
    }

    if (line.isEmpty()) {
        return category;
    }
    line = line.simplified();
    const int space = line.indexOf(u' ');
    if (space == -1) {
        qCWarning(KDEBUGSETTINGSCORE_LOG) << "Invalid categories file. Missing space. Syntax is logname<space>description + optional element. Line: " << line
                                          << " from file:" << filename << Qt::endl;
        return category;
    }
    QString logName;
    QString description;
    QString defaultSeverity;
    QString identifier;

    // TODO create an unique regularexpression

    static const QRegularExpression regularExpressionUser(u"^([\\w._-]+)\\s*(.*)$"_s);
    QRegularExpressionMatch match = regularExpressionUser.match(line);
    if (match.hasMatch()) {
        logName = match.captured(1);
        description = match.captured(2);
    }

    bool newFormatFound = false;
    static const QRegularExpression regularExpressionDefaultSeverityNewFormat(
        u"^(.*)\\s+DEFAULT_SEVERITY\\s+\\[(DEBUG|INFO|WARNING|CRITICAL)\\](?:\\s+(.*))?"_s);
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
            // qDebug() << " match.captured(1);" << descriptionCaptured;
            // qDebug() << " match.captured(2);" << defaultCategoryCaptured;
        }
    }

    if (potentialIdentifier.isEmpty()) {
        static const QRegularExpression regularExpressionDefaultIdentifierNewFormat(u"^(.*)\\s+IDENTIFIER\\s+\\[(.*)\\]"_s);
        QRegularExpressionMatch match4 = regularExpressionDefaultIdentifierNewFormat.match(description);
        if (match4.hasMatch()) {
            newFormatFound = true;
            const QString descriptionCaptured = match4.captured(1);
            const QString identifierCaptured = match4.captured(2);
            if (!descriptionCaptured.isEmpty() && !identifierCaptured.isEmpty()) {
                description = descriptionCaptured;
                identifier = identifierCaptured;
                // qDebug() << " match.captured(1);" << descriptionCaptured;
                // qDebug() << " match.captured(2);" << identifierCaptured;
            }
        }
    } else {
        static const QRegularExpression regularExpressionDefaultIdentifierNewFormat2(u"IDENTIFIER\\s+\\[(.*)\\]"_s);
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
        // Old format.
        static const QRegularExpression regularExpressionDefaultSeverityOldFormat(u"^(.*)\\s+\\[(DEBUG|INFO|WARNING|CRITICAL)\\]"_s);
        QRegularExpressionMatch match2 = regularExpressionDefaultSeverityOldFormat.match(description);
        if (match2.hasMatch()) {
            const QString descriptionCaptured = match2.captured(1);
            defaultSeverityCaptured = match2.captured(2);
            if (!descriptionCaptured.isEmpty() && !defaultSeverityCaptured.isEmpty()) {
                description = descriptionCaptured;
                defaultSeverity = defaultSeverityCaptured;
                // qDebug() << " match.captured(1);" << descriptionCaptured;
                // qDebug() << " match.captured(2);" << defaultCategoryCaptured;
                qCWarning(KDEBUGSETTINGSCORE_LOG) << "In this file: " << filename << " this line " << line << " still uses the old format. We need to port it.";
            }
        } else {
            qCWarning(KDEBUGSETTINGSCORE_LOG) << "In this file: " << filename << " this line " << line << " still uses the old format. We need to port it.";
        }
    }
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
        qCWarning(KDEBUGSETTINGSCORE_LOG) << "Couldn't open" << filename;
    } else {
        QString data;
        QTextStream ts(&file);
        ts.setEncoding(QStringConverter::Encoding::Latin1);
        while (!ts.atEnd()) {
            data = ts.readLine().simplified();
            const KdeLoggingCategory category = parseLineKdeLoggingCategory(data, filename);
            if (category.isValid()) {
                bool needToAppend = true;
                for (const KdeLoggingCategory &cat : std::as_const(categoriesList)) {
                    if (cat == category) {
                        needToAppend = false;
                        break;
                    } else if (cat.categoryName == category.categoryName) {
                        qCWarning(KDEBUGSETTINGSCORE_LOG)
                            << "Duplicate categories, it is a bug. Please verify: category:" << cat.categoryName << " filename : " << filename;
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
        qCWarning(KDEBUGSETTINGSCORE_LOG) << "Couldn't open" << filename;
    } else {
        QString data;
        QTextStream ts(&file);
        ts.setEncoding(QStringConverter::Encoding::Latin1);
        while (!ts.atEnd()) {
            data = ts.readLine().simplified();
            const KdeLoggingCategory category = parseLineKdeLoggingCategory(data, filename);
            if (category.isValid()) {
                if (checkCategoryList) {
                    bool needToAppend = true;
                    for (const KdeLoggingCategory &cat : std::as_const(categoriesList)) {
                        if (cat == category) {
                            needToAppend = false;
                            break;
                        } else if (cat.categoryName == category.categoryName) {
                            qCWarning(KDEBUGSETTINGSCORE_LOG)
                                << "Duplicate categories, it is a bug. Please verify: category:" << cat.categoryName << " filename : " << filename;
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
    int equalPos = line.indexOf(u'=');
    if ((equalPos != -1) && (line.lastIndexOf(u'=') == equalPos)) {
        const QString pattern = line.left(equalPos);
        const QString valueStr = line.mid(equalPos + 1);
        if (valueStr == "true"_L1) {
            lineCategory.enabled = true;
        } else {
            lineCategory.enabled = false;
        }
        QString p;
        if (pattern.endsWith(".debug"_L1)) {
            p = pattern.left(pattern.length() - 6); // strlen(".debug")
            lineCategory.logName = p;
            lineCategory.type = LineLoggingQtCategory::Debug;
        } else if (pattern.endsWith(".warning"_L1)) {
            p = pattern.left(pattern.length() - 8); // strlen(".warning")
            lineCategory.logName = p;
            lineCategory.type = LineLoggingQtCategory::Warning;
        } else if (pattern.endsWith(".critical"_L1)) {
            p = pattern.left(pattern.length() - 9); // strlen(".critical")
            lineCategory.logName = p;
            lineCategory.type = LineLoggingQtCategory::Critical;
        } else if (pattern.endsWith(".info"_L1)) {
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
        qCWarning(KDEBUGSETTINGSCORE_LOG) << "Empty file name";
        return {};
    }
    if (!QFileInfo::exists(filename)) {
        qCWarning(KDEBUGSETTINGSCORE_LOG) << u"filename %1 does not exist"_s.arg(filename);
        return {};
    }
    // Code based on src/corelib/io/qloggingregistry.cpp
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
            line.remove(u' ');

            // comment
            if (line.startsWith(u';')) {
                continue;
            }

            if (line.startsWith(u'[') && line.endsWith(u']')) {
                // new section
                _section = line.mid(1, line.size() - 2);
                rulesSections = (_section == "Rules"_L1);
                continue;
            }
            if (rulesSections) {
                KDebugSettingsUtil::LineLoggingQtCategory cat = parseLineLoggingQtCategory(line);
                // qDebug() << " line " << line;
                // qDebug() << "enable " << cat.enabled << " valid : " << cat.isValid();
                if (cat.isValid()) {
                    KDebugSettingsUtil::LoadLoggingCategory nextCat = hashLoadLoggingCategories.value(cat.logName);
                    if (nextCat.isValid()) {
                        LoadLoggingCategory::LogType type = LoadLoggingCategory::Unknown;
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
                            nextCat.loggingTypes.insert(LoadLoggingCategory::Unknown,
                                                        cat.enabled ? LoadLoggingCategory::Enabled : LoadLoggingCategory::Disabled);
                            break;
                        case LineLoggingQtCategory::Info:
                            nextCat.loggingTypes.insert(LoadLoggingCategory::Info, cat.enabled ? LoadLoggingCategory::Enabled : LoadLoggingCategory::Disabled);
                            break;
                        case LineLoggingQtCategory::Warning:
                            nextCat.loggingTypes.insert(LoadLoggingCategory::Warning,
                                                        cat.enabled ? LoadLoggingCategory::Enabled : LoadLoggingCategory::Disabled);
                            break;
                        case LineLoggingQtCategory::Debug:
                            nextCat.loggingTypes.insert(LoadLoggingCategory::Debug, cat.enabled ? LoadLoggingCategory::Enabled : LoadLoggingCategory::Disabled);
                            break;
                        case LineLoggingQtCategory::Critical:
                            nextCat.loggingTypes.insert(LoadLoggingCategory::Critical,
                                                        cat.enabled ? LoadLoggingCategory::Enabled : LoadLoggingCategory::Disabled);
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
        qCWarning(KDEBUGSETTINGSCORE_LOG) << "Impossible to open file: " << filename;
    }

    return hashLoadLoggingCategories.values();
}

LoggingCategory::LoggingType KDebugSettingsUtil::convertCategoryTypeFromString(const QString &str)
{
    if (str.isEmpty()) {
        return LoggingCategory::Info; // Default
    } else if (str == "DEBUG"_L1) {
        return LoggingCategory::Debug;
    } else if (str == "INFO"_L1) {
        return LoggingCategory::Info;
    } else if (str == "WARNING"_L1) {
        return LoggingCategory::Warning;
    } else if (str == "CRITICAL"_L1) {
        return LoggingCategory::Critical;
    }
    qCWarning(KDEBUGSETTINGSCORE_LOG) << "Default category is unknown: " << str;
    return LoggingCategory::Info;
}

QString KDebugSettingsUtil::convertCategoryTypeToString(LoggingCategory::LoggingType type)
{
    QString str;
    switch (type) {
    case LoggingCategory::Debug:
    case LoggingCategory::All:
        str = i18n("Full Debug");
        break;
    case LoggingCategory::Info:
        str = i18n("Info");
        break;
    case LoggingCategory::Warning:
        str = i18n("Warning");
        break;
    case LoggingCategory::Critical:
        str = i18n("Critical");
        break;
    case LoggingCategory::Off:
        str = i18n("Off");
        break;
    case LoggingCategory::Undefined:
        str = i18n("Undefined");
        break;
    }
    return str;
}

QString KDebugSettingsUtil::qtFileName()
{
    const QString envPath = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/QtProject"_L1;
    QDir().mkpath(envPath);
    const QString qtloggingFileName = envPath + u"/qtlogging.ini"_s;
    return qtloggingFileName;
}

QString KDebugSettingsUtil::defaultWritableGroupPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/groups"_L1;
}

QStringList KDebugSettingsUtil::groupFileList()
{
    const QString groupPath = KDebugSettingsUtil::defaultWritableGroupPath();
    if (groupPath.isEmpty()) {
        return {};
    }
    QDir dir(groupPath);
    const QStringList groups = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    return groups;
}

bool KDebugSettingsUtil::hasWritableGroups()
{
    return !groupFileList().isEmpty();
}

LoggingCategory KDebugSettingsUtil::convertRuleStrToLoggingCategory(const QString &ruleStr)
{
    LoggingCategory tmp;
    const KDebugSettingsUtil::LineLoggingQtCategory cat = KDebugSettingsUtil::parseLineLoggingQtCategory(ruleStr);
    if (cat.isValid()) {
        tmp.categoryName = cat.logName;
        tmp.enabled = cat.enabled;
        switch (cat.type) {
        case KDebugSettingsUtil::LineLoggingQtCategory::Unknown:
            break;
        case KDebugSettingsUtil::LineLoggingQtCategory::Info:
            tmp.loggingType = LoggingCategory::Info;
            break;
        case KDebugSettingsUtil::LineLoggingQtCategory::Warning:
            tmp.loggingType = LoggingCategory::Warning;
            break;
        case KDebugSettingsUtil::LineLoggingQtCategory::Debug:
            tmp.loggingType = LoggingCategory::Debug;
            break;
        case KDebugSettingsUtil::LineLoggingQtCategory::Critical:
            tmp.loggingType = LoggingCategory::Critical;
            break;
        case KDebugSettingsUtil::LineLoggingQtCategory::All:
            tmp.loggingType = LoggingCategory::All;
            break;
        }
    }
    return tmp;
}

QString KDebugSettingsUtil::generateDisplayRule(const QString &categoryName, bool state, LoggingCategory::LoggingType type)
{
    QString ruleStr = categoryName;
    if (!categoryName.isEmpty()) {
        switch (type) {
        case LoggingCategory::Undefined:
        case LoggingCategory::All:
            break;
        case LoggingCategory::Info:
            ruleStr += u".info"_s;
            break;
        case LoggingCategory::Warning:
            ruleStr += u".warning"_s;
            break;
        case LoggingCategory::Debug:
            ruleStr += u".debug"_s;
            break;
        case LoggingCategory::Critical:
            ruleStr += u".critical"_s;
            break;
        case LoggingCategory::Off:
            break;
        }
        if (state) {
            ruleStr += u"=true"_s;
        } else {
            ruleStr += u"=false"_s;
        }
    }
    return ruleStr;
}
