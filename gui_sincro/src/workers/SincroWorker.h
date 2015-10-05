/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#ifndef _SINCRO_WORKER_H
#define _SINCRO_WORKER_H

#include <QObject>
#include "test/test_sincro.h"

class SincroWorker : public QObject 
{ 
    Q_OBJECT    
    
public:
    struct st_guiData 
    {
        int state;
        float tarFreq;
        float realFreq;
        int devSign;
        int devFraction;
        int waitFraction;        
    };

 private:    
    bool bstop;
    SincroTest* mSincroTest;
    st_guiData jobsData[4];

public:
    SincroWorker(SincroTest* oSincroTest);
    ~SincroWorker();
       
    public slots:
        void process ();
        void stop();       
        
   signals:
        void refreshGUI(SincroWorker::st_guiData* data, int rythm);
        void finished();

    private:
        void transformJobData(st_guiData* jobData, int state, int real_cycle, Sincro::st_debugData* sincroDebug);
};

#endif	/* _SINCRO_SENSING_H */
