// SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as QQC2
import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.delegates 1.0 as Delegates

import org.kde.kdebugsettings

Kirigami.ScrollablePage {
    id: page2
    title: i18nc("@title", "Custom Rules")
    leftPadding: 20
    actions: [
        Kirigami.Action {
            displayComponent: Kirigami.SearchField {
                onAccepted: LoggingManager.customLoggingCategoryProxyModel.filterText = text
            }
        }
    ]
    EditCustomRuleDialog {
        id: editCustomRuleDialog
    }

    ListView {
        id: listviewRules
        reuseItems: true
        activeFocusOnTab: true // keyboard navigation
        focus: true // keyboard navigation
        model: LoggingManager.customLoggingCategoryProxyModel
        delegate: Delegates.RoundedItemDelegate {
            required property string displayRule
            required property int index

            text: displayRule
            highlighted: ListView.isCurrentItem
            onClicked: listviewRules.currentIndex = index

        }
        TapHandler {
            acceptedButtons: Qt.RightButton
            onTapped: contextMenu.popup()
        }

        QQC2.Menu {
            id: contextMenu
            QQC2.MenuItem {
                icon.name: "list-add"
                text: i18nc("@action add custom rule", "Add Rule…")
                onTriggered: {
                    console.debug("Not implemented yet")
                    editCustomRuleDialog.open();
                    // TODO
                }
            }
            QQC2.MenuItem {
                visible: listviewRules.currentIndex !== -1 && listviewRules.count !== 0
                icon.name: "document-edit"
                text: i18nc("@action edit custom rule", "Edit Rule…")
                onTriggered: {
                    console.debug("Not implemented yet")
                    editCustomRuleDialog.open();
                    // TODO
                }
            }
            QQC2.MenuSeparator {
                visible: listviewRules.currentIndex !== -1 && listviewRules.count !== 0
            }
            QQC2.MenuItem {
                visible: listviewRules.currentIndex !== -1 && listviewRules.count !== 0
                icon.name: "edit-delete"
                text: i18nc("@action remove custom rule", "Remove Rule")
                onTriggered: {
                    console.debug("Not implemented yet")
                    // TODO
                }
            }
        }
    }
}
