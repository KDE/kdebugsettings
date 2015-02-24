set(kdebugsettings_SRCS 
   main.cpp 
   kdebugsettingsdialog.cpp
   customdebugsettingspage.cpp
   kdeapplicationdebugsettingpage.cpp
   )
   
add_executable(kdebugsettings ${kdebugsettings_SRCS})

target_link_libraries(kdebugsettings Qt5::Widgets KF5::I18n KF5::DBusAddons KF5::CoreAddons KF5::ConfigCore)

install(TARGETS kdebugsettings  ${INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( PROGRAMS org.kde.kdebugsettings.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )

