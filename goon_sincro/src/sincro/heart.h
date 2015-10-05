#ifndef HEART_H
#define HEART_H

/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics  *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sincro.h"

class Heart
{
public:

private:
    pthread_mutex_t mutex;
    Sincro::eRythm rythm;
    int energy;

public:

    Heart ();
    ~Heart();

    Sincro::eRythm getRythm ();    
    bool raiseRythm();
    bool lowerRythm();
    void setRythm (Sincro::eRythm value);
    
    void setEnergy (int value);
    int getEnergy ();

};

						
#endif		
