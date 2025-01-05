# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
# KDE Application Version, managed by release script
cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)
set(RELEASE_SERVICE_VERSION_MAJOR "25")
set(RELEASE_SERVICE_VERSION_MINOR "03")
set(RELEASE_SERVICE_VERSION_MICRO "70")
set(RELEASE_SERVICE_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO}")
project(kdebugsettings VERSION ${RELEASE_SERVICE_VERSION})

set(QT_REQUIRED_VERSION "6.8.0")
set(KF_MIN_VERSION "6.8.0")

set(ECM_VERSION ${KF_MIN_VERSION})
find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})
include(FeatureSummary)
include(KDEGitCommitHooks)
include(KDEClangFormat)
file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h *.c)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
include(ECMAddAppIcon)
include(ECMInstallIcons)
include(KDEInstallDirs)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(ECMAddTests)
include(ECMQtDeclareLoggingCategory)
include(GenerateExportHeader)
include(ECMDeprecationSettings)
include(ECMCheckOutboundLicense)

find_package(Qt6 ${QT_REQUIRED_VERSION} REQUIRED NO_MODULE COMPONENTS Widgets)
find_package(KF6 ${KF_MIN_VERSION} REQUIRED COMPONENTS
    CoreAddons 
    Config
    I18n 
    WidgetsAddons
    Completion
    XmlGui
    IconThemes
    Crash
)

# shall we use DBus?
# enabled per default on Linux & BSD systems
set(USE_DBUS_DEFAULT OFF)
if(UNIX AND NOT APPLE AND NOT HAIKU)
    set(USE_DBUS_DEFAULT ON)
endif()


option(USE_DBUS "Build components using DBus" ${USE_DBUS_DEFAULT})
if(USE_DBUS)
   set(WITH_DBUS TRUE)
   find_package(KF6DBusAddons ${KF_MIN_VERSION} CONFIG REQUIRED)
else()
   find_package(KDSingleApplication-qt6 CONFIG REQUIRED)
endif()

add_definitions(-DTRANSLATION_DOMAIN="kdebugsettings")
add_definitions(-DQT_NO_CONTEXTLESS_CONNECT)
ecm_set_disabled_deprecation_versions(QT 6.8.1
    KF 6.9.0
)

if(OPTION_SELENIUMWEBDRIVER_SUPPORT)
    find_package(SeleniumWebDriverATSPI)
    set_package_properties(SeleniumWebDriverATSPI PROPERTIES PURPOSE "Needed for GUI tests" URL "https://invent.kde.org/sdk/selenium-webdriver-at-spi" TYPE OPTIONAL)
endif()
configure_file(config-kdebugsettings.h.in ${CMAKE_CURRENT_BINARY_DIR}/config-kdebugsettings.h)

set(KDEBUGSETTINGS_LIB_VERSION "${RELEASE_SERVICE_VERSION}")
set(KDEBUGSETTINGS_LIB_SOVERSION "6")

option(BUILD_QUICK_VERSION "Experimental (in progress)" FALSE)
if(BUILD_QUICK_VERSION)
    find_package(Qt6 ${QT_MIN_VERSION} REQUIRED NO_MODULE COMPONENTS Quick QuickControls2)
    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        add_definitions(-DQT_QML_DEBUG)
    endif()
endif()
if(BUILD_TESTING)
    add_definitions(-DBUILD_TESTING)
endif()

option(USE_UNITY_CMAKE_SUPPORT "Use UNITY cmake support (speedup compile time)" OFF)

set(COMPILE_WITH_UNITY_CMAKE_SUPPORT OFF)
if(USE_UNITY_CMAKE_SUPPORT)
    set(COMPILE_WITH_UNITY_CMAKE_SUPPORT ON)
endif()
if(BUILD_TESTING)
    find_package(Qt6 ${QT_MIN_VERSION} REQUIRED NO_MODULE COMPONENTS Test)
endif()

add_subdirectory( src )

ecm_qt_install_logging_categories(EXPORT KDEBUGSETTINGS FILE kdebugsettings.categories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR})
add_subdirectory(data/groups)

install(FILES data/kde.renamecategories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR} )
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
ki18n_install(po)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)


file(GLOB_RECURSE ALL_SOURCE_FILES src/quickapps/*.cpp src/quickapps/*.h src/core/*.cpp src/core/*.h src/apps/*.h src/apps/*.cpp src/widgets/*.cpp src/widgets/*.h)
ecm_check_outbound_license(LICENSES GPL-2.0-only  FILES ${ALL_SOURCE_FILES})

