// SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15 as QQC2
import org.kde.kirigami 2.15 as Kirigami
import org.kde.kirigamiaddons.labs.mobileform 0.1 as MobileForm
import QtQuick.Controls 1.4
import org.kde.kdebugsettings 1.0

Kirigami.Page {
    id: root
    title: i18nc("@title", "Rules Settings with Environment Variable")

    leftPadding: 20

    contextualActions: [
        aboutAction
    ]
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

