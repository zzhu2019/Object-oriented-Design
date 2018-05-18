/*!
  It is concrete factory derived from abstract factory, and it will be used for prduction.
*/
#ifndef CONCRETEFACTORY_H
#define CONCRETEFACTORY_H
#include "factory.h"

class Factory : public Absfactory {//factory
    //create balls
    //create table
public:
    poolTable *createTable(double xsize = 100, double ysize = 100, string color = "white", double fri = 0);//maybe need some input
    poolBall *createBall(Coordinate coordinate, double radius, string color, double mass, Velocity velocity);//same as above
};

#endif // CONCRETEFACTORY_H
