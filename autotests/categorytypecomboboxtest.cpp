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

#include "categorytypecomboboxtest.h"
#include "../src/categorytypecombobox.h"
#include <qtest.h>

CategoryTypeComboBoxTest::CategoryTypeComboBoxTest(QObject *parent)
    : QObject(parent)
{

}

CategoryTypeComboBoxTest::~CategoryTypeComboBoxTest()
{

}

void CategoryTypeComboBoxTest::shouldHaveDefaultValue()
{
    CategoryTypeComboBox w;
    QCOMPARE(w.count(), 4);
}

void CategoryTypeComboBoxTest::shouldSetType_data()
{
    QTest::addColumn<QString>("input");

    QTest::newRow("empty") <<  QString();
    QTest::newRow("warning") <<  QStringLiteral("warning");
    QTest::newRow("invalid") <<  QStringLiteral("allss");
    QTest::newRow("debug") <<  QStringLiteral("debug");
    QTest::newRow("critical") <<  QStringLiteral("critical");
}

void CategoryTypeComboBoxTest::shouldSetType()
{
    QFETCH(QString, input);
    CategoryTypeComboBox w;
    w.setType(input);
    QString result;
    if (input.isEmpty()) {
        result = QStringLiteral("all");
    }
    const int pos = w.findData(input);
    if (pos < 0) {
        result = QString();
        QCOMPARE(w.type(), result);
    } else {
        result = w.type();
        QCOMPARE(w.type(), result);
    }
}

QTEST_MAIN(CategoryTypeComboBoxTest)
