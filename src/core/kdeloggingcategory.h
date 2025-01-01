/*
    SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "libkdebugsettingscore_private_export.h"
#include <QDebug>
#include <QList>
#include <QString>

struct LIBKDEBUGSETTINGSCORE_EXPORT_TEST_EXPORT KdeLoggingCategory {
    KdeLoggingCategory();
    using List = QList<KdeLoggingCategory>;
    [[nodiscard]] bool operator==(const KdeLoggingCategory &other) const;
    [[nodiscard]] bool operator!=(const KdeLoggingCategory &other) const;
    [[nodiscard]] bool isValid() const;

    QString description;
    QString categoryName;
    QString identifierName;
    QString defaultSeverity;
};
LIBKDEBUGSETTINGSCORE_EXPORT_TEST_EXPORT QDebug operator<<(QDebug debug, const KdeLoggingCategory &cat);
Q_DECLARE_TYPEINFO(KdeLoggingCategory, Q_RELOCATABLE_TYPE);
Q_DECLARE_METATYPE(KdeLoggingCategory)
