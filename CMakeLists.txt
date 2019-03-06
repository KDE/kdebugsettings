# KDE Application Version, managed by release script
set (KDE_APPLICATIONS_VERSION_MAJOR "19")
set (KDE_APPLICATIONS_VERSION_MINOR "03")
set (KDE_APPLICATIONS_VERSION_MICRO "70")
set (KDE_APPLICATIONS_VERSION "${KDE_APPLICATIONS_VERSION_MAJOR}.${KDE_APPLICATIONS_VERSION_MINOR}.${KDE_APPLICATIONS_VERSION_MICRO}")
cmake_minimum_required (VERSION 3.0 FATAL_ERROR)
project(kdebugsettings VERSION ${KDE_APPLICATIONS_VERSION})

set(QT_MIN_VERSION "5.10.0")
set(KF5_MIN_VERSION "5.50.0")

set(ECM_VERSION ${KF5_MIN_VERSION})

find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})


find_package(Qt5 ${QT_MIN_VERSION} REQUIRED NO_MODULE COMPONENTS Widgets Test)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS 
    CoreAddons 
    Config
    DBusAddons 
    I18n 
    WidgetsAddons
    ItemViews
    Completion)
    
include(FeatureSummary)
include(ECMAddAppIcon)
include(ECMInstallIcons)
include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(ECMAddTests)
include(ECMQtDeclareLoggingCategory)

add_definitions(-DTRANSLATION_DOMAIN="kdebugsettings")
add_definitions( -DQT_DISABLE_DEPRECATED_BEFORE=0x060000 )
add_definitions(-DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT)
add_definitions(-DQT_NO_FOREACH)



configure_file(config-kdebugsettings.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-kdebugsettings.h)

add_subdirectory( src )
if (BUILD_TESTING)
   add_subdirectory( autotests )
endif()
install( FILES data/kde.categories DESTINATION ${KDE_INSTALL_CONFDIR} )
install( FILES data/kde.renamecategories DESTINATION ${KDE_INSTALL_CONFDIR} )

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
