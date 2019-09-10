
include_directories(${kdebugsettings_BINARY_DIR}/src ${kdebugsettings_BINARY_DIR})
add_definitions( -DKDEBUGSETTINGS_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data" )

set(full_source_file
    ../src/kdebugsettingsdialog.cpp
    ../src/customdebugsettingspage.cpp
    ../src/kdeapplicationdebugsettingpage.cpp
    ../src/configurecustomsettingdialog.cpp
    ../src/configurecustomsettingwidget.cpp
    ../src/environmentsettingsrulespage.cpp
    ../src/kdeapplicationtreelistwidget.cpp
    ../src/categorywarning.cpp
    ${CMAKE_BINARY_DIR}/src/kdebugsettings_debug.cpp
    )

# convenience macro to add qtest unit tests
macro(add_unittest _source _additionalsource)
    set(_test ${_source} ${_additionalsource} "../src/kdebugsettings_debug.cpp")
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test(NAME ${_name} COMMAND ${_name} )
    ecm_mark_as_test(kdebugsettings-${_name})
    set_tests_properties(${_name} PROPERTIES ENVIRONMENT "QT_HASH_SEED=1;QT_NO_CPU_FEATURE=sse4.2")
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

add_unittest( kdebugsettingsdialogtest.cpp "${full_source_file}")
add_unittest( kdeapplicationdebugsettingpagetest.cpp "../src/kdeapplicationdebugsettingpage.cpp;../src/kdeapplicationtreelistwidget.cpp")
add_unittest( customdebugsettingspagetest.cpp "../src/customdebugsettingspage.cpp;../src/configurecustomsettingdialog.cpp;../src/configurecustomsettingwidget.cpp")
add_unittest( configurecustomsettingdialogtest.cpp "../src/configurecustomsettingdialog.cpp;../src/configurecustomsettingwidget.cpp")
add_unittest( configurecustomsettingwidgettest.cpp "../src/configurecustomsettingwidget.cpp")
add_unittest( environmentsettingsrulespagetest.cpp "../src/environmentsettingsrulespage.cpp")
add_unittest( kdebugsettingutiltest.cpp "")
add_unittest( categorytypecomboboxtest.cpp "")
add_unittest( kdeapplicationtreelistwidgettest.cpp "../src/kdeapplicationtreelistwidget.cpp")
add_unittest( categorywarningtest.cpp "../src/categorywarning.cpp")
add_unittest( loggingcategorytest.cpp "")
add_unittest( loadcategoriesjobtest.cpp "")
add_unittest( renamecategorytest.cpp "")
add_unittest( saverulesjobtest.cpp "")
add_unittest( kdebugsettingsloadingcategoriestest.cpp "")
add_unittest( changedebugmodejobtest.cpp "")
