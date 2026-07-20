// SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as QQC2
import org.kde.kirigami as Kirigami
import org.kde.kdebugsettings

Kirigami.Page {
    id: root
    title: i18nc("@title", "Rules Settings with Environment Variable")

    leftPadding: 20

    ColumnLayout {
        spacing: Kirigami.Units.gridUnit
        width: parent.width - (Kirigami.Units.largeSpacing * 4)
        anchors.centerIn: parent
        TextEdit {
            text: LoggingManager.environmentrules().length === 0 ? i18n("No rules have been defined in the environment variable \"QT_LOGGING_RULES\".") : LoggingManager.environmentrules()
            readOnly: true;
            horizontalAlignment: Qt.AlignHCenter
        }
    }
}
