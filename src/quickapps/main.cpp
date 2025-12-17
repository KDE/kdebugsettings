/*
    SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

using namespace Qt::Literals::StringLiterals;

#include <KLocalizedQmlContext>
#include <QApplication>

#include "jobs/changedebugmodejob.h"
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
        QQuickStyle::setStyle(u"org.kde.desktop"_s);
    }

    KStyleManager::initStyle();

    KLocalizedString::setApplicationDomain("kdebugsettings"_ba);
    KAboutData aboutData(u"kdebugsettingsquick"_s,
                         i18n("KDebugSettings"),
                         QStringLiteral(KDEBUGSETTINGS_VERSION),
                         i18n("Configure debug settings"),
                         KAboutLicense::GPL_V2,
                         i18n("(c) %1 kdebugsettings authors", u"2023"_s));
    aboutData.addAuthor(i18nc("@info:credit", "Laurent Montel"), i18n("Maintainer"), u"montel@kde.org"_s);
    KAboutData::setApplicationData(aboutData);

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
            qDebug() << " Error during loading main.qml";
            return 1;
        }
        return app.exec();
    }
}
