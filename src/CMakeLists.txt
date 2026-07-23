# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
include_directories(${CMAKE_BINARY_DIR})
add_subdirectory(core)
add_subdirectory(apps)
add_subdirectory(data)
add_subdirectory(widgets)
add_subdirectory(quickapps)

# Selenium GUI tests
if(SeleniumWebDriverATSPI_FOUND)
    add_subdirectory(seleniumtests)
endif()
