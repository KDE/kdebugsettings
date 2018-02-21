/*
  Copyright (c) 2016-2018 Montel Laurent <montel@kde.org>

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
#include "renamecategorytest.h"
#include "../src/kdebugsettingsutil.h"
#include "../src/renamecategory.h"
#include <QTest>

RenameCategoryTest::RenameCategoryTest(QObject *parent)
    : QObject(parent)
{
}

RenameCategoryTest::~RenameCategoryTest()
{
}

void RenameCategoryTest::shouldParseRenameLine_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("newname");
    QTest::addColumn<QString>("original");
    QTest::addColumn<bool>("valid");
    QTest::newRow("empty") <<  QString() << QString() << QString() << false;
    QTest::newRow("validLine") << QStringLiteral("log linux") << QStringLiteral("linux") << QStringLiteral("log") << true;
    QTest::newRow("validLinewithspace") << QStringLiteral(" log linux  ") << QStringLiteral("linux") << QStringLiteral("log") << true;
    QTest::newRow("comment") << QStringLiteral("#log linux  ") << QString() << QString() << false;
    QTest::newRow("commentWithSpace") << QStringLiteral("   #log linux  ") << QString() << QString() << false;
    QTest::newRow("badline") << QStringLiteral("log") << QString() << QString() << false;
    QTest::newRow("comment-2") << QStringLiteral("#log linux") << QString() << QString() << false;

    QTest::newRow("linewithcomment") << QStringLiteral("log linux#comment about linux") << QStringLiteral("linux") << QStringLiteral("log") << true;
}

void RenameCategoryTest::shouldParseRenameLine()
{
    QFETCH(QString, input);
    QFETCH(QString, newname);
    QFETCH(QString, original);
    QFETCH(bool, valid);
    RenameCategory result;
    result.originalName = original;
    result.newName = newname;
    const RenameCategory cat = KDebugSettingsUtil::parseRenameCategory(input);
    QCOMPARE(cat, result);
    QCOMPARE(cat.isValid(), valid);
}

QTEST_MAIN(RenameCategoryTest)
