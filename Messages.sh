#! /usr/bin/env bash
# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-FileCopyrightText: 2023 Luigi Toscano <luigi.toscano@tiscali.it>
# SPDX-License-Identifier: BSD-3-Clause
$XGETTEXT `find src/ -name '*.cpp' | grep -v '/tests/' | grep -v '/autotests/'` -o $podir/kdebugsettings.pot
