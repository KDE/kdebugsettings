/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "customdebuglistviewgui.h"

#include <QApplication>

CustomDebugListViewGui::CustomDebugListViewGui(QWidget *parent)
    : QWidget{parent}
{
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CustomDebugListViewGui w;
    w.show();
    return app.exec();
}
