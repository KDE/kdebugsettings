/*
    SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef KDEAPPLICATIONTREELISTWIDGETTEST_H
#define KDEAPPLICATIONTREELISTWIDGETTEST_H

#include <QObject>

class KDEApplicationTreeListWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit KDEApplicationTreeListWidgetTest(QObject *parent = nullptr);
    ~KDEApplicationTreeListWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // KDEAPPLICATIONTREELISTWIDGETTEST_H
