/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "loggingcategory.h"
#include <QAbstractListModel>

class CustomDebugModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum BannerInfosRoles {
        Description = Qt::UserRole + 1,
        CategoryName,
        IdentifierName,
    };

    explicit CustomDebugModel(QObject *parent = nullptr);
    ~CustomDebugModel() override;

    Q_REQUIRED_RESULT int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_REQUIRED_RESULT QVariant data(const QModelIndex &index, int role) const override;

    void setLoggingCategories(const LoggingCategory::List &list);

private:
    LoggingCategory::List mLoggingCategories;
};
