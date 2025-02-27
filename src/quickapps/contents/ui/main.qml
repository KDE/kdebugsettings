// SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick
import QtQuick.Controls as QQC2
import org.kde.kirigami as Kirigami

import org.kde.kdebugsettings 1.0

Kirigami.ApplicationWindow {
    id: root

    pageStack {
        initialPage: MainPage {}
        defaultColumnWidth: root.width

        globalToolBar {
            style: Kirigami.ApplicationHeaderStyle.ToolBar
            showNavigationButtons: if (applicationWindow().pageStack.currentIndex > 0) {
                Kirigami.ApplicationHeaderStyle.ShowBackButton
            } else {
                0
            }
        }
    }
    Kirigami.Action {
        id: goToKdeApplicationCategories
        text: i18nc("@action", "Show KDE Application Categories")
        onTriggered: { pageStack.layers.push("qrc:/KDEApplicationRulesPage.qml") }
    }
    Kirigami.Action {
        id: goToCustomCategories
        text: i18nc("@action", "Show Custom Categories")
        onTriggered: { pageStack.layers.push("qrc:/CustomRulesPage.qml") }
    }
    Kirigami.Action {
        id: goToEnviromnentCategories
        text: i18nc("@action", "Show Environment Categories")
        onTriggered: { pageStack.layers.push("qrc:/EnvironmentVariableRulesPage.qml") }
    }
    Kirigami.Action {
        id: aboutAction
        displayHint: Kirigami.DisplayHint.AlwaysHide
        icon.name: "debug-run"
        text: i18nc("@action opens about app page", "About")
        onTriggered: { pageStack.layers.push("qrc:/AboutPage.qml") }
    }

    Kirigami.Action {
        id: helpAction
        displayHint: Kirigami.DisplayHint.AlwaysHide
        icon.name: "help-browser"
        text: i18nc("@action", "Open Handbook")
        onTriggered: { Qt.openUrlExternally("help:/kdebugsettings") }
    }
    Kirigami.Action {
        id: separatorAction
        displayHint: Kirigami.DisplayHint.AlwaysHide
        separator: true
    }
    Kirigami.Action {
        id: quitAction
        displayHint: Kirigami.DisplayHint.AlwaysHide
        text: i18nc("@menu-action", "Quit")
        icon.name: "gtk-quit"
        shortcut: StandardKey.Quit
        onTriggered: Qt.quit()
    }
    Kirigami.Action {
        id: saveAction
        displayHint: Kirigami.DisplayHint.AlwaysHide
        text: i18nc("@menu-action", "Save")
        icon.name: "document-save"
        shortcut: StandardKey.Save
        onTriggered: {
            // TODO
        }
    }
    GlobalMenu {}
}
