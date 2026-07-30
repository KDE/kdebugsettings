/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

import QtQuick
import QtQuick.Controls as QQC2
import QtQuick.Layouts
import org.kde.kcmutils as KCM
import org.kde.kirigami as Kirigami

KCM.ScrollViewKCM {
    implicitHeight: Kirigami.Units.gridUnit * 28
    implicitWidth: Kirigami.Units.gridUnit * 28
    actions: [
        Kirigami.Action {
            id: goToKdeApplicationCategories
            text: i18nc("@action", "Show KDE Application Categories")
            onTriggered: {
                pageStack.layers.push(Qt.resolvedUrl("KDEApplicationRulesPage.qml"));
            }
        },
        Kirigami.Action {
            id: goToCustomCategories
            text: i18nc("@action", "Show Custom Categories")
            onTriggered: {
                pageStack.layers.push(Qt.resolvedUrl("CustomRulesPage.qml"));
            }
        },
        Kirigami.Action {
            id: goToEnviromnentCategories
            text: i18nc("@action", "Show Environment Categories")
            onTriggered: {
                pageStack.layers.push(Qt.resolvedUrl("EnvironmentVariableRulesPage.qml"));
            }
        }
    ]
}
