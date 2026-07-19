// SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later
import QtQuick
import org.kde.kirigami 2.19 as Kirigami
import QtQuick.Controls 2.12 as Controls

Kirigami.Dialog {
    id: dialog
    title: i18n("Edit Custom Dialog")
    clip: true

    standardButtons: Controls.Dialog.Ok | Controls.Dialog.Cancel
}
