/*
    SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdebugsettingsdialogtest.h"
#include "categorywarning.h"
#include "kdebugsettingsdialog.h"
#include "loadtoolbutton.h"
#include "savetoolbutton.h"
#include <QDialogButtonBox>
#include <QPushButton>
#include <QStandardPaths>
#include <QTabWidget>
#include <QTest>

KDebugSettingsDialogTest::KDebugSettingsDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

KDebugSettingsDialogTest::~KDebugSettingsDialogTest() = default;

void KDebugSettingsDialogTest::shouldHaveDefaultValue()
{
    KDebugSettingsDialog dlg;
    auto buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(),
             QDialogButtonBox::RestoreDefaults | QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Help | QDialogButtonBox::Apply);
    auto tab = dlg.findChild<QTabWidget *>(QStringLiteral("tabwidget"));
    QVERIFY(tab);
    for (int i = 0; i < tab->count(); ++i) {
        const QString objName = tab->widget(i)->objectName();
        const bool hasCorrectName = (objName == QLatin1StringView("kdeapplicationsettingspage")) || (objName == QLatin1StringView("customsettingspage"))
            || (objName == QLatin1StringView("environmentsettingsrulespage"));
        QVERIFY(hasCorrectName);
    }
    auto saveAs = buttonBox->findChild<SaveToolButton *>(QStringLiteral("saveas_button"));
    QVERIFY(saveAs);
    auto load = buttonBox->findChild<LoadToolButton *>(QStringLiteral("load_button"));
    QVERIFY(load);
    QVERIFY(load->menu());
    auto insertCategories = buttonBox->findChild<QPushButton *>(QStringLiteral("insert_button"));
    QVERIFY(insertCategories);
    auto categoryWarning = dlg.findChild<CategoryWarning *>(QStringLiteral("categorywarning"));
    QVERIFY(categoryWarning);
    QVERIFY(!categoryWarning->isVisible());
}

QTEST_MAIN(KDebugSettingsDialogTest)

#include "moc_kdebugsettingsdialogtest.cpp"
