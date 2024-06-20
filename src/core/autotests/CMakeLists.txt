# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_definitions(-DKDEBUGSETTINGS_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data" )
add_definitions(-DKDEBUGSETTINGS_BINARY_DATA_DIR="${CMAKE_CURRENT_BINARY_DIR}/data" )
macro(add_kdebugsettingscore_unittest _source)
    set(_test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name})
    ecm_mark_as_test(kdebugsettings-${_name})
    target_link_libraries(${_name}
        Qt::Test
        libkdebugsettingscore
        )
endmacro()

add_kdebugsettingscore_unittest(kdebugsettingutiltest.cpp)
add_kdebugsettingscore_unittest(loggingcategorytest.cpp)
add_kdebugsettingscore_unittest(loadcategoriesjobtest.cpp)
add_kdebugsettingscore_unittest(renamecategorytest.cpp)
add_kdebugsettingscore_unittest(saverulesjobtest.cpp)
add_kdebugsettingscore_unittest(changedebugmodejobtest.cpp)
add_kdebugsettingscore_unittest(categorytypemodeltest.cpp)

