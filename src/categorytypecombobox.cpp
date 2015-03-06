/*
  Copyright (c) 2015 Montel Laurent <montel@kde.org>

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

#include "categorytypecombobox.h"
#include <KLocalizedString>

CategoryTypeComboBox::CategoryTypeComboBox(QWidget *parent)
    : QComboBox(parent)
{
    addItem(i18n("All"), QString());
    addItem(i18n("Debug"), QStringLiteral("debug"));
    addItem(i18n("Warning"), QStringLiteral("warning"));
    addItem(i18n("Critical"), QStringLiteral("critical"));
}

CategoryTypeComboBox::~CategoryTypeComboBox()
{

}

void CategoryTypeComboBox::setType(const QString &type)
{
    if (type.isEmpty()) {
        //All
        setCurrentIndex(0);
    } else {
        const int pos = findData(type);
        if (pos != -1) {
            setCurrentIndex(pos);
        } else {
            //Default;
            setCurrentIndex(0);
        }
    }
}

QString CategoryTypeComboBox::type() const
{
    return currentData().toString();
}
