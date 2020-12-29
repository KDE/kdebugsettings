/*
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef RENAMECATEGORYTEST_H
#define RENAMECATEGORYTEST_H

#include <QObject>

class RenameCategoryTest : public QObject
{
    Q_OBJECT
public:
    explicit RenameCategoryTest(QObject *parent = nullptr);
    ~RenameCategoryTest();
private Q_SLOTS:
    void shouldParseRenameLine_data();
    void shouldParseRenameLine();
};

#endif // RENAMECATEGORYTEST_H
