/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Place2.h"

namespace sam
{
Place2::Place2()
{
    ID = -1;
}

void Place2::addConnection(Connection2& oConnection)
{
    listConnections.push_back(oConnection);
}

void Place2::resetConnections()
{
    listConnections.clear();
}
}