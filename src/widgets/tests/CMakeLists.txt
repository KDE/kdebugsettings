# SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(customdebuglistviewgui)
target_sources(customdebuglistviewgui PRIVATE
    customdebuglistviewgui.h customdebuglistviewgui.cpp)

target_link_libraries(customdebuglistviewgui
    libkdebugsettings
)

######
