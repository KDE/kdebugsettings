/*
  Copyright (c) 2019 Montel Laurent <montel@kde.org>

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

#include "changedebugmodejob.h"
#include "kdebugsettingsloadingcategories.h"

ChangeDebugModeJob::ChangeDebugModeJob()
{
}

ChangeDebugModeJob::~ChangeDebugModeJob()
{
}

bool ChangeDebugModeJob::canStart() const
{
    if (mDebugMode.isEmpty()) {
        return false;
    }
    //TODO add mLoggingCategoryName
    return true;
}

bool ChangeDebugModeJob::start()
{
    if (!canStart()) {
        return false;
    }
    return false;
}

void ChangeDebugModeJob::setDebugMode(const QString &mode)
{
    mDebugMode = mode;
}

QString ChangeDebugModeJob::debugMode() const
{
    return mDebugMode;
}

QStringList ChangeDebugModeJob::loggingCategoryName() const
{
    return mLoggingCategoryNames;
}

void ChangeDebugModeJob::setLoggingCategoryName(const QStringList &loggingCategoryName)
{
    mLoggingCategoryNames = loggingCategoryName;
}
