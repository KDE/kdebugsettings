/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "libkdebugsettingscore_export.h"
#include "loggingcategory.h"
#include <QAbstractListModel>

class LIBKDEBUGSETTINGSCORE_EXPORT CustomDebugModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum BannerInfosRoles {
        Description = Qt::UserRole + 1,
        CategoryName,
        IdentifierName,
        DefaultCategory,
        DisplayRule,
        LoggingType,
    };

    explicit CustomDebugModel(QObject *parent = nullptr);
    ~CustomDebugModel() override;

    Q_REQUIRED_RESULT int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_REQUIRED_RESULT QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setLoggingCategories(const LoggingCategory::List &list);

    void clear();

private:
    LoggingCategory::List mLoggingCategories;
};
