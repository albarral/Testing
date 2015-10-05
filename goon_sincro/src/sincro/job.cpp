/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

// Base class for job executions inside threads.

#include "job.h"

// main constructor
Job::Job()
{
   pthread_mutex_init (&mutex, NULL);

   // default synchronization: normal process, 10% tolerance
   oSincro = new Sincro (Sincro::ePROC_NORMAL, 0.1);

   state = 0;
   request = 0;
   bstopRequested = false;
}

Job::~Job()
{
    pthread_mutex_destroy (&mutex);

    if (oSincro != NULL)
        delete (oSincro);
}

// ************* EXTERNAL CALLS ****************


void Job::setSincroType(Sincro::eProcess processType)
{
    oSincro->setProcessType(processType);
}


void Job::setSincroTolerance(float tolerance)
{
    oSincro->setTolerance(tolerance);
}


int Job::getState()
{
    pthread_mutex_lock (&mutex);
    int value = state;
    pthread_mutex_unlock (&mutex);
    return (value);
}

void Job::getDebugData(Sincro::st_debugData* psincroDebug)
{
   oSincro->getDebugData(psincroDebug); 
}


// ************* PROTECTED CALLS ****************


void Job::changeState(int value)
{
    pthread_mutex_lock (&mutex);
    state = value;
    pthread_mutex_unlock (&mutex);
}

void Job::setRequest(int new_request)
{
    pthread_mutex_lock (&mutex);
    request = new_request;
    pthread_mutex_unlock (&mutex);
}

int Job::getRequest()
{
    pthread_mutex_lock (&mutex);
    int value = request;
    pthread_mutex_unlock (&mutex);
    return (value);
}

void Job::clearRequests()
{
    pthread_mutex_lock (&mutex);
    bstopRequested = false;
    request = 0;
    pthread_mutex_unlock (&mutex);
}

int Job::synchronize(Sincro::eRythm rythm, int real_cycle)
{
    return oSincro->followRythm(rythm, real_cycle);
}

void Job::stop()
{
    pthread_mutex_lock (&mutex);
    bstopRequested = true;
    pthread_mutex_unlock (&mutex);
}

bool Job::isStopRequested()
{
    pthread_mutex_lock (&mutex);
    bool bvalue = bstopRequested;
    pthread_mutex_unlock (&mutex);
    return (bvalue);
}

