#ifndef __SYNCHRO_H
#define __SYNCHRO_H

/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
// This class features job sinchronization
// For different process types (slow, normal and fast) it waits for the appropriate time 
// to achieve the execution frequency corresponding to a specified rythm (active, relaxed, sleep)

#include <log4cxx/logger.h>

class Sincro
{
    public:
        // types of process
        enum eProcess
        {
            ePROC_SLOW,
            ePROC_NORMAL,
            ePROC_FAST,
            ePROC_DIM
        };

    // types of rythm
    enum eRythm
    {
        eRYTHM_SLEEP,
        eRYTHM_RELAXED,
        eRYTHM_ACTIVE,
        eRYTHM_DIM
    };
 
    struct st_debugData
    {
        int cycle;
        int real_cycle;
        int wait;
        float deviation;
        float rate;
    };

    private:
        static log4cxx::LoggerPtr logger;
        pthread_mutex_t mutex_debug;
        eProcess process;
        eRythm rythm;
        int tab_cycles[eRYTHM_DIM];   // ms
        int cycle;      // ms
        int real_cycle; // ms
        int wait;       // ms
        int step;       // ms
        float tolerance;
        float deviation;
        int counts;
        int counts_out;
        float rate_corrections;
        
    public:
        Sincro (eProcess processType, float valTolerance);
        ~Sincro();

        void setProcessType(eProcess processType);
        void setTolerance(float value);
        int followRythm (eRythm new_rythm, int measured_cycle);        
        // for debugging (mutex protected).
        void getDebugData(st_debugData* pdebug);

private:
        void setNewRythm(eRythm new_rythm);
        void updateWorkingValues();
        void computeCorrection ();
        void trackCorrections (bool bcorrected);
};
		
#endif
