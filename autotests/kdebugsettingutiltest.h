/*
    SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef KDEBUGSETTINGUTILTEST_H
#define KDEBUGSETTINGUTILTEST_H

#include <QObject>

class KDebugSettingUtilTest : public QObject
{
    Q_OBJECT
public:
    explicit KDebugSettingUtilTest(QObject *parent = nullptr);
    ~KDebugSettingUtilTest();
private Q_SLOTS:
    void shouldParseKdeLoggingLine_data();
    void shouldParseKdeLoggingLine();

    void shouldParseQtLoggingLine_data();
    void shouldParseQtLoggingLine();

    void shouldReadLoadKdeCategories_data();
    void shouldReadLoadKdeCategories();

    void shouldReadRenameCategories_data();
    void shouldReadRenameCategories();

    void shouldConvertCategoryTypeFromString_data();
    void shouldConvertCategoryTypeFromString();
};

#endif // KDEBUGSETTINGUTILTEST_H
