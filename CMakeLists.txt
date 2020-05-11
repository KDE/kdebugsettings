# KDE Application Version, managed by release script
set (RELEASE_SERVICE_VERSION_MAJOR "20")
set (RELEASE_SERVICE_VERSION_MINOR "04")
set (RELEASE_SERVICE_VERSION_MICRO "1")
set (RELEASE_SERVICE_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO}")
cmake_minimum_required (VERSION 3.5 FATAL_ERROR)
project(kdebugsettings VERSION ${RELEASE_SERVICE_VERSION})

set(QT_MIN_VERSION "5.12.0")
set(KF5_MIN_VERSION "5.66.0")

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
include(GenerateExportHeader)


add_definitions(-DTRANSLATION_DOMAIN="kdebugsettings")
add_definitions(-DQT_NO_FOREACH)


configure_file(config-kdebugsettings.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-kdebugsettings.h)

set(KDEBUGSETTINGS_LIB_VERSION "${RELEASE_SERVICE_VERSION}")
set(KDEBUGSETTINGS_LIB_SOVERSION "5")

if(BUILD_TESTING)
	add_definitions(-DBUILD_TESTING)
endif(BUILD_TESTING)


add_subdirectory( src )
if (BUILD_TESTING)
	add_subdirectory( autotests )
endif()
if (NOT ECM_VERSION VERSION_LESS "5.68.0")
   ecm_qt_install_logging_categories(EXPORT KDEBUGSETTINGS FILE kdebugsettings.categories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR})
else()
   install( FILES data/kdebugsettings.categories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR} )
endif()

install( FILES data/kde.categories data/kde.renamecategories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR} )
feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
