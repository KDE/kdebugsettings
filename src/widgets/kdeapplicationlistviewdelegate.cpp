/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdeapplicationlistviewdelegate.h"
#include "categorytypecombobox.h"
#include "model/kdeapplicationloggingcategorymodel.h"
#include <QSpinBox>

KDEApplicationListViewDelegate::KDEApplicationListViewDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

KDEApplicationListViewDelegate::~KDEApplicationListViewDelegate() = default;

QWidget *KDEApplicationListViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem & /*option*/, const QModelIndex & /*index*/) const
{
    auto *comboBox = new CategoryTypeComboBox(false, parent);
    auto *that = const_cast<KDEApplicationListViewDelegate *>(this);
    connect(comboBox, &CategoryTypeComboBox::activated, this, [=]() {
        Q_EMIT that->commitData(mComboBox);
        Q_EMIT that->closeEditor(mComboBox);
    });
    const_cast<KDEApplicationListViewDelegate *>(this)->mComboBox = comboBox;
    return comboBox;
}

void KDEApplicationListViewDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto loggingIndex = index.model()->index(index.row(), KDEApplicationLoggingCategoryModel::LoggingTypeRole);
    qobject_cast<CategoryTypeComboBox *>(editor)->setType(loggingIndex.data().value<LoggingCategory::LoggingType>());
}

void KDEApplicationListViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto loggingIndex = index.model()->index(index.row(), KDEApplicationLoggingCategoryModel::LoggingTypeRole);
    model->setData(loggingIndex, qobject_cast<CategoryTypeComboBox *>(editor)->type());
}

void KDEApplicationListViewDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex & /*index*/) const
{
    editor->setGeometry(option.rect);
}
