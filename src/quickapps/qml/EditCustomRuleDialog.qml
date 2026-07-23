// SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later
import QtQuick
import org.kde.kirigami as Kirigami
import QtQuick.Controls as QQC2
import QtQuick.Layouts
import org.kde.kdebugsettings

Kirigami.Dialog {
    id: dialog
    title: editMode ? i18nc("@title:window", "Edit Custom Rule") : i18nc("@title:window", "Create Custom Rule")
    clip: true
    showCloseButton: false
    property alias categoryName: categoryNameField.text
    property alias categoryEnabled: categoryEnabled.checked
    property alias categoryType: categoryType.loggingType
    property bool editMode: false
    property int editRowIndex: -1

    footer: QQC2.DialogButtonBox {
        standardButtons: saveButton | QQC2.DialogButtonBox.Cancel
        onAccepted: {
            editUserModal.saveUser();
        }
        QQC2.Button {
            id: saveButton
            icon.name: "document-save"
            enabled: categoryNameField.text !== ""
            text: i18nc("@label:button", "Save")
            QQC2.DialogButtonBox.buttonRole: QQC2.DialogButtonBox.AcceptRole
        }
    }

    RowLayout {
        id: mainColumn
        spacing: Kirigami.Units.smallSpacing

        QQC2.Label {
            Layout.leftMargin: 4
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            verticalAlignment: Text.AlignVCenter
            text: i18nc("@label:textbox", "Category:")
        }
        QQC2.TextField {
            id: categoryNameField
        }
        QQC2.Label {
            Layout.leftMargin: 4
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            verticalAlignment: Text.AlignVCenter
            text: i18nc("@label:textbox", "Type:")
        }
        CategoryComboBox {
            id: categoryType
            showOffTypeValue: false
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
        }
        QQC2.CheckBox {
            id: categoryEnabled
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            text: i18nc("@label:textbox", "Enabled")
        }
    }
    onAccepted: {
        if (editMode) {
            LoggingManager.customCategoryModel.updateCategory(editRowIndex, categoryNameField.text, categoryEnabled.checked, categoryType.currentValue);
        } else {
            LoggingManager.customCategoryModel.addCategory(categoryNameField.text, categoryEnabled.checked, categoryType.currentValue);
        }
    }
}
