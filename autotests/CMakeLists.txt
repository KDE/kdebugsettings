# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

include_directories(${kdebugsettings_BINARY_DIR}/src ${kdebugsettings_BINARY_DIR})
add_definitions( -DKDEBUGSETTINGS_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data" )
add_definitions( -DKDEBUGSETTINGS_BINARY_DATA_DIR="${CMAKE_CURRENT_BINARY_DIR}/data" )
# convenience macro to add qtest unit tests
macro(add_unittest _source)
    set(_test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test(NAME ${_name} COMMAND ${_name} )
    ecm_mark_as_test(kdebugsettings-${_name})
    target_link_libraries( ${_name}
        Qt::Test
        KF5::I18n
        Qt::Widgets
        KF5::ConfigCore
        KF5::WidgetsAddons
        KF5::ItemViews
        KF5::Completion
        libkdebugsettings
        )
endmacro ()

add_unittest( kdebugsettingsdialogtest.cpp)
add_unittest( kdeapplicationdebugsettingpagetest.cpp)
add_unittest( customdebugsettingspagetest.cpp)
add_unittest( configurecustomsettingdialogtest.cpp)
add_unittest( configurecustomsettingwidgettest.cpp)
add_unittest( environmentsettingsrulespagetest.cpp)
add_unittest( kdebugsettingutiltest.cpp)
add_unittest( categorytypecomboboxtest.cpp)
add_unittest( kdeapplicationtreelistwidgettest.cpp)
add_unittest( categorywarningtest.cpp)
add_unittest( loggingcategorytest.cpp)
add_unittest( loadcategoriesjobtest.cpp)
add_unittest( renamecategorytest.cpp)
add_unittest( saverulesjobtest.cpp)
add_unittest( kdebugsettingsloadingcategoriestest.cpp)
add_unittest( changedebugmodejobtest.cpp)
add_unittest( loadgroupmenutest.cpp)
add_unittest( loadtoolbuttontest.cpp)
add_unittest( savetoolbuttontest.cpp)
add_unittest( groupmanagementdialogtest.cpp)
add_unittest( groupmanagementwidgettest.cpp)
