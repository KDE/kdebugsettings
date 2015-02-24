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

#include "kdebugsettingsutil.h"
#include <QDebug>
#include <QFile>


KDebugSettingsDialog::CategoriesMap KDebugSettingsUtil::readLoggingCategories(const QString &filename)
{
    KDebugSettingsDialog::CategoriesMap categories;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open" << filename;
    } else {
        QString data;
        QTextStream ts(&file);
        ts.setCodec( "ISO-8859-1" );
        while (!ts.atEnd()) {
            data = ts.readLine().simplified();

            int pos = data.indexOf(QLatin1Literal("#"));
            if ( pos != -1 ) {
                data.truncate( pos );
                data = data.simplified();
            }

            if (data.isEmpty())
                continue;

            const int space = data.indexOf(QLatin1Char(' '));
            if (space == -1)
                qCritical() << "No space:" << data << endl;

            const QString logName = data.left(space);

            const QString description = data.mid(space).simplified();
            categories.insert( logName, description );
        }
    }

    return categories;
}

QStringList KDebugSettingsUtil::readLoggingQtCategories(const QString &filename)
{
    //TODO
    return QStringList();
}
