/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>

#include "SincroWorker.h"

SincroWorker::SincroWorker(SincroTest* oSincroTest) 
{
    mSincroTest = oSincroTest;       
    bstop = false;
}

SincroWorker::~SincroWorker() {
}

void SincroWorker::process()
{
    int state, real_cycle;
    Sincro::st_debugData sincroData;
    
    int num_jobs = mSincroTest->getNumJobs();
    
    while (!bstop)
    {
        for (int i=0; i<num_jobs; i++)
        {
            mSincroTest->getJobData(i, &state, &real_cycle, &sincroData);
            transformJobData(&jobsData[i], state, real_cycle, &sincroData);            
        }
                
        int rythm = mSincroTest->getHeartRythm();
        emit refreshGUI(jobsData, rythm);
        
        usleep (300000);   // 300ms             
    }

    emit finished();
}

void SincroWorker::stop()
{
    bstop = true;
}

void SincroWorker::transformJobData(st_guiData* jobData, int state, int real_cycle, Sincro::st_debugData* sincroData)
{
    jobData->state = state;
    jobData->tarFreq = 1000.0/sincroData->cycle;
    jobData->realFreq = 1000.0/real_cycle;
    jobData->devSign = (sincroData->deviation < 0 ? -1 : 1);
    jobData->devFraction = 100*fabs(sincroData->deviation);
    jobData->waitFraction = 100*sincroData->wait/sincroData->cycle;
}