/*
    SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#pragma once

#include "libkdebugsettingscore_private_export.h"
#include <QObject>
#include <QString>
#include <QVector>
struct LIBKDEBUGSETTINGSCORE_EXPORT_TEST_EXPORT RenameCategory {
public:
    RenameCategory() = default;

    using List = QVector<RenameCategory>;
    Q_REQUIRED_RESULT bool operator==(const RenameCategory &other) const;
    Q_REQUIRED_RESULT bool isValid() const;

    QString originalName;
    QString newName;
};
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
Q_DECLARE_TYPEINFO(RenameCategory, Q_MOVABLE_TYPE);
#else
Q_DECLARE_TYPEINFO(RenameCategory, Q_RELOCATABLE_TYPE);
#endif
Q_DECLARE_METATYPE(RenameCategory)
