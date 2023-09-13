/*
    SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#pragma once

#include "libkdebugsettingscore_private_export.h"
#include <QList>
#include <QObject>
#include <QString>
struct LIBKDEBUGSETTINGSCORE_EXPORT_TEST_EXPORT RenameCategory {
public:
    RenameCategory() = default;

    using List = QList<RenameCategory>;
    Q_REQUIRED_RESULT bool operator==(const RenameCategory &other) const;
    Q_REQUIRED_RESULT bool isValid() const;

    QString originalName;
    QString newName;
};
Q_DECLARE_TYPEINFO(RenameCategory, Q_RELOCATABLE_TYPE);
Q_DECLARE_METATYPE(RenameCategory)
