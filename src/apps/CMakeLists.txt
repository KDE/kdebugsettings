# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(kdebugsettings main.cpp)
if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kdebugsettings PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kdebugsettings
    Qt::Widgets
    KF6::I18n
    libkdebugsettings
    KF6::IconThemes
    KF6::Crash
)

if(TARGET KF6::DBusAddons)
    target_link_libraries(kdebugsettings KF6::DBusAddons)
endif()

install(TARGETS kdebugsettings  ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} )
