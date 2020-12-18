
include_directories(${kdebugsettings_BINARY_DIR}/src ${kdebugsettings_BINARY_DIR})
add_definitions( -DKDEBUGSETTINGS_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data" )
add_definitions( -DKDEBUGSETTINGS_BINARY_DATA_DIR="${CMAKE_CURRENT_BINARY_DIR}/data" )
# convenience macro to add qtest unit tests
macro(add_unittest _source _additionalsource)
    set(_test ${_source} ${_additionalsource})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test(NAME ${_name} COMMAND ${_name} )
    ecm_mark_as_test(kdebugsettings-${_name})
    target_link_libraries( ${_name}
        Qt5::Test
        KF5::I18n
        Qt5::Widgets
        KF5::ConfigCore
        KF5::WidgetsAddons
        KF5::ItemViews
        KF5::Completion
        libkdebugsettings
        )
endmacro ()

add_unittest( kdebugsettingsdialogtest.cpp "")
add_unittest( kdeapplicationdebugsettingpagetest.cpp "")
add_unittest( customdebugsettingspagetest.cpp "")
add_unittest( configurecustomsettingdialogtest.cpp "")
add_unittest( configurecustomsettingwidgettest.cpp "")
add_unittest( environmentsettingsrulespagetest.cpp "")
add_unittest( kdebugsettingutiltest.cpp "")
add_unittest( categorytypecomboboxtest.cpp "")
add_unittest( kdeapplicationtreelistwidgettest.cpp "")
add_unittest( categorywarningtest.cpp "")
add_unittest( loggingcategorytest.cpp "")
add_unittest( loadcategoriesjobtest.cpp "")
add_unittest( renamecategorytest.cpp "")
add_unittest( saverulesjobtest.cpp "")
add_unittest( kdebugsettingsloadingcategoriestest.cpp "")
add_unittest( changedebugmodejobtest.cpp "")
add_unittest( loadgroupmenutest.cpp "")
add_unittest( loadtoolbuttontest.cpp "")
add_unittest( savetoolbuttontest.cpp "")
