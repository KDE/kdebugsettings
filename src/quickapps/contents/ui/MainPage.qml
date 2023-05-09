// SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15 as QQC2
import org.kde.kirigami 2.15 as Kirigami
import org.kde.kirigamiaddons.labs.mobileform 0.1 as MobileForm

Kirigami.ScrollablePage {
    id: root
    title: i18n("Main Page")

    leftPadding: 20

    Kirigami.Action {
        id: goToKdeApplicationCategories
        // enabled: page.state === ""
        // iconName: "go-home"
        text: i18nc("@action", "Show KDE Application Categories")
        // onTriggered: pageStack.currentIndex = 0
    }
    Kirigami.Action {
        id: goToCustomCategories
        // enabled: page.state === ""
        // iconName: "go-home"
        text: i18nc("@action", "Show Custom Categories")
        // onTriggered: pageStack.currentIndex = 0
    }
    Kirigami.Action {
        id: goToEnviromnentCategories
        // enabled: page.state === ""
        // iconName: "go-home"
        text: i18nc("@action", "Show Environment Categories")
        // onTriggered: pageStack.currentIndex = 0
    }
    contextualActions: [
        goToKdeApplicationCategories,
        goToCustomCategories,
        goToEnviromnentCategories,
        helpAction,
        aboutAction
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
