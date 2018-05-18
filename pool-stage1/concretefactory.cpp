#include "concretefactory.h"

poolTable *Factory::createTable(double xsize, double ysize, string color, double fri)//maybe need some input
{
    //get the ball shaped and colored
    return new poolTable(xsize, ysize, color, fri);
}
poolBall *Factory::createBall(Coordinate coordinate, double radius, string color, double mass, Velocity velocity)//same as above
{
    //get the table shaped and colored
    return new poolBall(coordinate, radius, color, mass, velocity);
}
