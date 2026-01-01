/*
    SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "config-kdebugsettings.h"

#include <QApplication>

#include "jobs/changedebugmodejob.h"
#include "kdebugsettingsdialog.h"
#include <KAboutData>
#include <KCrash>
#include <config-kdebugsettings.h>
#if WITH_DBUS
#include <KDBusService>
#include <KWindowSystem>
#else
#include <kdsingleapplication.h>
#endif
#include <KLocalizedString>
#include <QCommandLineParser>
#include <QStandardPaths>

#include <iostream>

#include <KIconTheme>

#include <KStyleManager>
using namespace Qt::Literals::StringLiterals;
int main(int argc, char **argv)
{
    KIconTheme::initTheme();
    QApplication app(argc, argv);
#if !WITH_DBUS
    KDSingleApplication sapp;
#endif

    KAboutData aboutData(u"kdebugsettings"_s,
                         i18n("KDebugSettings"),
                         QStringLiteral(KDEBUGSETTINGS_VERSION),
                         i18n("Configure debug settings"),
                         KAboutLicense::GPL_V2,
                         i18n("(c) 2015-%1 kdebugsettings authors", u"2026"_s));
    aboutData.addAuthor(i18nc("@info:credit", "Laurent Montel"), i18n("Maintainer"), u"montel@kde.org"_s);
    KStyleManager::initStyle();
    QApplication::setWindowIcon(QIcon::fromTheme(u"debug-run"_s));
    KAboutData::setApplicationData(aboutData);
    KCrash::initialize();

    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);

    const QCommandLineOption testModeOption(u"test-mode"_s, i18n("Enable QStandardPaths test mode, i.e. read/write settings used by unittests"));
    parser.addOption(testModeOption);

    const QCommandLineOption switchFullDebugOption(u"enable-full-debug"_s, i18n("Activate full debug for all modules."));
    parser.addOption(switchFullDebugOption);
    const QCommandLineOption switchOffDebugOption(u"disable-full-debug"_s, i18n("Disable full debug for all modules."));
    parser.addOption(switchOffDebugOption);

    const QCommandLineOption changeDebugSettingOption(u"debug-mode"_s, i18n("Change debug mode as console (in console)"), u"Full|Info|Warning|Critical|Off"_s);
    parser.addOption(changeDebugSettingOption);
    parser.addPositionalArgument(u"logging category name"_s, i18n("Specify logging category name that you want to change debug mode (in console)"));

    parser.process(app);
    aboutData.processCommandLine(&parser);

    if (parser.isSet(testModeOption)) {
        QStandardPaths::setTestModeEnabled(true);
    }

    if (parser.isSet(switchFullDebugOption)) {
        ChangeDebugModeJob job;
        job.setDebugMode(u"Full"_s);
        job.setWithoutArguments(true);
        if (!job.start()) {
            std::cout << i18n("Impossible to change debug mode").toLocal8Bit().data() << std::endl;
        }

        return 1;
    }
    if (parser.isSet(switchOffDebugOption)) {
        ChangeDebugModeJob job;
        job.setDebugMode(u"Off"_s);
        job.setWithoutArguments(true);
        if (!job.start()) {
            std::cout << i18n("Impossible to change debug mode").toLocal8Bit().data() << std::endl;
        }
        return 1;
    }
    const QString changeModeValue = parser.value(changeDebugSettingOption);
    if (!changeModeValue.isEmpty() && !parser.positionalArguments().isEmpty()) {
        ChangeDebugModeJob job;
        job.setDebugMode(changeModeValue);
        job.setLoggingCategoriesName(parser.positionalArguments());
        if (!job.start()) {
            std::cout << i18n("Impossible to change debug mode").toLocal8Bit().data() << std::endl;
        }
        return 1;
    } else {
#if WITH_DBUS
        KDBusService service(KDBusService::Unique);
#else
        if (!sapp.isPrimaryInstance()) {
            return 0;
        }
#endif
        auto dialog = new KDebugSettingsDialog;

#if WITH_DBUS
        QObject::connect(&service, &KDBusService::activateRequested, dialog, [dialog] {
            KWindowSystem::updateStartupId(dialog->windowHandle());
            KWindowSystem::activateWindow(dialog->windowHandle());
        });
#endif
        const int ret = dialog->exec();
        delete dialog;
        return ret;
    }
}
