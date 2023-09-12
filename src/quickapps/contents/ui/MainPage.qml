// SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15 as QQC2
import org.kde.kirigami 2.15 as Kirigami

Kirigami.Page {
    id: root

    leftPadding: 20


    actions: [
        goToKdeApplicationCategories,
        goToCustomCategories,
        goToEnviromnentCategories,
        saveAction,
        separatorAction,
        helpAction,
        aboutAction,
        separatorAction,
        quitAction
    ]
    ColumnLayout {
        spacing: Kirigami.Units.gridUnit
        width: parent.width - (Kirigami.Units.largeSpacing * 4)
        anchors.centerIn: parent
        Kirigami.Icon {
            Layout.alignment: Qt.AlignHCenter
            source: "debug-run"
            implicitWidth: Kirigami.Units.iconSizes.enormous
            implicitHeight: implicitWidth
        }
        Kirigami.Heading {
            Layout.alignment: Qt.AlignHCenter
            text: i18nc("@title", "Welcome to kdebugsettings")
        }
    }
}
