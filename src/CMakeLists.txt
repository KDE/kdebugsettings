# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
include_directories(${CMAKE_BINARY_DIR})

add_library(libkdebugsettings SHARED)

ecm_qt_declare_logging_category(libkdebugsettings HEADER kdebugsettings_debug.h IDENTIFIER KDEBUGSETTINGS_LOG CATEGORY_NAME log_kdebugsettings DESCRIPTION "kdebugsettings" EXPORT KDEBUGSETTINGS)
target_sources(libkdebugsettings PRIVATE
    kdebugsettingsloadingcategories.cpp
    kdeloggingcategory.cpp
    renamecategory.cpp
    loggingcategory.cpp
    kdebugsettingsutil.cpp
    loadcategoriesjob.cpp
    saverulesjob.cpp
    categorytypecombobox.cpp
    environmentplaintextedit.cpp
    changedebugmodejob.cpp
    loadgroupmenu.cpp

    kdebugsettingsdialog.cpp
    customdebugsettingspage.cpp
    kdeapplicationdebugsettingpage.cpp

    configurecustomsettingdialog.cpp
    configurecustomsettingwidget.cpp
    environmentsettingsrulespage.cpp
    kdeapplicationtreelistwidget.cpp
    categorywarning.cpp
    loadtoolbutton.cpp
    savetoolbutton.cpp
    groupmanagementdialog.cpp
    groupmanagementwidget.cpp
    environmentplaintextedit.h
    renamecategory.h
    configurecustomsettingwidget.h
    kdeapplicationtreelistwidget.h
    saverulesjob.h
    kdeloggingcategory.h
    loadtoolbutton.h
    groupmanagementwidget.h
    loadgroupmenu.h
    environmentsettingsrulespage.h
    groupmanagementdialog.h
    categorytypecombobox.h
    libkdebugsettings_private_export.h
    loadcategoriesjob.h
    customdebugsettingspage.h
    loggingcategory.h
    categorywarning.h
    kdebugsettingsdialog.h
    kdeapplicationdebugsettingpage.h
    savetoolbutton.h
    kdebugsettingsloadingcategories.h
    changedebugmodejob.h
    kdebugsettingsutil.h
    configurecustomsettingdialog.h
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
