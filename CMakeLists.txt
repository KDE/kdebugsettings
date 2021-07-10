# KDE Application Version, managed by release script
set (RELEASE_SERVICE_VERSION_MAJOR "21")
set (RELEASE_SERVICE_VERSION_MINOR "07")
set (RELEASE_SERVICE_VERSION_MICRO "80")
set (RELEASE_SERVICE_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO}")
cmake_minimum_required (VERSION 3.16.0 FATAL_ERROR)
project(kdebugsettings VERSION ${RELEASE_SERVICE_VERSION})

set(QT_MIN_VERSION "5.15.0")
set(KF5_MIN_VERSION "5.83.0")

set(ECM_VERSION ${KF5_MIN_VERSION})

find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})


find_package(Qt5 ${QT_MIN_VERSION} REQUIRED NO_MODULE COMPONENTS Widgets)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS 
    CoreAddons 
    Config
    DBusAddons 
    I18n 
    WidgetsAddons
    ItemViews
    Completion)
include(FeatureSummary)
include(KDEGitCommitHooks)
include(ECMAddAppIcon)
include(ECMInstallIcons)
include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(ECMAddTests)
include(ECMQtDeclareLoggingCategory)
include(GenerateExportHeader)


add_definitions(-DTRANSLATION_DOMAIN="kdebugsettings")
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x050f00)
add_definitions(-DKF_DISABLE_DEPRECATED_BEFORE_AND_AT=0x055400)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


configure_file(config-kdebugsettings.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-kdebugsettings.h)

set(KDEBUGSETTINGS_LIB_VERSION "${RELEASE_SERVICE_VERSION}")
set(KDEBUGSETTINGS_LIB_SOVERSION "5")

if(BUILD_TESTING)
    add_definitions(-DBUILD_TESTING)
endif(BUILD_TESTING)

option(USE_UNITY_CMAKE_SUPPORT "Use UNITY cmake support (speedup compile time)" OFF)

set(COMPILE_WITH_UNITY_CMAKE_SUPPORT OFF)
if (USE_UNITY_CMAKE_SUPPORT)
    set(COMPILE_WITH_UNITY_CMAKE_SUPPORT ON)
endif()

add_subdirectory( src )
if (BUILD_TESTING)
    find_package(Qt5 ${QT_MIN_VERSION} REQUIRED NO_MODULE COMPONENTS Test)
    add_subdirectory( autotests )
endif()
ecm_qt_install_logging_categories(EXPORT KDEBUGSETTINGS FILE kdebugsettings.categories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR})
add_subdirectory(data/groups)

install( FILES data/kde.renamecategories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR} )
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
ki18n_install(po)
feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
