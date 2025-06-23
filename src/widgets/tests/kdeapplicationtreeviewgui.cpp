/*
    SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "kdeapplicationtreeviewgui.h"
using namespace Qt::Literals::StringLiterals;

#include "kdeapplicationtreeview.h"
#include "model/kdeapplicationloggingcategorymodel.h"

#include <QApplication>
#include <QVBoxLayout>

KDEApplicationTreeViewGui::KDEApplicationTreeViewGui(QWidget *parent)
    : QWidget{parent}
{
    auto vboxLayout = new QVBoxLayout(this);
    auto view = new KDEApplicationTreeView(this);

    LoggingCategory::List lst;
    for (int i = 0; i < 5; ++i) {
        LoggingCategory cat;
        cat.categoryName = u"foo-%1"_s.arg(i);
        cat.identifierName = u"ident-%1"_s.arg(i);
        cat.description = u"desc-%1"_s.arg(i);
        cat.loggingType = static_cast<LoggingCategory::LoggingType>(i);
        cat.enabled = (i % 2);
        lst.append(cat);
    }

    auto model = new KDEApplicationLoggingCategoryModel(this);
    model->setLoggingCategories(lst);
    view->setLoggingCategoryModel(model);

    vboxLayout->addWidget(view);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    KDEApplicationTreeViewGui w;
    w.show();
    return app.exec();
}

#include "moc_kdeapplicationtreeviewgui.cpp"
