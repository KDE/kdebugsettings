// SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15 as QQC2
import org.kde.kirigami 2.15 as Kirigami
import org.kde.kirigamiaddons.labs.mobileform 0.1 as MobileForm

import org.kde.kdebugsettings 1.0

Kirigami.ScrollablePage {
    id: page
    title: i18nc("@title", "KDE Application Rules")

    leftPadding: 20

//    contextualActions: [
//        aboutAction,
//    ]
    ListView {
        id: listviewRules
        focus: true // keyboard navigation
        activeFocusOnTab: true // keyboard navigation
        clip: true
        model: LoggingManager.qtKdeCategoryModel
        delegate: Kirigami.BasicListItem {
            RowLayout {
                QQC2.Label {
                    Layout.fillHeight: true
                    Layout.leftMargin: 4
                    text: model.description
                }
                QQC2.ComboBox {
                    model: LoggingManager.categoryTypeModel
                    textRole: "display"
                }
            }
        }
    }
}

