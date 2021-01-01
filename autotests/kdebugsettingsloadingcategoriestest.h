/*
    SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef KDEBUGSETTINGSLOADINGCATEGORIESTEST_H
#define KDEBUGSETTINGSLOADINGCATEGORIESTEST_H

#include <QObject>

class KDebugSettingsLoadingCategoriesTest : public QObject
{
    Q_OBJECT
public:
    explicit KDebugSettingsLoadingCategoriesTest(QObject *parent = nullptr);
    ~KDebugSettingsLoadingCategoriesTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // KDEBUGSETTINGSLOADINGCATEGORIES_H
