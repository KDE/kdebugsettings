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

#include "kdeapplicationdebugsettingpagetest.h"
#include "../src/kdeapplicationdebugsettingpage.h"
#include <qlistwidget.h>
#include <qtest.h>

KDeApplicationDebugSettingPageTest::KDeApplicationDebugSettingPageTest(QObject *parent)
    : QObject(parent)
{

}

KDeApplicationDebugSettingPageTest::~KDeApplicationDebugSettingPageTest()
{

}

void KDeApplicationDebugSettingPageTest::shouldHaveDefaultValue()
{
    KDeApplicationDebugSettingPage page;
    QListWidget *listWidget = page.findChild<QListWidget *>(QStringLiteral("listwidget"));
    QVERIFY(listWidget);
}

QTEST_MAIN(KDeApplicationDebugSettingPageTest)
