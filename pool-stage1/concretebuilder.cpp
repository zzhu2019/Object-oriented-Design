#include "concretebuilder.h"

poolTable *poolManufacturer::buildTable(double xsize, double ysize, string color, double fri)
{
    return factory.createTable(xsize, ysize, color, fri);
}

poolBall *poolManufacturer::buildBall(Coordinate coordinate, double radius, string color, double mass, Velocity velocity)
{
    return factory.createBall(coordinate, radius, color, mass, velocity);
}
poolGame *poolManufacturer::getPool()
{
    return new poolGame();
}
