#ifndef __TEST_SINCRO_H
#define __TEST_SINCRO_H

/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>
#include "sincro/heart.h"
#include "simple_job.h"


class SincroTest
{
    private:
        static log4cxx::LoggerPtr logger;
        Heart* oHeart;
        int numJobs;
        SimpleJob* oSimpleJobs[5];
        pthread_t threads[5];
        bool bactive[5];

    public:
        SincroTest(int num_jobs);
        ~SincroTest();

        void startAll();
        void stopAll();
        void start(int id);
        void doOne(int id);
        void doTwo(int id);
        void stop(int id);
        void getJobData(int id, int* pstate, int* prealCycle, Sincro::st_debugData* psincroDebug);
        void heartUp();
        void heartDown();
        int getHeartRythm();
        int getNumJobs();
};
    
void* runJob (void* arg);

#endif
