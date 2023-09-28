/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "libkdebugsettingscore_export.h"
#include <QSortFilterProxyModel>

class LIBKDEBUGSETTINGSCORE_EXPORT CategoryTypeProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(bool showOffType READ showOffType WRITE setShowOffType NOTIFY showOffTypeChanged FINAL)
public:
    explicit CategoryTypeProxyModel(QObject *parent = nullptr);
    ~CategoryTypeProxyModel() override;

    [[nodiscard]] bool showOffType() const;
    void setShowOffType(bool newShowOffType);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

Q_SIGNALS:
    void showOffTypeChanged();

private:
    bool mShowOffType = false;
};
