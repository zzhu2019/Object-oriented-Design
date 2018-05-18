/*!
   It is the abstract factory and named Absfactory as a part of abstract factory design pattern structure.
*/
#include "product.h"
#ifndef FACTORY_H
#define FACTORY_H

class Absfactory{//abstarct factory
    //create balls
    //create table
public:
    ~Absfactory() {}
    virtual poolTable* createTable(double xsize = 100, double ysize = 100, string color = "white", double fri = 0) = 0;///<a method of creating table object.
    virtual poolBall* createBall(Coordinate coordinate, double radius, string color, double mass, Velocity velocity) = 0;///<a method of creating ball obejct.
};

#endif // FACTORY_H
