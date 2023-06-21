/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#include "categorytypemodeltest.h"
#include "model/categorytypemodel.h"
#include <QTest>

QTEST_GUILESS_MAIN(CategoryTypeModelTest)
CategoryTypeModelTest::CategoryTypeModelTest(QObject *parent)
    : QObject{parent}
{
}

void CategoryTypeModelTest::shouldHaveDefaultValues()
{
    CategoryTypeModel model;
    // TODO
}

#include "moc_categorytypemodeltest.cpp"
