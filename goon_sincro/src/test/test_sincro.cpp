/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "test_sincro.h"

using namespace log4cxx;
LoggerPtr SincroTest::logger(Logger::getLogger("goon.test"));


// Constructor
SincroTest::SincroTest (int num_jobs)
{
    std::string version = "0.2";
    LOG4CXX_INFO(logger, "*************************************************************");
    LOG4CXX_INFO(logger, "Starting SincroTest - v" << version);
    LOG4CXX_INFO(logger, "jobs = " << num_jobs);
    LOG4CXX_INFO(logger, "*************************************************************");

    oHeart = new Heart();
    numJobs = num_jobs;
    for (int i=0; i<numJobs; i++)
    {
        oSimpleJobs[i] = new SimpleJob(oHeart, i, 1000);
        bactive[i] = false;
    }    
}

// Destructor
SincroTest::~SincroTest ()
{
    for (int i=0; i<numJobs; i++)
        delete (oSimpleJobs[i]);

    delete (oHeart);
}


void SincroTest::startAll()
{
    LOG4CXX_INFO(logger, "START ALL");

    for (int i=0; i<numJobs; i++)
        start(i);
}


void SincroTest::stopAll()
{
    LOG4CXX_INFO(logger, "STOP ALL");

    for (int i=0; i<numJobs; i++)
        stop(i);
}


void SincroTest::start (int i)
{
    int ret;

    LOG4CXX_INFO(logger, "START " << i);

    // launch thread
    if (!bactive[i])
    {
        ret = pthread_create (&threads[i], NULL, runJob, oSimpleJobs[i]);
        if (ret > 0)
        {
            LOG4CXX_ERROR(logger, "Error creating job thread ... ");                    
        }
        else
            bactive[i] = true;
    }
    else
        LOG4CXX_ERROR(logger, "Job already started!");    
}


void SincroTest::stop(int i)
{
    LOG4CXX_INFO(logger, "STOP " << i);

    // stop thread
    if (bactive[i])
    {
        oSimpleJobs[i]->stop();
        pthread_join (threads[i], NULL);
        bactive[i] = false;        
        LOG4CXX_INFO(logger, "thread joined");
    }
    else
        LOG4CXX_ERROR(logger, "Job already stopped!");    

}


void SincroTest::doOne(int id)
{
    LOG4CXX_INFO(logger, "DO ONE " << id);

    oSimpleJobs[id]->doOne();
}


void SincroTest::doTwo(int id)
{
    LOG4CXX_INFO(logger, "DO TWO " << id);

    oSimpleJobs[id]->doTwo();
}


void SincroTest::getJobData(int id, int* pstate, int* prealCycle, Sincro::st_debugData* psincroDebug)
{
    oSimpleJobs[id]->getData(pstate, prealCycle, psincroDebug);
}


int SincroTest::getNumJobs()
{
    return numJobs;
}


void SincroTest::heartUp()
{
    LOG4CXX_INFO(logger, "HEART UP");

    oHeart->raiseRythm();
}


void SincroTest::heartDown()
{
    LOG4CXX_INFO(logger, "HEART DOWN");

    oHeart->lowerRythm();
}


int SincroTest::getHeartRythm()
{
    int value = oHeart->getRythm();
    return (value);
}


// Thread functions that run the jobs
void* runJob (void* arg)
{
    SimpleJob* pSimpleJob = (SimpleJob*) arg;
    pSimpleJob->run();
}




