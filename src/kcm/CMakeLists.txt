# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcmutils_add_qml_kcm(kcm_debugsettings)

ecm_qt_declare_logging_category(kcm_debugsettings HEADER kcm_debugsettings_debug.h IDENTIFIER KDEBUGSETTINGS_KCM_LOG
    CATEGORY_NAME log_kdebugsettings_kcm DESCRIPTION "kdebugsettings kcm" EXPORT KDEBUGSETTINGS
)

target_sources(
    kcm_debugsettings
    PRIVATE
        kcmdebugsettingsqml.h
        kcmdebugsettingsqml.cpp
)

target_link_libraries(
    kcm_debugsettings
    PRIVATE
        Qt::Gui
        Qt::Quick
        Qt::Qml
        KF6::I18n
        KF6::KCMUtilsQuick
        libkdebugsettingscore
)
