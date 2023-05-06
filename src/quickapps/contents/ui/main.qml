// SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import org.kde.kirigami 2.19 as Kirigami

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
        id: aboutAction
        displayHint: Kirigami.Action.AlwaysHide
        iconName: "kdebugsettings"
        text: i18nc("@action opens about app page", "About")
        onTriggered: { pageStack.layers.push("qrc:/AboutPage.qml") }
    }
    GlobalMenu {}
}
