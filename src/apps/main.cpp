/*
    SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "config-kdebugsettings.h"

#include <QApplication>
#include <QTimer>

#include "jobs/changedebugmodejob.h"
#include "kdebugsettingscommandlineparser.h"
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
    KDebugSettingsCommandLineParser commandLineParser(&parser);

    aboutData.setupCommandLine(&parser);

    parser.process(app);
    aboutData.processCommandLine(&parser);

    if (parser.isSet(KDebugSettingsCommandLineParser::optionParserFromEnum(KDebugSettingsCommandLineParser::OptionParser::TestMode))) {
        QStandardPaths::setTestModeEnabled(true);
    }

    if (parser.isSet(KDebugSettingsCommandLineParser::optionParserFromEnum(KDebugSettingsCommandLineParser::OptionParser::EnableFullDebug))) {
        ChangeDebugModeJob job;
        job.setDebugMode(u"Full"_s);
        job.setWithoutArguments(true);
        if (!job.start()) {
            std::cout << i18n("Impossible to change debug mode").toLocal8Bit().data() << std::endl;
        }

        return 1;
    }
    if (parser.isSet(KDebugSettingsCommandLineParser::optionParserFromEnum(KDebugSettingsCommandLineParser::OptionParser::DisableFullDebug))) {
        ChangeDebugModeJob job;
        job.setDebugMode(u"Off"_s);
        job.setWithoutArguments(true);
        if (!job.start()) {
            std::cout << i18n("Impossible to change debug mode").toLocal8Bit().data() << std::endl;
        }
        return 1;
    }
    const QString changeModeValue =
        parser.value(KDebugSettingsCommandLineParser::optionParserFromEnum(KDebugSettingsCommandLineParser::OptionParser::DebugMode));
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
        if (parser.isSet(KDebugSettingsCommandLineParser::optionParserFromEnum(KDebugSettingsCommandLineParser::OptionParser::SelfTest))) {
            QTimer::singleShot(std::chrono::milliseconds(250), &app, &QCoreApplication::quit);
        }
        dialog->show();
        int result = app.exec();
        delete dialog;
        return result;
    }
}
