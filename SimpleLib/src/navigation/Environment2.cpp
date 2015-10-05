/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Environment2.h"

using namespace std;

namespace sam
{
Environment2::Environment2()
{
    ID = -1;
}

void Environment2::addPlace(Place2& oPlace)
{
    listPlaces.push_back(oPlace);
}

void Environment2::resetPlaces()
{
    listPlaces.clear();
}

}