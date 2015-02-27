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

#ifndef KDEBUGSETTINGSDIALOG_H
#define KDEBUGSETTINGSDIALOG_H

#include <QDialog>
#include <QMap>
#include <QVector>
class QTabWidget;
class KDeApplicationDebugSettingPage;
class CustomDebugSettingsPage;
struct Category {
    Category()
        : enabled(false)
    {

    }
    typedef QVector<Category> List;
    bool operator ==(const Category &other) const
    {
        return (description == other.description) &&
               (logName == other.logName) &&
               (type == other.type) &&
               (enabled == other.enabled);
    }
    bool isValid() const
    {
        return !logName.isEmpty();
    }

    QString description;
    QString logName;
    QString type;
    bool enabled;
};

class KDebugSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit KDebugSettingsDialog(QWidget *parent = Q_NULLPTR);
    ~KDebugSettingsDialog();

private slots:
    void slotAccepted();
private:
    void readCategoriesFiles();
    void saveConfig();
    void readConfig();
    QTabWidget *mTabWidget;
    KDeApplicationDebugSettingPage *mKdeApplicationSettingsPage;
    CustomDebugSettingsPage *mCustomSettingsPage;
};

#endif // KDEBUGSETTINGSDIALOG_H
