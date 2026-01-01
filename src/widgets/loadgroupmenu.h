/*
    SPDX-FileCopyrightText: 2020-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "libkdebugsettings_private_export.h"
#include <QMenu>
class LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT LoadGroupMenu : public QMenu
{
    Q_OBJECT
public:
    explicit LoadGroupMenu(QWidget *parent = nullptr);
    ~LoadGroupMenu() override;

    void refreshMenu();

    [[nodiscard]] static QString defaultWritableGroupPath();

    [[nodiscard]] QStringList groupNames() const;
    void setGroupNames(const QStringList &groupNames);

Q_SIGNALS:
    void loadGroupRequested(const QString &filePath);
    void manageGroupRequested();

private:
    LIBKDEBUGSETTINGS_NO_EXPORT void init();
    [[nodiscard]] LIBKDEBUGSETTINGS_NO_EXPORT QStringList defaultReadableGroupPath() const;
    QStringList mGroupNames;
};
