
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
  )
endmacro ()

add_unittest( kdebugsettingsdialogtest.cpp "../src/kdebugsettingsdialog.cpp")
add_unittest( kdeapplicationdebugsettingpagetest.cpp "../src/kdeapplicationdebugsettingpage.cpp")
add_unittest( customdebugsettingspagetest.cpp "../src/customdebugsettingspage.cpp")
add_unittest( kdeapplicationlistwidgettest.cpp "../src/kdeapplicationlistwidget.cpp")
