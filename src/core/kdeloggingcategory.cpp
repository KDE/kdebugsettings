/*
    SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdeloggingcategory.h"

KdeLoggingCategory::KdeLoggingCategory() = default;

bool KdeLoggingCategory::operator==(const KdeLoggingCategory &other) const
{
    return (description == other.description) && (categoryName == other.categoryName) && (defaultSeverity == other.defaultSeverity)
        && (identifierName == other.identifierName);
}

bool KdeLoggingCategory::operator!=(const KdeLoggingCategory &other) const
{
    return !operator==(other);
}

bool KdeLoggingCategory::isValid() const
{
    return !categoryName.isEmpty();
}

QDebug operator<<(QDebug d, const KdeLoggingCategory &cat)
{
    d << "description: " << cat.description;
    d << "logname: " << cat.categoryName;
    d << "default category: " << cat.defaultSeverity;
    d << "identifier: " << cat.identifierName;
    return d;
}
