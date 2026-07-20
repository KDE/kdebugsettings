// SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later
import QtQuick
import org.kde.kirigami as Kirigami
import QtQuick.Controls as QQC2
import QtQuick.Layouts
import org.kde.kdebugsettings 1.0
Kirigami.Dialog {
    id: dialog
    title: i18n("Edit Custom Rule")
    clip: true

    standardButtons: QQC2.Dialog.Ok | QQC2.Dialog.Cancel
    RowLayout {
        id: mainColumn
        spacing: Kirigami.Units.smallSpacing

        QQC2.Label {
            Layout.fillHeight: true
            Layout.leftMargin: 4
            Layout.alignment: Qt.AlignLeft
            text: i18n("Category:")
        }
        QQC2.TextField {
            id: categoryName
        }
        QQC2.Label {
            Layout.fillHeight: true
            Layout.leftMargin: 4
            Layout.alignment: Qt.AlignLeft
            text: i18n("Type:")
        }
        QQC2.ComboBox {
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

            model: CategoryTypeProxyModel {
                sourceModel: LoggingManager.categoryTypeModel
                showOffType: true
            }
            textRole: "display"
            valueRole: "categoryType"
        }
    }
}
