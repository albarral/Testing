/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <QApplication>
#include "forms/SincroForm.h"
#include "forms/testForm.h"
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx::xml;

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    DOMConfigurator::configure("log4cxx_config.xml");
    
    QApplication app(argc, argv);

    // create and show your widgets here
    SincroForm form;
    form.show();
    //testForm form;
    //form.show();
    
    return app.exec();
}
