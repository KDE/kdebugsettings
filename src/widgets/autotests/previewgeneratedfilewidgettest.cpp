/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "previewgeneratedfilewidgettest.h"
#include "previewgeneratedfilewidget.h"
#include <QPlainTextEdit>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(PreviewGeneratedFileWidgetTest)
using namespace Qt::Literals::StringLiterals;
PreviewGeneratedFileWidgetTest::PreviewGeneratedFileWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void PreviewGeneratedFileWidgetTest::shouldHaveDefaultValues()
{
    const PreviewGeneratedFileWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTextEdit = w.findChild<QPlainTextEdit *>(u"mTextEdit"_s);
    QVERIFY(mTextEdit);
}