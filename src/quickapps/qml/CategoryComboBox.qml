// SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick.Controls as QQC2
import org.kde.kdebugsettings

QQC2.ComboBox {
    id: categoryType

    property int loggingType: -1

    onLoggingTypeChanged: {
        currentIndex = count > 0 ? indexOfValue(loggingType) : -1
    }

    onCurrentIndexChanged: {
        if (currentIndex >= 0 && currentValue !== undefined) {
            loggingType = currentValue
        }
    }

    model: CategoryTypeProxyModel {
        sourceModel: LoggingManager.categoryTypeModel
        showOffType: true
    }
    textRole: "display"
    valueRole: "categoryType"
}