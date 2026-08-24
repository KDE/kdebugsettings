# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

file(GLOB icons "*-apps-kdebugsettings.png")
ecm_install_icons(
    ICONS ${icons}
    DESTINATION ${KDE_INSTALL_ICONDIR}
    THEME hicolor
)
