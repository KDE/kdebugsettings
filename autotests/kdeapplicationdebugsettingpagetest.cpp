/*
  Copyright (c) 2015-2018 Montel Laurent <montel@kde.org>

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

#include "kdeapplicationdebugsettingpagetest.h"
#include "../src/kdeapplicationdebugsettingpage.h"
#include "../src/kdeapplicationtreelistwidget.h"
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qtest.h>
#include <KTreeWidgetSearchLine>

KDEApplicationDebugSettingPageTest::KDEApplicationDebugSettingPageTest(QObject *parent)
    : QObject(parent)
{
}

KDEApplicationDebugSettingPageTest::~KDEApplicationDebugSettingPageTest()
{
}

void KDEApplicationDebugSettingPageTest::shouldHaveDefaultValue()
{
    KDEApplicationDebugSettingPage page;
    KDEApplicationTreeListWidget *listWidget = page.findChild<KDEApplicationTreeListWidget *>(QStringLiteral("listwidget"));
    QVERIFY(listWidget);

    QPushButton *selectAll = page.findChild<QPushButton *>(QStringLiteral("selectall"));
    QVERIFY(selectAll);

    QPushButton *deselectAll = page.findChild<QPushButton *>(QStringLiteral("deselectall"));
    QVERIFY(deselectAll);

    KTreeWidgetSearchLine *searchLine = page.findChild<KTreeWidgetSearchLine *>(QStringLiteral("searchline"));
    QVERIFY(searchLine);
    QVERIFY(searchLine->text().isEmpty());
}

QTEST_MAIN(KDEApplicationDebugSettingPageTest)
