/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdeapplicationlistviewdelegate.h"
#include "categorytypecombobox.h"

KDEApplicationListViewDelegate::KDEApplicationListViewDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

KDEApplicationListViewDelegate::~KDEApplicationListViewDelegate() = default;

QWidget *KDEApplicationListViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem & /*option*/, const QModelIndex & /*index*/) const
{
    auto *comboBox = new CategoryTypeComboBox(parent);
    auto *that = const_cast<KDEApplicationListViewDelegate *>(this);
#if 0
    connect(comboBox, &CategoryTypeComboBox::customerActivated, this, [=]() {
        Q_EMIT that->commitData(mComboBox);
        Q_EMIT that->closeEditor(mComboBox);
    });
#endif
    const_cast<KDEApplicationListViewDelegate *>(this)->mComboBox = comboBox;
    return comboBox;
}

void KDEApplicationListViewDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    // qobject_cast<CategoryTypeComboBox *>(editor)->setCurrentCustomerId(index.data(Qt::EditRole).value<CustomerId>());
}

void KDEApplicationListViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    // model->setData(index, qobject_cast<CategoryTypeComboBox *>(editor)->currentCustomerId());
}

void KDEApplicationListViewDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex & /*index*/) const
{
    const int hCell = option.rect.height();
    const QSize hint = editor->sizeHint();
    const int hEditor = hint.height();
    const int h = std::max(hCell, hEditor);
    QSize size = option.rect.size();
    size.setWidth(std::max(size.width(), hint.width()));
    size.setHeight(h);
    editor->setGeometry(QRect(option.rect.topLeft() - QPoint(0, (h - hCell) / 2), size));
}

void KDEApplicationListViewDelegate::doneEditing()
{
    Q_EMIT commitData(mComboBox);
    Q_EMIT closeEditor(mComboBox);
}
