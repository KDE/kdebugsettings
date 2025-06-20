# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

# convenience macro to add qtest unit tests
macro(add_kdebugsettings_unittest _source)
    set(_test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name})
    ecm_mark_as_test(kdebugsettings-${_name})
    target_link_libraries(
        ${_name}
        Qt::Test
        KF6::I18n
        Qt::Widgets
        KF6::ConfigCore
        KF6::WidgetsAddons
        KF6::Completion
        libkdebugsettings
    )
endmacro()

add_kdebugsettings_unittest(kdebugsettingsdialogtest.cpp)
add_kdebugsettings_unittest(kdeapplicationdebugsettingpagetest.cpp)
add_kdebugsettings_unittest(customdebugsettingspagetest.cpp)
add_kdebugsettings_unittest(configurecustomsettingdialogtest.cpp)
add_kdebugsettings_unittest(configurecustomsettingwidgettest.cpp)
add_kdebugsettings_unittest(environmentsettingsrulespagetest.cpp)
add_kdebugsettings_unittest(categorytypecomboboxtest.cpp)

add_kdebugsettings_unittest(categorywarningtest.cpp)
add_kdebugsettings_unittest(loadgroupmenutest.cpp)
add_kdebugsettings_unittest(loadtoolbuttontest.cpp)
add_kdebugsettings_unittest(savetoolbuttontest.cpp)
add_kdebugsettings_unittest(groupmanagementdialogtest.cpp)
add_kdebugsettings_unittest(groupmanagementwidgettest.cpp)
add_kdebugsettings_unittest(customdebuglistviewtest.cpp)
add_kdebugsettings_unittest(kdeapplicationtreeviewtest.cpp)
