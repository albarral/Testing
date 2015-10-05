#ifndef __CONNECTION_H
#define __CONNECTION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *

 ***************************************************************************/

namespace sam 
{
// Class to represent connections between places in a environment
class Connection2
{
private:
    int ID;
    int place;
    int nextPlace;

public:

    Connection2();
    
    int getID() {return ID;};
    void setID(int ID) {this->ID = ID;};
    int getPlace() {return place;};
    void setPlace(int place) {this->place = place;};
    int getNextPlace() {return nextPlace;};
    void setNextPlace(int place) {this->nextPlace = place;};
    
};
}

#endif
