#ifndef __CRONO_H
#define __CRONO_H

/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *

 ***************************************************************************/
#include <sys/time.h>

class Crono
{
private:
    timeval t0;
    timeval t1;

public:

    Crono();

    // Computes the ellapsed time (in milliseconds) since the previous click.
    float click ();

};

#endif
