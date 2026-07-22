// SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick.Controls as QQC2
import org.kde.kdebugsettings

QQC2.ComboBox {
    id: categoryType
    model: CategoryTypeProxyModel {
        sourceModel: LoggingManager.categoryTypeModel
        showOffType: true
    }
    textRole: "display"
    valueRole: "categoryType"
}