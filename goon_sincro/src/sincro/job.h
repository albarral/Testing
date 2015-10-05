#ifndef __JOB_H
#define __JOB_H

/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

// Base class for job executions inside threads.

#include <pthread.h>
#include "sincro.h"

class Job
{        
   private:
        pthread_mutex_t mutex;
        Sincro* oSincro;
        int state;
        int request;
        bool bstopRequested;        

    public:
        // main constructor
        Job ();
        ~Job();

        // changes the synchronization process type 
        void setSincroType (Sincro::eProcess processType);
        // changes the synchronization tolerance
        void setSincroTolerance(float tolerance);
        
       // Implements the job.
       virtual void run () =0;
       // Requests the job to stop
       void stop ();
       // Returns the job's state (mutex protected).
       int getState ();
       // for debugging (mutex protected)
       void getDebugData (Sincro::st_debugData* psincroDebug);
       

    protected:
       // Updates the state value (mutex protected).
       void changeState (int value);
       // Sets a new external request (mutex protected).
       void setRequest (int new_request);
       // Gets the last external request (mutex protected).
       int getRequest ();
       // Clears pending requests
       void clearRequests();
       // Checks if stop was requested
       bool isStopRequested();
       // Sinchronizes the job with the specified rythm
       int synchronize(Sincro::eRythm rythm, int real_cycle);

};
		
#endif
