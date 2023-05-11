// SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15 as QQC2
import org.kde.kirigami 2.15 as Kirigami
import org.kde.kirigamiaddons.labs.mobileform 0.1 as MobileForm

import org.kde.kdebugsettings 1.0

Kirigami.ScrollablePage {
    id: root
    title: i18nc("@title", "Custom111 Rules")

    leftPadding: 20

    contextualActions: [
        aboutAction,
        quitAction,
    ]
    ColumnLayout {
        spacing: Kirigami.Units.gridUnit
        width: parent.width - (Kirigami.Units.largeSpacing * 4)
        anchors.centerIn: parent
            // TODO remove it.
            Text {
                text: "List";
            }
            Component {
                id: loggingDelegate
                Item {
                    width: 180; height: 40
                    Column {
                        Text { text: "cccc" + displayRule }
                    }
                }
            }
            ListView {
                delegate: loggingDelegate
                model: LoggingManager.customCategoryModel
            }
    }
}

