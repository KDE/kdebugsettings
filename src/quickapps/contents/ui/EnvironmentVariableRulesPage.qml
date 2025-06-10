// SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as QQC2
import org.kde.kirigami as Kirigami
import org.kde.kdebugsettings 1.0

Kirigami.Page {
    id: root
    title: i18nc("@title", "Rules Settings with Environment Variable")

    leftPadding: 20

    ColumnLayout {
        spacing: Kirigami.Units.gridUnit
        width: parent.width - (Kirigami.Units.largeSpacing * 4)
        anchors.centerIn: parent
        TextEdit {
            //placeholderText: i18n("No rules have been defined in the environment variable \"QT_LOGGING_RULES\".")
            text: LoggingManager.environmentrules().length === 0 ? i18n("No rules have been defined in the environment variable \"QT_LOGGING_RULES\".") : LoggingManager.environmentrules()
        }
    }
}
