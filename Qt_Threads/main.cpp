/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <QApplication>
#include <QDebug>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);

    MainWindow win;
    win.show();

    return app.exec();

}
