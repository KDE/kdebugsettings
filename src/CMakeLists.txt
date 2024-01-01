# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
include_directories(${CMAKE_BINARY_DIR})
add_subdirectory(core)
add_subdirectory(apps)
add_subdirectory(data)
add_subdirectory(widgets)
if (BUILD_QUICK_VERSION)
    add_subdirectory(quickapps)
endif()

# Selenium GUI tests
if (SeleniumWebDriverATSPI_FOUND)
    add_subdirectory(seleniumtests)
endif()
