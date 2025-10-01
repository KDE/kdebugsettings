/*
    SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdebugsettingsdialogtest.h"
using namespace Qt::Literals::StringLiterals;

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
    auto buttonBox = dlg.findChild<QDialogButtonBox *>(u"buttonbox"_s);
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(),
             QDialogButtonBox::RestoreDefaults | QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Help | QDialogButtonBox::Apply);
    auto tab = dlg.findChild<QTabWidget *>(u"tabwidget"_s);
    QVERIFY(tab);
    for (int i = 0; i < tab->count(); ++i) {
        const QString objName = tab->widget(i)->objectName();
        const bool hasCorrectName =
            (objName == "kdeapplicationsettingspage"_L1) || (objName == "customsettingspage"_L1) || (objName == "environmentsettingsrulespage"_L1);
        QVERIFY(hasCorrectName);
    }
    auto saveAs = buttonBox->findChild<SaveToolButton *>(u"saveas_button"_s);
    QVERIFY(saveAs);
    auto load = buttonBox->findChild<LoadToolButton *>(u"load_button"_s);
    QVERIFY(load);
    QVERIFY(load->menu());
    auto insertCategories = buttonBox->findChild<QPushButton *>(u"insert_button"_s);
    QVERIFY(insertCategories);
    auto categoryWarning = dlg.findChild<CategoryWarning *>(u"categorywarning"_s);
    QVERIFY(categoryWarning);
    QVERIFY(!categoryWarning->isVisible());
}

QTEST_MAIN(KDebugSettingsDialogTest)

#include "moc_kdebugsettingsdialogtest.cpp"
