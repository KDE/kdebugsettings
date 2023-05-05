# SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_executable(kdebugsettingsquick main.cpp)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kdebugsettingsquick PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kdebugsettingsquick
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::CoreAddons
    KF${KF_MAJOR_VERSION}::DBusAddons
    libkdebugsettingscore
    Qt::Quick
    Qt::QuickControls2
    Qt::Widgets

)

install(TARGETS kdebugsettingsquick ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} )

