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

#include "kdeapplicationlistwidgettest.h"
#include "../src/kdeapplicationlistwidget.h"
#include <qtest.h>

KDeApplicationListWidgetTest::KDeApplicationListWidgetTest(QObject *parent)
    : QObject(parent)
{

}

KDeApplicationListWidgetTest::~KDeApplicationListWidgetTest()
{

}

void KDeApplicationListWidgetTest::shouldHaveDefaultValue()
{
    KDeApplicationListWidget widgetList;
    QCOMPARE(widgetList.count(), 0);
}

void KDeApplicationListWidgetTest::shouldHaveAddRules()
{
    KDeApplicationListWidget widgetList;
    Category::List lst;
    int count = 10;
    for (int i = 0; i < count; ++i) {
        Category cat;
        cat.description = QStringLiteral("desc%1").arg(i);
        cat.enabled = true;
        cat.logName = cat.description;
        lst.append(cat);
    }
    widgetList.fillList(lst);
    QCOMPARE(widgetList.count(), count);
}

void KDeApplicationListWidgetTest::shouldReturnRules()
{
    KDeApplicationListWidget widgetList;
    Category::List lst;
    Category cat;
    cat.description = QStringLiteral("desc");
    cat.enabled = true;
    cat.logName = cat.description;
    lst.append(cat);
    widgetList.fillList(lst);
    QStringList rules = widgetList.rules();
    QCOMPARE(rules.count(), 1);
    QString result = cat.description + QLatin1Literal("=true");
    QCOMPARE(rules.at(0), result);
    //Add more test
}


QTEST_MAIN(KDeApplicationListWidgetTest)
