/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "libkdebugsettings_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT
#define LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT LIBKDEBUGSETTINGS_EXPORT
#endif
#else /* not compiling tests */
#define LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT
#endif
