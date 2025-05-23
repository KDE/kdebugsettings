/*
    SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "libkdebugsettingscore_export.h"
#include <QSortFilterProxyModel>

class LIBKDEBUGSETTINGSCORE_EXPORT KDEApplicationLoggingCategoryProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString filterText READ filterText WRITE setFilterText NOTIFY filterTextChanged FINAL)
public:
    explicit KDEApplicationLoggingCategoryProxyModel(QObject *parent = nullptr);
    ~KDEApplicationLoggingCategoryProxyModel() override;

    [[nodiscard]] QString filterText() const;
    void setFilterText(const QString &newFilterText);

protected:
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

Q_SIGNALS:
    void filterTextChanged();

private:
    QString mFilterText;
};
