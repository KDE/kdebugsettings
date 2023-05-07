/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include <QApplication>

#include "jobs/changedebugmodejob.h"
#include "loggingmanager.h"
#include "model/loggingcategorymodel.h"
#include <config-kdebugsettings.h>

#include <KAboutData>
#include <KDBusService>
#include <KLocalizedString>
#include <QCommandLineParser>
#include <QStandardPaths>

#include <QQmlApplicationEngine>
#include <QUrl>
#include <QtQml>

#include <iostream>

class About : public QObject
{
    Q_OBJECT
    Q_PROPERTY(KAboutData data READ data CONSTANT)
    Q_REQUIRED_RESULT static KAboutData data()
    {
        return KAboutData::applicationData();
    }

public:
    using QObject::QObject;
};

int main(int argc, char **argv)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif

    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("kdebugsettings");
    KAboutData aboutData(QStringLiteral("kdebugsettingsquick"),
                         i18n("KDebugSettings"),
                         QStringLiteral(KDEBUGSETTINGS_VERSION),
                         i18n("Configure debug settings"),
                         KAboutLicense::GPL_V2,
                         i18n("(c) %1 kdebugsettings authors", QStringLiteral("2023")));
    aboutData.addAuthor(i18n("Laurent Montel"), i18n("Maintainer"), QStringLiteral("montel@kde.org"));
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
        KDBusService service(KDBusService::Unique);
        QQmlApplicationEngine engine;
        engine.rootContext()->setContextObject(new KLocalizedContext(&engine));

        LoggingManager loggingManager;
        qmlRegisterSingletonInstance("org.kde.kdebugsettings", 1, 0, "LoggingManager", &loggingManager);
        qRegisterMetaType<LoggingCategoryModel *>("LoggingCategoryModel *");
        auto about = new About;
        qmlRegisterSingletonInstance("org.kde.kdebugsettings", 1, 0, "About", about);
        engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
        // Exit on QML load error.
        if (engine.rootObjects().isEmpty()) {
            return 1;
        }
        return app.exec();
    }
}
#include "main.moc"
