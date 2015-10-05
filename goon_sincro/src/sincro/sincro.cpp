/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "unistd.h"
#include "sincro.h"

using namespace log4cxx;
LoggerPtr Sincro::logger(Logger::getLogger("goon.utils.sincro"));


Sincro::Sincro(eProcess processType, float valTolerance)
{
    pthread_mutex_init (&mutex_debug, NULL);

    rythm = eRYTHM_ACTIVE;
    tolerance = valTolerance;
    setProcessType(processType);    

    counts = 1;
    counts_out = 0;
    rate_corrections = 0.0;
}

Sincro::~Sincro()
{
    pthread_mutex_destroy (&mutex_debug);
}

void Sincro::setProcessType(eProcess processType)
{
    const float normal_cycles[eRYTHM_DIM] = {10000, 3000, 1000}; // ms
    const float fast_process_factor = 0.3;
    const float slow_process_factor = 3;
    int i;
  
    LOG4CXX_DEBUG(logger, "setProcessType -> " << (int)processType);
    process = processType;

    switch (process)
    {
        case ePROC_SLOW:
            for (i = 0; i<eRYTHM_DIM; i++)
                tab_cycles[i] = normal_cycles[i] * slow_process_factor;
            break;

        case ePROC_NORMAL:
            for (i = 0; i<eRYTHM_DIM; i++)
                tab_cycles[i] = normal_cycles[i];
            break;

        case ePROC_FAST:
            for (i = 0; i<eRYTHM_DIM; i++)
                tab_cycles[i] = normal_cycles[i] * fast_process_factor;
            break;
    }
    
    updateWorkingValues();
}


void Sincro::setTolerance(float value)
{
    tolerance = value;
    updateWorkingValues();
}


// computes the appropriate wait time and waits for it
int Sincro::followRythm(eRythm new_rythm, int measured_cycle)
{
    pthread_mutex_lock (&mutex_debug);
    
    real_cycle = measured_cycle;
    
    if (new_rythm == rythm)
        computeCorrection();
    else
        setNewRythm(new_rythm);
    
    pthread_mutex_unlock (&mutex_debug);
        
    LOG4CXX_DEBUG(logger, "target " << cycle << " real " << real_cycle << " dev " << deviation << " wait " << wait);

    // correct the job's frequency
    usleep (wait * 1000);       // usecs    
    
    return (wait);
}



// INTERNAL FUNCTIONS *****************


void Sincro::updateWorkingValues()
{
    cycle = tab_cycles[rythm];
    wait = 0.5*cycle;
    step = tolerance * cycle;
}


void Sincro::setNewRythm(eRythm new_rythm)
{
    rythm = new_rythm;
    updateWorkingValues();
        
    switch (new_rythm)
    {
        case eRYTHM_ACTIVE:
        LOG4CXX_INFO(logger, "setNewRythm -> ACTIVE");
        break;

        case eRYTHM_RELAXED:
        LOG4CXX_INFO(logger, "setNewRythm -> RELAXED");
        break;

        case eRYTHM_SLEEP:
        LOG4CXX_INFO(logger, "setNewRythm -> SLEEP");
        break;
    }
}


// Smoothly corrects the wait time to make the real cycle approach the desired one.
void Sincro::computeCorrection()
{
    bool bcorrected = false;

    deviation = (float)(real_cycle - cycle)/cycle;

    // real cycle bigger -> reduce wait time
    if (deviation > tolerance)
    {
        bcorrected = true;
        wait -= step;
        if (wait < 0) wait = 0;
    }
    // real cycle smaller -> increase wait time
    else if (deviation < -tolerance)
    {
        bcorrected = true;
        wait += step;
        if (wait > cycle) wait = cycle;
    }

    trackCorrections(bcorrected);
}


void Sincro::trackCorrections(bool bcorrected)
{
    counts++;
    if (bcorrected)
        counts_out++;

    if (counts == 10000)
    {
        counts = 100;
        counts_out = counts_out/100;
    }

    rate_corrections = (float)counts_out / counts;
}


// Gets the rate of corrections
void Sincro::getDebugData(st_debugData* pdebug)
{
    pthread_mutex_lock (&mutex_debug);
    
    pdebug->cycle = cycle;
    pdebug->real_cycle = real_cycle;
    pdebug->wait = wait;
    pdebug->deviation = deviation;
    pdebug->rate = rate_corrections;
    
    pthread_mutex_unlock (&mutex_debug);
}

