/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "customdebuglistviewgui.h"
#include "customdebuglistview.h"
#include "model/loggingcategorymodel.h"

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
        cat.categoryName = QStringLiteral("foo-%1").arg(i);
        cat.identifierName = QStringLiteral("ident-%1").arg(i);
        cat.description = QStringLiteral("desc-%1").arg(i);
        cat.enabled = (i % 2);
        lst.append(cat);
    }

    auto model = new LoggingCategoryModel(this);
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
