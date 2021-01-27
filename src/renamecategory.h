/*
    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#ifndef RENAMECATEGORY_H
#define RENAMECATEGORY_H

#include "libkdebugsettings_private_export.h"
#include <QObject>
#include <QString>
#include <QVector>
struct LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT RenameCategory {
public:
    RenameCategory()
    {
    }

    using List = QVector<RenameCategory>;
    Q_REQUIRED_RESULT bool operator==(const RenameCategory &other) const;
    Q_REQUIRED_RESULT bool isValid() const;

    QString originalName;
    QString newName;
};
Q_DECLARE_TYPEINFO(RenameCategory, Q_MOVABLE_TYPE);
Q_DECLARE_METATYPE(RenameCategory)

#endif // RENAMECATEGORY_H
