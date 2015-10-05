#ifndef __PLACE_H
#define __PLACE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *

 ***************************************************************************/

#include <vector>
#include "navigation/Connection2.h"

namespace sam 
{
// Class to represent places in a environment
class Place2
{
private:
    int ID;
    std::vector<Connection2> listConnections;

public:

    Place2();

    int getID() {return ID;};
    void setID(int ID) {this->ID = ID;};

    void addConnection(Connection2& oConnection);
    std::vector<Connection2>& getListConnections() {return listConnections;};
    void resetConnections();    
    
};
}

#endif
