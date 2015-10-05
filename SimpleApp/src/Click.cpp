/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Click.h"

using namespace std;

namespace goon 
{
Click::Click()
{
    brunning = false;
    t1 = t2 = chrono::steady_clock::now();
}

void Click::start()
{
    t1 = chrono::steady_clock::now();
    brunning = true;    
}

void Click::stop()
{
    if (brunning)
    {
        t2 = chrono::steady_clock::now();
        brunning = false;            
    }
}

int Click::getMillis()
{
    if (brunning == false)
    {
        chrono::duration<int, milli> interval = chrono::duration_cast<chrono::milliseconds>(t2-t1);
        return interval.count();        
    }
    else 
        return -1;
}

int Click::getMicros()
{
    if (brunning == false)
    {
        chrono::duration<int, micro> interval = chrono::duration_cast<chrono::microseconds>(t2-t1);
        return interval.count();        
    }
    else 
        return -1;
}

}