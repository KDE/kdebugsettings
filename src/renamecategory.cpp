/*
    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "renamecategory.h"

bool RenameCategory::operator ==(const RenameCategory &other) const
{
    return (originalName == other.originalName) && (newName == other.newName);
}

bool RenameCategory::isValid() const
{
    return !originalName.isEmpty() && !newName.isEmpty();
}
