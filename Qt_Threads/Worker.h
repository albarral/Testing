#ifndef WORKER_H
#define	WORKER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <QObject>
#include <QMutex>
#include <QtGui>

//#include "sam/utils/Database.h"

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker(QObject *parent = 0);
    
    void requestWork();
    void abort();

private:
    
    bool _abort;
    bool _working;

    QMutex mutex;
 //   Database oDatabase;
 //   sql::Connection* con;

signals:
    void workRequested();
    void finished();

public slots:

    void doWork();
};

#endif	/* WORKER_H */

