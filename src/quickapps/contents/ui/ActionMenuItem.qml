// SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick 2.15
import Qt.labs.platform 1.1 as Platform

Platform.MenuItem {
    required property var action

    checkable: action.checkable
    checked: action.checked
    icon.name: action.iconName
    icon.source: action.iconSource
    shortcut: action.shortcut
    separator: action.separator
    text: action.text
    visible: action.visible
    onTriggered: action.triggered(this)
}
