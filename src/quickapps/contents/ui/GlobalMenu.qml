// SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick
import Qt.labs.platform as Platform
import org.kde.kirigami as Kirigami

Platform.MenuBar {
    Platform.Menu {
        title: i18nc("@item:inmenu", "Help")

        ActionMenuItem { action: aboutAction }
    }
}
