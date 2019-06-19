/*
  Copyright (c) 2016-2019 Montel Laurent <montel@kde.org>

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

#ifndef KDELOGGINGCATEGORY_H
#define KDELOGGINGCATEGORY_H

#include <QVector>
#include <QString>
#include <QDebug>
struct KdeLoggingCategory {
    KdeLoggingCategory();
    typedef QVector<KdeLoggingCategory> List;
    Q_REQUIRED_RESULT bool operator ==(const KdeLoggingCategory &other) const;
    Q_REQUIRED_RESULT bool operator !=(const KdeLoggingCategory &other) const;
    Q_REQUIRED_RESULT bool isValid() const;

    QString description;
    QString categoryName;
    QString identifierName;
    QString defaultSeverity;
};
QDebug operator<<(QDebug debug, const KdeLoggingCategory &cat);
Q_DECLARE_TYPEINFO(KdeLoggingCategory, Q_MOVABLE_TYPE);
Q_DECLARE_METATYPE(KdeLoggingCategory)

#endif // KDELOGGINGCATEGORY_H
