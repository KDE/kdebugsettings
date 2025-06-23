/*
    SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "customdebuglistviewgui.h"
using namespace Qt::Literals::StringLiterals;

#include "customdebuglistview.h"
#include "model/customloggingcategorymodel.h"

#include <QApplication>
#include <QVBoxLayout>

CustomDebugListViewGui::CustomDebugListViewGui(QWidget *parent)
    : QWidget{parent}
{
    auto vboxLayout = new QVBoxLayout(this);
    auto view = new CustomDebugListView(this);

    LoggingCategory::List lst;
    for (int i = 0; i < 5; ++i) {
        LoggingCategory cat;
        cat.categoryName = u"foo-%1"_s.arg(i);
        cat.identifierName = u"ident-%1"_s.arg(i);
        cat.description = u"desc-%1"_s.arg(i);
        cat.enabled = (i % 2);
        lst.append(cat);
    }

    auto model = new CustomLoggingCategoryModel(this);
    model->setLoggingCategories(lst);
    view->setLoggingCategoryModel(model);
    vboxLayout->addWidget(view);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CustomDebugListViewGui w;
    w.show();
    return app.exec();
}

#include "moc_customdebuglistviewgui.cpp"
