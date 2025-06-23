/*
    SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#include "renamecategorytest.h"
using namespace Qt::Literals::StringLiterals;

#include "kdebugsettingsutil.h"
#include "renamecategory.h"
#include <QTest>

RenameCategoryTest::RenameCategoryTest(QObject *parent)
    : QObject(parent)
{
}

RenameCategoryTest::~RenameCategoryTest() = default;

void RenameCategoryTest::shouldParseRenameLine_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("newname");
    QTest::addColumn<QString>("original");
    QTest::addColumn<bool>("valid");
    QTest::newRow("empty") << QString() << QString() << QString() << false;
    QTest::newRow("validLine") << u"log linux"_s << u"linux"_s << QStringLiteral("log") << true;
    QTest::newRow("validLinewithspace") << u" log linux  "_s << u"linux"_s << QStringLiteral("log") << true;
    QTest::newRow("comment") << u"#log linux  "_s << QString() << QString() << false;
    QTest::newRow("commentWithSpace") << u"   #log linux  "_s << QString() << QString() << false;
    QTest::newRow("badline") << u"log"_s << QString() << QString() << false;
    QTest::newRow("comment-2") << u"#log linux"_s << QString() << QString() << false;

    QTest::newRow("linewithcomment") << u"log linux#comment about linux"_s << u"linux"_s << QStringLiteral("log") << true;
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
    const RenameCategory cat = KDebugSettingsUtil::parseRenameCategory(input, QString());
    QCOMPARE(cat, result);
    QCOMPARE(cat.isValid(), valid);
}

QTEST_MAIN(RenameCategoryTest)

#include "moc_renamecategorytest.cpp"
