// SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick.Controls as QQC2
import org.kde.kdebugsettings

QQC2.ComboBox {
    id: categoryType

    property int loggingType: -1
    property bool showOffTypeValue: true
    property bool syncLoggingTypeFromSelection: true

    onLoggingTypeChanged: {
        currentIndex = count > 0 ? indexOfValue(loggingType) : -1
    }

    onCountChanged: {
        // Resolve initial selection once the proxy model is populated.
        if (count > 0 && currentIndex < 0) {
            currentIndex = indexOfValue(loggingType)
        }
    }

    onActivated: {
        if (syncLoggingTypeFromSelection) {
            loggingType = currentValue
        }
    }

    model: CategoryTypeProxyModel {
        sourceModel: LoggingManager.categoryTypeModel
        showOffType: showOffTypeValue
    }
    textRole: "display"
    valueRole: "categoryType"
}