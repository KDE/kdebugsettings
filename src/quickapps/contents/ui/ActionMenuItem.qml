// SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick
import Qt.labs.platform as Platform

Platform.MenuItem {
    required property var action

    checkable: action.checkable
    checked: action.checked
    icon.name: action.icon.name
    icon.source: action.icon.source
    shortcut: action.shortcut
    separator: action.separator
    text: action.text
    visible: action.visible
    onTriggered: action.triggered(this)
}
