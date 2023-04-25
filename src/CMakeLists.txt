# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
include_directories(${CMAKE_BINARY_DIR})

add_library(libkdebugsettings SHARED)

ecm_qt_declare_logging_category(libkdebugsettings HEADER kdebugsettings_debug.h IDENTIFIER KDEBUGSETTINGS_LOG CATEGORY_NAME log_kdebugsettings DESCRIPTION "kdebugsettings" EXPORT KDEBUGSETTINGS)
target_sources(libkdebugsettings PRIVATE
    customdebugsettingspage.cpp
    customdebugsettingspage.h
    environmentplaintextedit.h
    kdeapplicationdebugsettingpage.h
    kdebugsettingsdialog.h
    loggingcategory.h
    loadgroupmenu.h
    groupmanagementwidget.cpp
    groupmanagementwidget.h
    changedebugmodejob.cpp
    changedebugmodejob.h
    kdebugsettingsdialog.cpp
    loadgroupmenu.cpp
    kdebugsettingsutil.cpp
    kdebugsettingsutil.h
    kdeapplicationtreelistwidget.h
    saverulesjob.h
    kdeloggingcategory.h
    configurecustomsettingwidget.h
    savetoolbutton.cpp
    configurecustomsettingdialog.h
    environmentplaintextedit.cpp
    groupmanagementdialog.h
    environmentsettingsrulespage.h
    saverulesjob.cpp
    renamecategory.h
    groupmanagementdialog.cpp
    categorywarning.h
    loadcategoriesjob.cpp
    libkdebugsettings_private_export.h
    loadtoolbutton.h
    kdeloggingcategory.cpp
    loadtoolbutton.cpp
    environmentsettingsrulespage.cpp
    loggingcategory.cpp
    categorywarning.cpp
    kdebugsettingsloadingcategories.cpp
    loadcategoriesjob.h
    categorytypecombobox.cpp
    configurecustomsettingwidget.cpp
    kdebugsettingsloadingcategories.h
    configurecustomsettingdialog.cpp
    renamecategory.cpp
    categorytypecombobox.h
    kdeapplicationtreelistwidget.cpp
    kdeapplicationdebugsettingpage.cpp
    savetoolbutton.h
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(libkdebugsettings PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(libkdebugsettings BASE_NAME libkdebugsettings)
target_link_libraries(libkdebugsettings
    Qt::Core
    KF${KF_MAJOR_VERSION}::I18n
    Qt::Widgets
    KF${KF_MAJOR_VERSION}::WidgetsAddons
    KF${KF_MAJOR_VERSION}::ItemViews
    KF${KF_MAJOR_VERSION}::ConfigCore
    KF${KF_MAJOR_VERSION}::Completion
    KF${KF_MAJOR_VERSION}::ConfigGui
    KF${KF_MAJOR_VERSION}::XmlGui
    KF${KF_MAJOR_VERSION}::CoreAddons
)

set_target_properties(libkdebugsettings
    PROPERTIES OUTPUT_NAME kdebugsettings VERSION ${KDEBUGSETTINGS_LIB_VERSION} SOVERSION ${KDEBUGSETTINGS_LIB_SOVERSION}
    )

install(TARGETS libkdebugsettings ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)


add_executable(kdebugsettings main.cpp)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kdebugsettings PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kdebugsettings Qt::Widgets KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::DBusAddons KF${KF_MAJOR_VERSION}::CoreAddons libkdebugsettings)

install(TARGETS kdebugsettings  ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( PROGRAMS org.kde.kdebugsettings.desktop  DESTINATION  ${KDE_INSTALL_APPDIR} )
install( FILES org.kde.kdebugsettings.appdata.xml DESTINATION  ${KDE_INSTALL_METAINFODIR})
