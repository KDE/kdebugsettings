/*
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "previewgeneratedfilewidget.h"
#include <QPlainTextEdit>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
PreviewGeneratedFileWidget::PreviewGeneratedFileWidget(QWidget *parent)
    : QWidget{parent}
    , mTextEdit(new QPlainTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mTextEdit->setObjectName("mTextEdit"_L1);
    mainLayout->addWidget(mTextEdit);
    mTextEdit->setReadOnly(true);
}

PreviewGeneratedFileWidget::~PreviewGeneratedFileWidget() = default;

void PreviewGeneratedFileWidget::setPlainText(const QString &str)
{
    mTextEdit->setPlainText(str);
}

#include "moc_previewgeneratedfilewidget.cpp"
