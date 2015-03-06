
set(full_source_file
   ../src/kdebugsettingsdialog.cpp
   ../src/kdeapplicationlistwidget.cpp
   ../src/customdebugsettingspage.cpp
   ../src/kdeapplicationdebugsettingpage.cpp
   ../src/kdebugsettingsutil.cpp
   ../src/configurecustomsettingdialog.cpp
   ../src/configurecustomsettingwidget.cpp
   ../src/environmentsettingsrulespage.cpp
)

# convenience macro to add qtest unit tests
macro(add_unittest _source _additionalsource)
  set(_test ${_source} ${_additionalsource})
  get_filename_component(_name ${_source} NAME_WE)
  add_executable( ${_name} ${_test} )
  add_test( ${_name} ${_name} )
  ecm_mark_as_test(kdebugsettings-${_name})
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
add_unittest( kdeapplicationdebugsettingpagetest.cpp "../src/kdeapplicationdebugsettingpage.cpp;../src/kdeapplicationlistwidget.cpp")
add_unittest( customdebugsettingspagetest.cpp "../src/customdebugsettingspage.cpp;../src/configurecustomsettingdialog.cpp;../src/configurecustomsettingwidget.cpp;../src/kdebugsettingsutil.cpp")
add_unittest( kdeapplicationlistwidgettest.cpp "../src/kdeapplicationlistwidget.cpp")
add_unittest( configurecustomsettingdialogtest.cpp "../src/configurecustomsettingdialog.cpp;../src/configurecustomsettingwidget.cpp;../src/kdebugsettingsutil.cpp")
add_unittest( configurecustomsettingwidgettest.cpp "../src/configurecustomsettingwidget.cpp;../src/kdebugsettingsutil.cpp")
add_unittest( kdebugsettingutiltest.cpp "../src/kdebugsettingsutil.cpp")
add_unittest( environmentsettingsrulespagetest.cpp "../src/environmentsettingsrulespage.cpp")
