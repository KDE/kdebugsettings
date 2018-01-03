/*
  Copyright (c) 2016-2018 Montel Laurent <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

*/
#ifndef RENAMECATEGORY_H
#define RENAMECATEGORY_H

#include <QVector>
#include <QString>
#include <QObject>

struct RenameCategory
{
public:
    RenameCategory() {

    }

    typedef QVector<RenameCategory> List;
    bool operator ==(const RenameCategory &other) const;
    bool isValid() const;

    QString originalName;
    QString newName;
};
Q_DECLARE_TYPEINFO(RenameCategory, Q_MOVABLE_TYPE);
Q_DECLARE_METATYPE(RenameCategory)

#endif // RENAMECATEGORY_H
