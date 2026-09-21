/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "previewgeneratedfiledialogtest.h"
#include "previewgeneratedfiledialog.h"
#include "previewgeneratedfilewidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(PreviewGeneratedFileDialogTest)
using namespace Qt::Literals::StringLiterals;
PreviewGeneratedFileDialogTest::PreviewGeneratedFileDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void PreviewGeneratedFileDialogTest::shouldHaveDefaultValues()
{
    const PreviewGeneratedFileDialog w;
    QVERIFY(!w.windowTitle().isEmpty());
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mPreviewGeneratedFileWidget = w.findChild<PreviewGeneratedFileWidget *>(u"mPreviewGeneratedFileWidget"_s);
    QVERIFY(mPreviewGeneratedFileWidget);

    auto buttonBox = w.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
}
#include "moc_previewgeneratedfiledialogtest.cpp"
