/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics  *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

#include "simple_job.h"
#include "sincro/crono.h"
#include "log4cxx/ndc.h"

using namespace log4cxx;
LoggerPtr SimpleJob::logger(Logger::getLogger("goon.test.job"));


SimpleJob::SimpleJob(Heart* oHeart, int job_id, int base_num)
{
    mHeart = oHeart;
    ID = job_id;
    baseNum = base_num;
    counter = 0;
//    this::setSincroType(Sincro::ePROC_NORMAL);
//    this::setSincroType(Sincro::ePROC_SLOW);
    setSincroType(Sincro::ePROC_FAST);
}


void SimpleJob::run ()
{
    int waitedTime = 0;
    float loopTime;
    Crono oCrono;
    
    std::string jobName = "Job-" + std::to_string(ID);
    log4cxx::NDC::push(jobName);
    log4cxx::NDC::push("iddle");
    
    clearRequests();
    changeState(eSTATE_IDDLE);

    while (!isStopRequested())
    {
        checkRequests();

        switch (getState())
        {
            case eSTATE_IDDLE:                
                break;

            case eSTATE_ONE:
                doWork(100);
                break;

            case eSTATE_TWO:
                doWork(1000);
                break;
        }

        // adjust job's frequency
        loopTime = oCrono.click();
        waitedTime = synchronize(mHeart->getRythm(), loopTime); 
    }

    changeState(eSTATE_OFF);

    LOG4CXX_INFO(logger, "end");
    log4cxx::NDC::remove();
}

// EXTERNAL CALLS

void SimpleJob::doOne()
{
    LOG4CXX_INFO(logger, " >>> doOne");
    setRequest (eREQUEST_ONE);
}


void SimpleJob::doTwo()
{
    LOG4CXX_INFO(logger, " >>> doTwo");
    setRequest (eREQUEST_TWO);
}


void SimpleJob::getData(int* pstate, int* prealCycle, Sincro::st_debugData* psincroDebug)
{
    *pstate = this->getState();
    this->getDebugData(psincroDebug);
}

// INTERNAL CALLS

void SimpleJob::checkRequests()
{
    switch (getRequest())
    {
        case eREQUEST_ONE:
            changeState(eSTATE_ONE);
            log4cxx::NDC::pop();
            log4cxx::NDC::push("one");
            break;

        case eREQUEST_TWO:
            changeState(eSTATE_TWO);
            log4cxx::NDC::pop();
            log4cxx::NDC::push("two");
            break;
    }
    // clear request
    clearRequests();
}


void SimpleJob::doWork(int num)
{
    counter = 0;
    for (int i=0; i<num; i++)
        for (int j=0; j<baseNum; j++)
                counter++;
}
