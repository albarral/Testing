#ifndef __CLICK_H
#define __CLICK_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *

 ***************************************************************************/

#include <chrono>

namespace goon 
{
// Utility class for computing time intervals.
class Click
{
private:
    bool brunning;
    std::chrono::steady_clock::time_point t1;
    std::chrono::steady_clock::time_point t2;

public:

    Click();
    // stores initial time point
    void start();
    // stores final time point
    void stop();    
    // returns the ellapsed time (t2 - t1) in milliseconds
    int getMillis();
    // returns the ellapsed time (t2 - t1) in microseconds
    int getMicros();
    
};
}

#endif
