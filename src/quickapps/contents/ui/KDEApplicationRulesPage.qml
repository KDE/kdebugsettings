// SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15 as QQC2
import org.kde.kirigami 2.15 as Kirigami
import org.kde.kirigamiaddons.labs.mobileform 0.1 as MobileForm

import org.kde.kdebugsettings 1.0

Kirigami.Page {
    id: root
    title: i18nc("@title", "KDE Application Rules")

    leftPadding: 20

    contextualActions: [
        aboutAction,
    ]
    ColumnLayout {
        spacing: Kirigami.Units.gridUnit
        width: parent.width - (Kirigami.Units.largeSpacing * 4)
        anchors.centerIn: parent
        anchors.fill: parent


        Component {
            id: loggingDelegate
            Item {
                width: listviewRules.width
                height: 50
                Column {
                    Text { text: description }
                }
            }
        }
        ListView {
            height: 400
            id: listviewRules
            focus: true // keyboard navigation
            activeFocusOnTab: true // keyboard navigation
            delegate: loggingDelegate
            //clip: true
            model: LoggingManager.qtKdeCategoryModel
        }
    }
}

