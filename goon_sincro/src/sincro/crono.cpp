/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdlib.h>

#include "crono.h"

// Constructor
Crono::Crono()
{
    gettimeofday (&t0, NULL);
}

// computes the ellapsed time (ms) since the previous click (or its creation)
float Crono::click ()
{
    float dif_milis;

    gettimeofday (&t1, NULL);
    dif_milis = (t1.tv_sec - t0.tv_sec)*1000 + ((float)(t1.tv_usec - t0.tv_usec) / 1000);
    t0 = t1;

    return (dif_milis);
}

