include_directories(${CMAKE_BINARY_DIR})

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
   categorywarning.cpp
   loggingcategory.cpp
   kdeloggingcategory.cpp
   loadcategoriesjob.cpp
   )

ecm_qt_declare_logging_category(kdebugsettings_SRCS HEADER kdebugsettings_debug.h IDENTIFIER KDEBUGSETTINGS_LOG CATEGORY_NAME log_kdebugsettings)
   
add_executable(kdebugsettings ${kdebugsettings_SRCS})

target_link_libraries(kdebugsettings Qt5::Widgets KF5::I18n KF5::DBusAddons KF5::CoreAddons KF5::ConfigCore KF5::WidgetsAddons KF5::ItemViews KF5::Completion)

install(TARGETS kdebugsettings  ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( PROGRAMS org.kde.kdebugsettings.desktop  DESTINATION  ${KDE_INSTALL_APPDIR} )

