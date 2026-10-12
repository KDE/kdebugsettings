/*
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "renamecategory.h"

bool RenameCategory::isValid() const
{
    return !originalName.isEmpty() && !newName.isEmpty();
}
