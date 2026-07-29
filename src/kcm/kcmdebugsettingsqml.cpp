/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kcmdebugsettingsqml.h"

K_PLUGIN_CLASS_WITH_JSON(KCMDebugSettingsQml, "kcm_debugsettings.json")

KCMDebugSettingsQml::KCMDebugSettingsQml(QObject *parent, const KPluginMetaData &metaData)
    : KQuickConfigModule(parent, metaData)
{
}

KCMDebugSettingsQml::~KCMDebugSettingsQml() = default;

#include "kcmdebugsettingsqml.moc"
