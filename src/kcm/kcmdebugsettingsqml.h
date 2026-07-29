/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <KQuickConfigModule>

class KCMDebugSettingsQml : public KQuickConfigModule
{
    Q_OBJECT
public:
    explicit KCMDebugSettingsQml(QObject *parent, const KPluginMetaData &metaData);
    ~KCMDebugSettingsQml() override;

    void load() override;
    void save() override;
};
