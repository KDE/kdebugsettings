// SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick 2.15
import Qt.labs.platform 1.1 as Platform
import org.kde.kirigami 2.19 as Kirigami

Platform.MenuBar {
    Platform.Menu {
        title: i18nc("@item:inmenu", "Help")

        ActionMenuItem { action: aboutAction }
    }
}
