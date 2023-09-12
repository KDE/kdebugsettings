// SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15 as QQC2
import org.kde.kirigami 2.15 as Kirigami

import org.kde.kdebugsettings 1.0

Kirigami.ScrollablePage {
    id: page2
    title: i18nc("@title", "Custom Rules")

    leftPadding: 20

    ListView {
        id: listviewRules
        reuseItems: true
        focus: true // keyboard navigation
        activeFocusOnTab: true // keyboard navigation
        clip: true
        model: LoggingManager.customCategoryModel
        delegate: Kirigami.BasicListItem {
            label: model.displayRule
            QQC2.Menu {
                id: contextMenu
                QQC2.MenuItem {
                    action: Kirigami.Action {
                        icon.name: "list-add"
                        text: i18nc("@action add custom rule", "Add Rule...")
                    }
                    onTriggered: {}
                }
                QQC2.MenuItem {
                    action: Kirigami.Action {
                        icon.name: "document-edit" // TODO fixit
                        text: i18nc("@action edit custom rule", "Edit Rule...")
                    }
                    onTriggered: {}
                }
                QQC2.MenuSeparator { }
                QQC2.MenuItem {
                    action: Kirigami.Action {
                        icon.name: "edit-delete"
                        text: i18nc("@action remove custom rule", "Remove Rule")
                    }
                    onTriggered: {}
                }
            }
            TapHandler {
                acceptedButtons: Qt.RightButton
                onTapped: contextMenu.popup()
            }
        }
    }
}

