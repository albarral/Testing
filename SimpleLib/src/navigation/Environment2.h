#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *

 ***************************************************************************/

#include <vector>
#include "navigation/Place2.h"

namespace sam 
{
// Class to represent a environment as a list of places linked by connections
class Environment2
{
private:
    int ID;
    std::vector<Place2> listPlaces;

public:

    Environment2();

    int getID() {return ID;};
    void setID(int ID) {this->ID = ID;};

    void addPlace(Place2& oPlace);
    std::vector<Place2>& getListPlaces() {return listPlaces;};;
    void resetPlaces();    
    
};
}

#endif
