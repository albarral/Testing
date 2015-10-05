/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics  *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "heart.h"

// Constructor
Heart::Heart ()
{
    pthread_mutex_init (&mutex, NULL);

    rythm = Sincro::eRYTHM_ACTIVE;
}

Heart::~Heart ()
{
    pthread_mutex_destroy (&mutex);
}

Sincro::eRythm Heart::getRythm()
{
    pthread_mutex_lock (&mutex);
    Sincro::eRythm value = rythm;    
    pthread_mutex_unlock (&mutex);
    return value;
}

void Heart::setRythm(Sincro::eRythm value)
{
    pthread_mutex_lock (&mutex);

    if (value >= 0 && value < Sincro::eRYTHM_DIM)	
        rythm = value;

    pthread_mutex_unlock (&mutex);
}

bool Heart::raiseRythm()
{
    pthread_mutex_lock (&mutex);

    bool bchanged = false;
    if (rythm < Sincro::eRYTHM_ACTIVE)	
    {
        int value = rythm;
        value++;
        rythm = (Sincro::eRythm)value;
        bchanged = true;
    }      
    pthread_mutex_unlock (&mutex);
  
    return bchanged;
}

bool Heart::lowerRythm()
{
    pthread_mutex_lock (&mutex);

    bool bchanged = false;
    if (rythm > 0)	
    {
        int value = rythm;
        value--;
        rythm = (Sincro::eRythm)value;
        bchanged = true;
    }      
    pthread_mutex_unlock (&mutex);
  
    return bchanged;
}


void Heart::setEnergy(int value)
{
    energy = value;
}

int Heart::getEnergy()
{
    return energy;
}
