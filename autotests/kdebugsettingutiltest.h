/*
    SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class KDebugSettingUtilTest : public QObject
{
    Q_OBJECT
public:
    explicit KDebugSettingUtilTest(QObject *parent = nullptr);
    ~KDebugSettingUtilTest() override;
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
