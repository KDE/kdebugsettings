/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef ENVIRONMENTSETTINGSRULESPAGE_H
#define ENVIRONMENTSETTINGSRULESPAGE_H

#include "libkdebugsettings_private_export.h"
#include <QWidget>
class EnvironmentPlainTextEdit;
class LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT EnvironmentSettingsRulesPage : public QWidget
{
    Q_OBJECT
public:
    explicit EnvironmentSettingsRulesPage(QWidget *parent = nullptr);
    ~EnvironmentSettingsRulesPage() override;
    void setRules(const QString &rules);

private:
    EnvironmentPlainTextEdit *const mRichTextEdit;
};

#endif // ENVIRONMENTSETTINGSRULESPAGE_H
