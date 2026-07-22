// SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as QQC2
import org.kde.kirigami as Kirigami

import org.kde.kdebugsettings
import org.kde.kirigamiaddons.delegates as Delegates

Kirigami.ScrollablePage {
    id: page
    title: i18nc("@title", "KDE Application Rules")

    leftPadding: 20
    actions: [
        Kirigami.Action {
            displayComponent: Kirigami.SearchField {
                onAccepted: LoggingManager.kdeApplicationLoggingCategoryProxyModel.filterText = text
            }
        }
    ]

    ListView {
        id: listviewRules
        focus: true // keyboard navigation
        activeFocusOnTab: true // keyboard navigation
        reuseItems: true
        clip: true
        model: LoggingManager.kdeApplicationLoggingCategoryProxyModel
        delegate: Delegates.RoundedItemDelegate {
            highlighted: ListView.isCurrentItem
            onClicked: listviewRules.currentIndex = index

            RowLayout {
                width: parent.width

                QQC2.Label {
                    Layout.leftMargin: 4
                    text: model.description
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                    verticalAlignment: Text.AlignVCenter

                    QQC2.ToolTip.visible: hovered
                    QQC2.ToolTip.text: model.generatedToolTip
                }
                Item {
                    Layout.fillWidth: true
                }
                CategoryComboBox {
                    id: categoryType
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    property int rowIndex: index

                    // Re-evaluate once the ComboBox model is populated on startup.
                    currentIndex: count > 0 ? indexOfValue(loggingType) : -1
                    onActivated: () => {
                        listviewRules.model.setCategoryType(rowIndex, currentValue);
                    }
                }
            }
        }
    }
}
