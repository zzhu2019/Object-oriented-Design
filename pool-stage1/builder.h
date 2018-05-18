/*!
  this file is the abstract builder, which is the manufacturer.
*/
#ifndef BUILDER_H
#define BUILDER_H
#include "product.h"
#include "concretefactory.h"

class manufacturer{//builder
    //for pool
public:
    Factory factory;///<using factory in builder
    virtual poolTable *buildTable(double xsize, double ysize, string color, double fri) = 0;///<a method of building table
    virtual poolBall *buildBall(Coordinate coordinate, double radius, string color, double mass, Velocity velocity) = 0;///<a method of buidling table
    virtual poolGame *getPool() = 0;
};

#endif // BUILDER_H
