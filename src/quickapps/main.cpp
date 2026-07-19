/*
    SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include <KLocalizedQmlContext>
#include <QApplication>

#include "jobs/changedebugmodejob.h"
#include "kdebugsettingscommandlineparser.h"
#include "loggingmanager.h"
#include "model/categorytypeproxymodel.h"
#include "model/customloggingcategorymodel.h"
#include "model/customloggingcategoryproxymodel.h"
#include "model/kdeapplicationloggingcategorymodel.h"
#include "model/kdeapplicationloggingcategoryproxymodel.h"
#include <config-kdebugsettings.h>

#include <KAboutData>
#if WITH_DBUS
#include <KDBusService>
#else
#include <kdsingleapplication.h>
#endif
#include <KLocalizedString>
#include <QCommandLineParser>
#include <QStandardPaths>

#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QUrl>

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
    // Default to org.kde.desktop style unless the user forces another style
    if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
        QQuickStyle::setStyle(u"org.kde.desktop"_s);
    }

    KStyleManager::initStyle();

    KLocalizedString::setApplicationDomain("kdebugsettings"_ba);
    KAboutData aboutData(u"kdebugsettingsquick"_s,
                         i18n("KDebugSettings"),
                         QStringLiteral(KDEBUGSETTINGS_VERSION),
                         i18n("Configure debug settings"),
                         KAboutLicense::GPL_V2,
                         i18n("(c) 2023-%1 kdebugsettings authors", u"2026"_s));
    aboutData.addAuthor(i18nc("@info:credit", "Laurent Montel"), i18n("Maintainer"), u"montel@kde.org"_s);
    QApplication::setWindowIcon(QIcon::fromTheme(u"debug-run"_s));
    KAboutData::setApplicationData(aboutData);

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

        QQmlApplicationEngine engine;

        qmlRegisterSingletonInstance("org.kde.kdebugsettings", 1, 0, "LoggingManager", &LoggingManager::self());
        qRegisterMetaType<CustomLoggingCategoryModel *>("CustomLoggingCategoryModel *");
        qRegisterMetaType<KDEApplicationLoggingCategoryModel *>("KDEApplicationLoggingCategoryModel *");
        qmlRegisterType<CategoryTypeProxyModel>("org.kde.kdebugsettings", 1, 0, "CategoryTypeProxyModel");
        qmlRegisterType<CustomLoggingCategoryProxyModel>("org.kde.kdebugsettings", 1, 0, "CustomLoggingCategoryProxyModel");
        qmlRegisterType<KDEApplicationLoggingCategoryProxyModel>("org.kde.kdebugsettings", 1, 0, "KDEApplicationLoggingCategoryProxyModel");

        qmlRegisterSingletonType("org.kde.kdebugsettings", 1, 0, "About", [](QQmlEngine *engine, QJSEngine *) -> QJSValue {
            return engine->toScriptValue(KAboutData::applicationData());
        });
        engine.rootContext()->setContextObject(new KLocalizedQmlContext(&engine));
        engine.load(QUrl(u"qrc:///main.qml"_s));
        // Exit on QML load error.
        if (engine.rootObjects().isEmpty()) {
            qWarning() << " Error during loading main.qml";
            return 1;
        }
        return app.exec();
    }
}
