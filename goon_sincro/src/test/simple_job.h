#ifndef SIMPLE_JOB_H
#define SIMPLE_JOB_H

/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics  *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sincro/job.h"
#include "sincro/heart.h"

struct s_jobData
{
    int state;
    int target_cycle;
    int real_cycle;
    int wait_time;
};

class SimpleJob: public Job
{
private:
    static log4cxx::LoggerPtr logger;
    int ID;
    int baseNum;
    Heart* mHeart;
    int counter;

    enum eState
    {
         eSTATE_OFF,
         eSTATE_IDDLE,
         eSTATE_ONE,
         eSTATE_TWO
    };

     enum eRequest
    {
         eREQUEST_NONE,
         eREQUEST_ONE,
         eREQUEST_TWO
    };

public:

    SimpleJob(Heart* oHeart, int job_id, int base_num);
    
   // Implements the job.
   void run ();
   void doOne();
   void doTwo();
   void getData(int* pstate, int* prealCycle, Sincro::st_debugData* psincroDebug);

private:
    // sets the proper state regarding the last request
    void checkRequests();
    void doWork(int num);
};

						
#endif		
