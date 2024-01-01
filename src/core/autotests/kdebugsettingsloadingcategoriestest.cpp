/*
    SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdebugsettingsloadingcategoriestest.h"
#include "kdebugsettingsloadingcategories.h"
#include <QTest>
QTEST_GUILESS_MAIN(KDebugSettingsLoadingCategoriesTest)

KDebugSettingsLoadingCategoriesTest::KDebugSettingsLoadingCategoriesTest(QObject *parent)
    : QObject(parent)
{
}

void KDebugSettingsLoadingCategoriesTest::shouldHaveDefaultValues()
{
    KDebugSettingsLoadingCategories w;
    QVERIFY(w.customCategories().isEmpty());
    QVERIFY(w.environmentrules().isEmpty());
    QVERIFY(w.renameCategoriesList().isEmpty());
    QVERIFY(w.categoriesList().isEmpty());
    QVERIFY(w.qtKdeCategories().isEmpty());
    QVERIFY(!w.foundOverrideRule());
}

#include "moc_kdebugsettingsloadingcategoriestest.cpp"
