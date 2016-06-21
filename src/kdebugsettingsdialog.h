/*
  Copyright (c) 2015-2016 Montel Laurent <montel@kde.org>

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

#ifndef KDEBUGSETTINGSDIALOG_H
#define KDEBUGSETTINGSDIALOG_H

#include <QDialog>
#include <QVector>
class QTabWidget;
class KDEApplicationDebugSettingPage;
class CustomDebugSettingsPage;
class EnvironmentSettingsRulesPage;
class CategoryWarning;

struct KdeLoggingCategory {
    KdeLoggingCategory()
    {

    }
    typedef QVector<KdeLoggingCategory> List;
    bool operator ==(const KdeLoggingCategory &other) const
    {
        return (description == other.description) &&
               (logName == other.logName);
    }
    bool isValid() const
    {
        return !logName.isEmpty();
    }

    QString description;
    QString logName;
};
Q_DECLARE_TYPEINFO(KdeLoggingCategory, Q_MOVABLE_TYPE);

struct LoggingCategory {
    LoggingCategory()
        : loggingType(Info),
          enabled(true)
    {

    }

    enum LoggingType {
        All = 0,
        Info,
        Warning,
        Debug,
        Critical,
        Off
    };

    typedef QVector<LoggingCategory> List;
    bool operator ==(const LoggingCategory &other) const
    {
        return (description == other.description) &&
               (logName == other.logName) &&
               (type == other.type) &&
               (enabled == other.enabled) &&
               (loggingType == other.loggingType);
    }
    bool isValid() const
    {
        return !logName.isEmpty();
    }

    QString createRule();
    QString description;
    QString logName;
    QString type;
    LoggingType loggingType;
    bool enabled;
};
Q_DECLARE_TYPEINFO(LoggingCategory, Q_MOVABLE_TYPE);
Q_DECLARE_METATYPE(LoggingCategory::LoggingType)

class KDebugSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit KDebugSettingsDialog(QWidget *parent = Q_NULLPTR);
    ~KDebugSettingsDialog();

private Q_SLOTS:
    void slotAccepted();
    void slotHelpRequested();
    void slotApply();
    void slotSaveAs();
    void slotLoad();
    void slotInsertCategories();
private:
    void readQtLoggingFile();
    bool saveRules(const QString &path);
    bool saveInQtLogging();
    void readCategoriesFiles(const QString &path);
    void saveConfig();
    void readConfig();
    KdeLoggingCategory::List mCategories;
    QTabWidget *mTabWidget;
    KDEApplicationDebugSettingPage *mKdeApplicationSettingsPage;
    CustomDebugSettingsPage *mCustomSettingsPage;
    EnvironmentSettingsRulesPage *mEnvironmentSettingsRulesPage;
    CategoryWarning *mCategoryWarning;
};

#endif // KDEBUGSETTINGSDIALOG_H
