set(kdebugsettings_SRCS 
   main.cpp 
   )
   
add_executable(kdebugsettings ${kdebugsettings_SRCS})

target_link_libraries(kdebugsettings Qt5::Widgets KF5::I18n)

install(TARGETS klines  ${INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

#install( PROGRAMS org.kde.klines.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )

