set(kdebugsettings_SRCS 
   main.cpp 
   kdebugsettingsdialog.cpp
   customdebugsettingspage.cpp
   kdeapplicationdebugsettingpage.cpp
   kdebugsettingsutil.cpp
   configurecustomsettingdialog.cpp
   configurecustomsettingwidget.cpp
   environmentsettingsrulespage.cpp
   environmentplaintextedit.cpp
   categorytypecombobox.cpp
   kdeapplicationtreelistwidget.cpp
   )
   
add_executable(kdebugsettings ${kdebugsettings_SRCS})

target_link_libraries(kdebugsettings Qt5::Widgets KF5::I18n KF5::DBusAddons KF5::CoreAddons KF5::ConfigCore KF5::WidgetsAddons KF5::ItemViews KF5::Completion)

install(TARGETS kdebugsettings  ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( PROGRAMS org.kde.kdebugsettings.desktop  DESTINATION  ${KDE_INSTALL_APPDIR} )

