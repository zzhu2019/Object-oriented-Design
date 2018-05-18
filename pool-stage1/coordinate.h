/*!
  I set coordinate of all elements of pool game as a class named Coordinate, it has two memeber variable for x, y.
  And some methods for modifying and getting x, y.
  It is used in pool ball class and pool table class.
*/
#ifndef COORDINATE_H
#define COORDINATE_H

#include <stdlib.h>

class Coordinate
{
public:
    Coordinate(double xCoordinate,
        double yCoordinate,
        double frameHeight);

    ~Coordinate();

    double getQtRenderingXCoordinate();///<get x coordinate
    double getQtRenderingYCoordinate();///<get y coordinate
    //double getYCoordinate();

    void changeInXCoordinate(double change);///<change x coordinate by increasing the value of change
    void changeInYCoordinate(double change);///<change y coordinate by increasing the value of change
    void changeFrameHeight(double change);///<change frame height by increasing the value of change

    void setYCoordinateToZero(double offset);///<set y to offset
    void setXCoordinateToZero(double offset);///<set x to offset

    double getFrameHeight();///<get x coordnate

private:
    double m_xCoordinate;///< x coordinate
    double m_yCoordinate;///< y doordinate
    double m_frameHeight;///< its frame height
};

#endif // COORDINATE_H
