# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(kdebugsettings main.cpp)
if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kdebugsettings PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(
    kdebugsettings
    Qt::Widgets
    KF6::I18n
    libkdebugsettings
    KF6::IconThemes
    KF6::Crash
)

if(TARGET KF6::DBusAddons)
    target_link_libraries(kdebugsettings KF6::DBusAddons KF6::WindowSystem)
else()
    target_link_libraries(kdebugsettings KDAB::kdsingleapplication)
endif()

if(APPLE)
    set_target_properties(
        kdebugsettings
        PROPERTIES
            MACOSX_BUNDLE_DISPLAY_NAME "KDebugsettings"
            MACOSX_BUNDLE_BUNDLE_NAME "KDebugsettings"
            MACOSX_BUNDLE_LONG_VERSION_STRING
                "KDebugsettings ${RELEASE_SERVICE_VERSION}"
            MACOSX_BUNDLE_SHORT_VERSION_STRING
                "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}"
            MACOSX_BUNDLE_BUNDLE_VERSION "${RELEASE_SERVICE_VERSION}"
            MACOSX_BUNDLE_GUI_IDENTIFIER "org.kde.kdebugsettings"
            MACOSX_BUNDLE_COPYRIGHT "2020-2024 The KDebugsettings Developers"
    )
endif()

install(TARGETS kdebugsettings ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
