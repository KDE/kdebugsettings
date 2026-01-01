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
                onAccepted: loggingDebugProxyModel.filterText = text
            }
        }
    ]

    ListView {
        id: listviewRules
        focus: true // keyboard navigation
        activeFocusOnTab: true // keyboard navigation
        reuseItems: true
        clip: true
        model: KDEApplicationLoggingCategoryProxyModel {
            id: loggingDebugProxyModel
            sourceModel: LoggingManager.qtKdeCategoryModel
        }
        delegate:  Delegates.RoundedItemDelegate {
            RowLayout {
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
                    model: CategoryTypeProxyModel {
                        sourceModel: LoggingManager.categoryTypeModel
                        showOffType: true
                    }
                    textRole: "display"
                    valueRole: "categoryType"
                    currentIndex: LoggingManager.categoryTypeModel.indexOfCategory(listviewRules.model.categoryType)
                    onActivated: {
                        // TODO
                    }
                }
            }
        }
    }
}
