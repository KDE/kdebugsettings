
include_directories(${kdebugsettings_BINARY_DIR}/src)
add_definitions( -DKDEBUGSETTINGS_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data" )

set(full_source_file
    ../src/kdebugsettingsdialog.cpp
    ../src/customdebugsettingspage.cpp
    ../src/kdeapplicationdebugsettingpage.cpp
    ../src/kdebugsettingsutil.cpp
    ../src/configurecustomsettingdialog.cpp
    ../src/configurecustomsettingwidget.cpp
    ../src/environmentsettingsrulespage.cpp
    ../src/environmentplaintextedit.cpp
    ../src/categorytypecombobox.cpp
    ../src/kdeapplicationtreelistwidget.cpp
    ../src/categorywarning.cpp
    ../src/loggingcategory.cpp
    ../src/kdeloggingcategory.cpp
    ../src/loadcategoriesjob.cpp
    ../src/renamecategory.cpp
    ${CMAKE_BINARY_DIR}/src/kdebugsettings_debug.cpp
    )

# convenience macro to add qtest unit tests
macro(add_unittest _source _additionalsource)
    set(_test ${_source} ${_additionalsource})
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
        )
endmacro ()

add_unittest( kdebugsettingsdialogtest.cpp "${full_source_file}")
add_unittest( kdeapplicationdebugsettingpagetest.cpp "../src/kdeloggingcategory.cpp;../src/loggingcategory.cpp;../src/kdebugsettings_debug.cpp;../src/kdeapplicationdebugsettingpage.cpp;../src/kdeapplicationtreelistwidget.cpp;../src/categorytypecombobox.cpp")
add_unittest( customdebugsettingspagetest.cpp "../src/renamecategory.cpp;../src/kdeloggingcategory.cpp;../src/loggingcategory.cpp;../src/kdebugsettings_debug.cpp;../src/categorytypecombobox.cpp;../src/customdebugsettingspage.cpp;../src/configurecustomsettingdialog.cpp;../src/configurecustomsettingwidget.cpp;../src/kdebugsettingsutil.cpp")
add_unittest( configurecustomsettingdialogtest.cpp "../src/renamecategory.cpp;../src/kdeloggingcategory.cpp;../src/loggingcategory.cpp;../src/kdebugsettings_debug.cpp;../src/categorytypecombobox.cpp;../src/configurecustomsettingdialog.cpp;../src/configurecustomsettingwidget.cpp;../src/kdebugsettingsutil.cpp")
add_unittest( configurecustomsettingwidgettest.cpp "../src/renamecategory.cpp;../src/kdeloggingcategory.cpp;../src/loggingcategory.cpp;../src/kdebugsettings_debug.cpp;../src/categorytypecombobox.cpp;../src/configurecustomsettingwidget.cpp;../src/kdebugsettingsutil.cpp")
add_unittest( environmentsettingsrulespagetest.cpp "../src/renamecategory.cpp;../src/kdeloggingcategory.cpp;../src/loggingcategory.cpp;../src/environmentsettingsrulespage.cpp;../src/environmentplaintextedit.cpp")
add_unittest( kdebugsettingutiltest.cpp "../src/renamecategory.cpp;../src/kdeloggingcategory.cpp;../src/loggingcategory.cpp;../src/kdebugsettings_debug.cpp;../src/kdebugsettingsutil.cpp")
add_unittest( categorytypecomboboxtest.cpp "../src/loggingcategory.cpp;../src/categorytypecombobox.cpp")
add_unittest( kdeapplicationtreelistwidgettest.cpp "../src/renamecategory.cpp;../src/loggingcategory.cpp;../src/kdeapplicationtreelistwidget.cpp;../src/categorytypecombobox.cpp")
add_unittest( categorywarningtest.cpp "../src/categorywarning.cpp")
add_unittest( loggingcategorytest.cpp "../src/loggingcategory.cpp")
add_unittest( loadcategoriesjobtest.cpp "../src/renamecategory.cpp;../src/loadcategoriesjob.cpp;../src/loggingcategory.cpp;../src/kdeloggingcategory.cpp;../src/kdebugsettings_debug.cpp;../src/kdebugsettingsutil.cpp")
add_unittest( renamecategorytest.cpp "../src/renamecategory.cpp;../src/kdebugsettingsutil.cpp;../src/kdeloggingcategory.cpp;../src/kdebugsettings_debug.cpp")
