// SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as QQC2
import org.kde.kirigami as Kirigami

import org.kde.kdebugsettings 1.0
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
        model: LoggingManager.kdeApplicationLoggingCategoryProxyModel;
        delegate:  Delegates.RoundedItemDelegate {
            highlighted: ListView.isCurrentItem
            onClicked: listviewRules.currentIndex = index

            RowLayout {
                width: parent.width

                QQC2.Label {
                    Layout.fillHeight: true
                    Layout.leftMargin: 4
                    Layout.alignment: Qt.AlignLeft
                    text: model.description
                }
                Item {
                    Layout.fillWidth: true
                }
                QQC2.ComboBox {
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                    // Keep the delegate row index distinct from ComboBox activation index.
                    property int rowIndex: index

                    model: CategoryTypeProxyModel {
                        sourceModel: LoggingManager.categoryTypeModel
                        showOffType: true
                    }
                    textRole: "display"
                    valueRole: "categoryType"
                    currentIndex: LoggingManager.categoryTypeModel.indexOfCategory(listviewRules.model.categoryType)
                    onActivated: () => {
                        listviewRules.model.setCategoryType(rowIndex, currentValue)
                    }
                }
            }
        }
    }
}
