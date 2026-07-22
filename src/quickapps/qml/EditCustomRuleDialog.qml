// SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later
import QtQuick
import org.kde.kirigami as Kirigami
import QtQuick.Controls as QQC2
import QtQuick.Layouts
import org.kde.kdebugsettings

Kirigami.Dialog {
    id: dialog
    title: i18n("Edit Custom Rule")
    clip: true
    showCloseButton: false
    property alias categoryName: categoryNameField.text
    property alias categoryEnabled: categoryEnabled.checked
    property alias categoryType: categoryType.loggingType
    property bool editMode: false

    standardButtons: QQC2.Dialog.Ok | QQC2.Dialog.Cancel
    RowLayout {
        id: mainColumn
        spacing: Kirigami.Units.smallSpacing

        QQC2.Label {
            Layout.leftMargin: 4
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            verticalAlignment: Text.AlignVCenter
            text: i18n("Category:")
        }
        QQC2.TextField {
            id: categoryNameField
        }
        QQC2.Label {
            Layout.leftMargin: 4
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            verticalAlignment: Text.AlignVCenter
            text: i18n("Type:")
        }
        CategoryComboBox {
            id: categoryType
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
        }
        QQC2.CheckBox {
            id: categoryEnabled
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            text: i18n("Enabled")
        }
    }
    onAccepted: {
        if (editMode) {
            console.debug("Edit custom Not implemented yet");
        } else {
            LoggingManager.customCategoryModel.addCategory(categoryNameField.text, categoryEnabled.checked, categoryType.currentValue);
        }
    }
}
