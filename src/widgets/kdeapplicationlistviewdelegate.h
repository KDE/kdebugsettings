/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QStyledItemDelegate>
class CategoryTypeComboBox;
class KDEApplicationListViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit KDEApplicationListViewDelegate(QObject *parent = nullptr);
    ~KDEApplicationListViewDelegate() override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const override;

private:
    CategoryTypeComboBox *mComboBox = nullptr;
};
