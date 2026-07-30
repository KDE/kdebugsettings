/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kcmdebugsettingsqml.h"
#include "kcm_debugsettings_debug.h"
#include "loggingmanager.h"
#include "model/categorytypeproxymodel.h"
#include "model/customloggingcategorymodel.h"
#include "model/customloggingcategoryproxymodel.h"
#include "model/kdeapplicationloggingcategorymodel.h"
#include "model/kdeapplicationloggingcategoryproxymodel.h"
#include <qqml.h>
K_PLUGIN_CLASS_WITH_JSON(KCMDebugSettingsQml, "kcm_debugsettings.json")

KCMDebugSettingsQml::KCMDebugSettingsQml(QObject *parent, const KPluginMetaData &metaData)
    : KQuickConfigModule(parent, metaData)
{
    qmlRegisterSingletonInstance("org.kde.kdebugsettings", 1, 0, "LoggingManager", &LoggingManager::self());
    qRegisterMetaType<CustomLoggingCategoryModel *>("CustomLoggingCategoryModel *");
    qRegisterMetaType<KDEApplicationLoggingCategoryModel *>("KDEApplicationLoggingCategoryModel *");
    qmlRegisterType<CategoryTypeProxyModel>("org.kde.kdebugsettings", 1, 0, "CategoryTypeProxyModel");
    qmlRegisterType<CustomLoggingCategoryProxyModel>("org.kde.kdebugsettings", 1, 0, "CustomLoggingCategoryProxyModel");
    qmlRegisterType<KDEApplicationLoggingCategoryProxyModel>("org.kde.kdebugsettings", 1, 0, "KDEApplicationLoggingCategoryProxyModel");

    connect(&LoggingManager::self(), &LoggingManager::customLoggingChanged, this, [this]() {
        setNeedsSave(true);
    });
}

KCMDebugSettingsQml::~KCMDebugSettingsQml() = default;

void KCMDebugSettingsQml::load()
{
    // Nothing, it loads from LoggingManager
}

void KCMDebugSettingsQml::save()
{
    if (!LoggingManager::self().saveInQtLogging()) {
        qCWarning(KDEBUGSETTINGS_KCM_LOG) << "Impossible to save file";
    }
}

#include "kcmdebugsettingsqml.moc"
