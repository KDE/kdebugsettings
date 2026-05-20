# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_test(
    NAME kdebugsettings-self-test
    COMMAND
        kdebugsettings --self-test
)
