/*!
  this file is the concrete buidler derived from abstract builder. The functions are from its base class.
*/
#ifndef CONCRETEBUILDER_H
#define CONCRETEBUILDER_H
#include "builder.h"


class poolManufacturer : public manufacturer{//concrete builder
    //detailed pool use factory to get product
public:
    virtual poolTable *buildTable(double xsize, double ysize, string color, double fri);
    virtual poolBall *buildBall(Coordinate coordinate, double radius, string color, double mass, Velocity velocity);
    virtual poolGame *getPool();
};

#endif // CONCRETEBUILDER_H

