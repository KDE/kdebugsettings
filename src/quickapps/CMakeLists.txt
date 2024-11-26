# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
# SPDX-License-Identifier: BSD-3-Clause

add_executable(kdebugsettingsquick)
target_sources(kdebugsettingsquick PRIVATE main.cpp resources.qrc)
if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kdebugsettingsquick PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kdebugsettingsquick
    KF6::I18n
    KF6::CoreAddons
    libkdebugsettingscore
    Qt::Quick
    Qt::QuickControls2
    Qt::Widgets
    KF6::IconThemes
    KF6::ConfigWidgets
)
if(TARGET KF6::DBusAddons)
    target_link_libraries(kdebugsettingsquick KF6::DBusAddons)
else()
    target_link_libraries(kdebugsettingsquick KDAB::kdsingleapplication)
endif()
target_link_libraries(kdebugsettingsquick KF6::I18nQml)

install(TARGETS kdebugsettingsquick ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

