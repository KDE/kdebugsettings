/*
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/
#ifndef RENAMECATEGORY_H
#define RENAMECATEGORY_H

#include <QVector>
#include <QString>
#include <QObject>
#include "libkdebugsettings_private_export.h"
struct LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT RenameCategory
{
public:
    RenameCategory()
    {
    }

    using List = QVector<RenameCategory>;
    Q_REQUIRED_RESULT bool operator ==(const RenameCategory &other) const;
    Q_REQUIRED_RESULT bool isValid() const;

    QString originalName;
    QString newName;
};
Q_DECLARE_TYPEINFO(RenameCategory, Q_MOVABLE_TYPE);
Q_DECLARE_METATYPE(RenameCategory)

#endif // RENAMECATEGORY_H
