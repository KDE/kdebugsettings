// SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later
import QtQuick
import org.kde.kirigami as Kirigami
import QtQuick.Controls as Controls

Kirigami.Dialog {
    id: dialog
    title: i18n("Edit Custom Dialog")
    clip: true

    standardButtons: Controls.Dialog.Ok | Controls.Dialog.Cancel
}
