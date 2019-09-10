/*
  Copyright (c) 2015-2019 Montel Laurent <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

*/

#include <QApplication>

#include <config-kdebugsettings.h>
#include "kdebugsettingsdialog.h"
#include "changedebugmodejob.h"

#include <KLocalizedString>
#include <KAboutData>
#include <QCommandLineParser>
#include <KDBusService>
#include <QStandardPaths>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    /**
     * enable high dpi support
     */
    app.setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    KAboutData aboutData(QStringLiteral("kdebugsettings"), i18n("kdebugssettings"), QStringLiteral(KDEBUGSETTINGS_VERSION),
                         i18n("Configure debug settings"), KAboutLicense::GPL_V2,
                         i18n("(c) 2015-2019 kdebugsettings authors"));
    aboutData.addAuthor(i18n("Laurent Montel"), i18n("Maintainer"), QStringLiteral("montel@kde.org"));
    KAboutData::setApplicationData(aboutData);

    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);

    QCommandLineOption testModeOption(QStringLiteral("test-mode"), i18n("Enable QStandardPaths test mode, i.e. read/write settings used by unittests"));
    parser.addOption(testModeOption);

    QCommandLineOption changeDebugSettingOption(QStringLiteral("debug-mode"), i18n("Change debug mode as console (in console)"), QStringLiteral("Full|Info|Warning|Critical|Off"));
    parser.addOption(changeDebugSettingOption);
    parser.addPositionalArgument(
        QStringLiteral("logging category name"),
        i18n("Specify logging category name that you want to change debug mode (in console)"));

    parser.process(app);
    aboutData.processCommandLine(&parser);

    if (parser.isSet(testModeOption)) {
        QStandardPaths::setTestModeEnabled(true);
    }

    const QString changeModeValue = parser.value(changeDebugSettingOption);
    if (!changeModeValue.isEmpty() && !parser.positionalArguments().isEmpty()) {
        ChangeDebugModeJob job;
        job.setDebugMode(changeModeValue);
        qDebug() << " Change mode" << changeModeValue;
        return 1;
    } else {
        KDBusService service(KDBusService::Unique);
        KDebugSettingsDialog *dialog = new KDebugSettingsDialog;
        const int ret = dialog->exec();
        delete dialog;
        return ret;
    }
}
