/*
    SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include <QApplication>

#include "jobs/changedebugmodejob.h"
#include "kdebugsettingsdialog.h"
#include <KAboutData>
#include <KCrash>
#include <config-kdebugsettings.h>
#if HAVE_KDBUSADDONS
#include <KDBusService>
#endif
#include <KLocalizedString>
#include <QCommandLineParser>
#include <QStandardPaths>

#include <iostream>

#include <KIconTheme>

#define HAVE_STYLE_MANAGER __has_include(<KStyleManager>)
#if HAVE_STYLE_MANAGER
#include <KStyleManager>
#endif

int main(int argc, char **argv)
{
    KIconTheme::initTheme();
    QApplication app(argc, argv);

    KAboutData aboutData(QStringLiteral("kdebugsettings"),
                         i18n("KDebugSettings"),
                         QStringLiteral(KDEBUGSETTINGS_VERSION),
                         i18n("Configure debug settings"),
                         KAboutLicense::GPL_V2,
                         i18n("(c) 2015-%1 kdebugsettings authors", QStringLiteral("2024")));
    aboutData.addAuthor(i18nc("@info:credit", "Laurent Montel"), i18n("Maintainer"), QStringLiteral("montel@kde.org"));
#if HAVE_STYLE_MANAGER
    KStyleManager::initStyle();
#else // !HAVE_STYLE_MANAGER
#if defined(Q_OS_WIN) || defined(Q_OS_MACOS)
    QApplication::setStyle(QStringLiteral("breeze"));
#endif
#endif
    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("debug-run")));
    KAboutData::setApplicationData(aboutData);
    KCrash::initialize();

    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);

    const QCommandLineOption testModeOption(QStringLiteral("test-mode"), i18n("Enable QStandardPaths test mode, i.e. read/write settings used by unittests"));
    parser.addOption(testModeOption);

    const QCommandLineOption switchFullDebugOption(QStringLiteral("enable-full-debug"), i18n("Activate full debug for all modules."));
    parser.addOption(switchFullDebugOption);
    const QCommandLineOption switchOffDebugOption(QStringLiteral("disable-full-debug"), i18n("Disable full debug for all modules."));
    parser.addOption(switchOffDebugOption);

    const QCommandLineOption changeDebugSettingOption(QStringLiteral("debug-mode"),
                                                      i18n("Change debug mode as console (in console)"),
                                                      QStringLiteral("Full|Info|Warning|Critical|Off"));
    parser.addOption(changeDebugSettingOption);
    parser.addPositionalArgument(QStringLiteral("logging category name"),
                                 i18n("Specify logging category name that you want to change debug mode (in console)"));

    parser.process(app);
    aboutData.processCommandLine(&parser);

    if (parser.isSet(testModeOption)) {
        QStandardPaths::setTestModeEnabled(true);
    }

    if (parser.isSet(switchFullDebugOption)) {
        ChangeDebugModeJob job;
        job.setDebugMode(QStringLiteral("Full"));
        job.setWithoutArguments(true);
        if (!job.start()) {
            std::cout << i18n("Impossible to change debug mode").toLocal8Bit().data() << std::endl;
        }

        return 1;
    }
    if (parser.isSet(switchOffDebugOption)) {
        ChangeDebugModeJob job;
        job.setDebugMode(QStringLiteral("Off"));
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
#if HAVE_KDBUSADDONS
        KDBusService service(KDBusService::Unique);
#endif
        auto dialog = new KDebugSettingsDialog;
        const int ret = dialog->exec();
        delete dialog;
        return ret;
    }
}
