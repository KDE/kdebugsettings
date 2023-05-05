/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "libkdebugsettingscore_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef LIBKDEBUGSETTINGSCORE_EXPORT_TEST_EXPORT
#define LIBKDEBUGSETTINGSCORE_EXPORT_TEST_EXPORT LIBKDEBUGSETTINGSCORE_EXPORT
#endif
#else /* not compiling tests */
#define LIBKDEBUGSETTINGSCORE_EXPORT_TEST_EXPORT
#endif
