/*
    SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "ki18n_version.h"
#include <KLocalizedQmlContext>
#include <QApplication>

#include "jobs/changedebugmodejob.h"
#include "ki18n_version.h"
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

#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QUrl>
#include <QtQml>

#include <iostream>

#include <KIconTheme>

#include <KStyleManager>

int main(int argc, char **argv)
{
    KIconTheme::initTheme();

    QApplication app(argc, argv);
#if !WITH_DBUS
    KDSingleApplication sapp;
#endif
    // Default to org.kde.desktop style unless the user forces another style
    if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
        QQuickStyle::setStyle(QStringLiteral("org.kde.desktop"));
    }

    KStyleManager::initStyle();

    KLocalizedString::setApplicationDomain(QByteArrayLiteral("kdebugsettings"));
    KAboutData aboutData(QStringLiteral("kdebugsettingsquick"),
                         i18n("KDebugSettings"),
                         QStringLiteral(KDEBUGSETTINGS_VERSION),
                         i18n("Configure debug settings"),
                         KAboutLicense::GPL_V2,
                         i18n("(c) %1 kdebugsettings authors", QStringLiteral("2023")));
    aboutData.addAuthor(i18nc("@info:credit", "Laurent Montel"), i18n("Maintainer"), QStringLiteral("montel@kde.org"));
    KAboutData::setApplicationData(aboutData);

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
        engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
        // Exit on QML load error.
        if (engine.rootObjects().isEmpty()) {
            qDebug() << " Error during loading main.qml";
            return 1;
        }
        return app.exec();
    }
}
