# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

include_directories(${kdebugsettings_BINARY_DIR}/src ${kdebugsettings_BINARY_DIR})
add_definitions( -DKDEBUGSETTINGS_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data" )
add_definitions( -DKDEBUGSETTINGS_BINARY_DATA_DIR="${CMAKE_CURRENT_BINARY_DIR}/data" )
# convenience macro to add qtest unit tests
macro(add_kdebugsettings_unittest _source)
    set(_test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name} )
    ecm_mark_as_test(kdebugsettings-${_name})
    target_link_libraries( ${_name}
        Qt::Test
        KF${KF_MAJOR_VERSION}::I18n
        Qt::Widgets
        KF${KF_MAJOR_VERSION}::ConfigCore
        KF${KF_MAJOR_VERSION}::WidgetsAddons
        KF${KF_MAJOR_VERSION}::ItemViews
        KF${KF_MAJOR_VERSION}::Completion
        libkdebugsettings
        )
endmacro ()

add_kdebugsettings_unittest( kdebugsettingsdialogtest.cpp)
add_kdebugsettings_unittest( kdeapplicationdebugsettingpagetest.cpp)
add_kdebugsettings_unittest( customdebugsettingspagetest.cpp)
add_kdebugsettings_unittest( configurecustomsettingdialogtest.cpp)
add_kdebugsettings_unittest( configurecustomsettingwidgettest.cpp)
add_kdebugsettings_unittest( environmentsettingsrulespagetest.cpp)
add_kdebugsettings_unittest( kdebugsettingutiltest.cpp)
add_kdebugsettings_unittest( categorytypecomboboxtest.cpp)
add_kdebugsettings_unittest( kdeapplicationtreelistwidgettest.cpp)
add_kdebugsettings_unittest( categorywarningtest.cpp)
add_kdebugsettings_unittest( loggingcategorytest.cpp)
add_kdebugsettings_unittest( loadcategoriesjobtest.cpp)
add_kdebugsettings_unittest( renamecategorytest.cpp)
add_kdebugsettings_unittest( saverulesjobtest.cpp)
add_kdebugsettings_unittest( kdebugsettingsloadingcategoriestest.cpp)
add_kdebugsettings_unittest( changedebugmodejobtest.cpp)
add_kdebugsettings_unittest( loadgroupmenutest.cpp)
add_kdebugsettings_unittest( loadtoolbuttontest.cpp)
add_kdebugsettings_unittest( savetoolbuttontest.cpp)
add_kdebugsettings_unittest( groupmanagementdialogtest.cpp)
add_kdebugsettings_unittest( groupmanagementwidgettest.cpp)
