# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
include_directories(${CMAKE_BINARY_DIR})

add_library(libkdebugsettings SHARED)

ecm_qt_declare_logging_category(libkdebugsettings HEADER kdebugsettings_debug.h IDENTIFIER KDEBUGSETTINGS_LOG CATEGORY_NAME log_kdebugsettings DESCRIPTION "kdebugsettings" EXPORT KDEBUGSETTINGS)

target_sources(libkdebugsettings PRIVATE
    categorytypecombobox.cpp
    categorytypecombobox.h
    categorywarning.cpp
    categorywarning.h
    configurecustomsettingdialog.cpp
    configurecustomsettingdialog.h
    configurecustomsettingwidget.cpp
    configurecustomsettingwidget.h
    customdebugsettingspage.cpp
    customdebugsettingspage.h
    environmentplaintextedit.cpp
    environmentplaintextedit.h
    environmentsettingsrulespage.cpp
    environmentsettingsrulespage.h
    groupmanagementdialog.cpp
    groupmanagementdialog.h
    groupmanagementwidget.cpp
    groupmanagementwidget.h
    kdeapplicationdebugsettingpage.cpp
    kdeapplicationdebugsettingpage.h
    kdeapplicationtreelistwidget.cpp
    kdeapplicationtreelistwidget.h
    kdebugsettingsdialog.cpp
    kdebugsettingsdialog.h
    libkdebugsettings_private_export.h
    loadgroupmenu.cpp
    loadgroupmenu.h
    loadtoolbutton.cpp
    loadtoolbutton.h
    savetoolbutton.cpp
    savetoolbutton.h

    customdebuglistview.h
    customdebuglistview.cpp
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(libkdebugsettings PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(libkdebugsettings BASE_NAME libkdebugsettings)
target_link_libraries(libkdebugsettings
    Qt::Core
    KF${KF_MAJOR_VERSION}::Completion
    KF${KF_MAJOR_VERSION}::ConfigCore
    KF${KF_MAJOR_VERSION}::CoreAddons
    KF${KF_MAJOR_VERSION}::I18n
    Qt::Widgets
    KF${KF_MAJOR_VERSION}::WidgetsAddons
    KF${KF_MAJOR_VERSION}::ItemViews
    KF${KF_MAJOR_VERSION}::ConfigGui
    KF${KF_MAJOR_VERSION}::XmlGui
    libkdebugsettingscore
)

set_target_properties(libkdebugsettings
    PROPERTIES OUTPUT_NAME kdebugsettings VERSION ${KDEBUGSETTINGS_LIB_VERSION} SOVERSION ${KDEBUGSETTINGS_LIB_SOVERSION}
    )

install(TARGETS libkdebugsettings ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

if (BUILD_TESTING)
    add_subdirectory( autotests )
    add_subdirectory( tests )
endif()

