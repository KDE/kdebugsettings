# SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
include_directories(${CMAKE_BINARY_DIR})

add_library(libkdebugsettingscore SHARED)

ecm_qt_declare_logging_category(libkdebugsettingscore HEADER kdebugsettingscore_debug.h IDENTIFIER KDEBUGSETTINGSCORE_LOG CATEGORY_NAME log_kdebugsettingscore DESCRIPTION "kdebugsettings core" EXPORT KDEBUGSETTINGS)
target_sources(libkdebugsettingscore PRIVATE
    jobs/changedebugmodejob.cpp
    jobs/changedebugmodejob.h
    jobs/loadcategoriesjob.cpp
    jobs/loadcategoriesjob.h
    jobs/saverulesjob.cpp
    jobs/saverulesjob.h

    model/loggingcategorymodel.h
    model/loggingcategorymodel.cpp

    model/customdebugproxymodel.h
    model/customdebugproxymodel.cpp
    model/categorytypemodel.h
    model/categorytypemodel.cpp

    loggingcategory.cpp
    loggingcategory.h
    kdebugsettingsutil.cpp
    kdebugsettingsutil.h
    renamecategory.cpp
    renamecategory.h

    kdeloggingcategory.cpp
    kdeloggingcategory.h
    kdebugsettingsloadingcategories.cpp
    kdebugsettingsloadingcategories.h

    libkdebugsettingscore_private_export.h


    loggingmanager.h loggingmanager.cpp
)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(libkdebugsettingscore PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(libkdebugsettingscore BASE_NAME libkdebugsettingscore)
target_link_libraries(libkdebugsettingscore
    Qt::Core
    KF${KF_MAJOR_VERSION}::I18n
)

set_target_properties(libkdebugsettingscore
    PROPERTIES OUTPUT_NAME kdebugsettingscore VERSION ${KDEBUGSETTINGS_LIB_VERSION} SOVERSION ${KDEBUGSETTINGS_LIB_SOVERSION}
    )

install(TARGETS libkdebugsettingscore ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

if (BUILD_TESTING)
    add_subdirectory( autotests )
endif()

