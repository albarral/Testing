/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QEventLoop>

#include "Worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{
    _working = false;
    _abort = false;
//    oDatabase.init("tcp://127.0.0.1:3306", "sam", "sam", "samMemo");
}

void Worker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug()<<"Request worker start in Thread "<<thread()->currentThreadId();
    mutex.unlock();
    
//    con = oDatabase.getConnectionDB(); 

    emit workRequested();
}
   
void Worker::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
    mutex.unlock();
    
//    oDatabase.closeConnectionDB(); 
}

void Worker::doWork()
{
    qDebug()<<"Starting worker process in Thread "<<thread()->currentThreadId();

    for (int i = 0; i < 60; i ++) 
    {

        // Checks if the process should be aborted
        mutex.lock();
        bool abort = _abort;
        mutex.unlock();

        if (abort) {
            qDebug()<<"Aborting worker process in Thread "<<thread()->currentThreadId();
            break;
        }

        // This will stupidly wait 1 sec doing nothing...
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, SLOT(quit()));
        loop.exec();
        
        //Coger datos de la bbdd
//        std::string sel = "SELECT * FROM TAB_BOARD WHERE tryID = " + std::to_string(i);
//        sql::ResultSet* res = pDatabase->select(sel, con);
//    
//        while (res->next())
//        {
//             = res->getInt("cell00");
//             = res->getInt("cell01");
//             = res->getInt("cell02");
//             = res->getInt("cell10");
//             = res->getInt("cell11");  
//             = res->getInt("cell12");  
//             = res->getInt("cell20");  
//             = res->getInt("cell21");  
//             = res->getInt("cell22");         
//             = res->getInt("boardStatus");
//        }
        //sleep(1);

    }

    // Set _working to false, meaning the process can't be aborted anymore.
    mutex.lock();
    _working = false;
    mutex.unlock();

    qDebug()<<"Worker process finished in Thread "<<thread()->currentThreadId();

    //Once 60 sec passed, the finished signal is sent
    emit finished();
}