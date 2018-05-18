#include "coordinate.h"

Coordinate::Coordinate(double xCoordinate,
                       double yCoordinate,
                       double frameHeight): m_xCoordinate(xCoordinate), m_yCoordinate(yCoordinate), m_frameHeight(frameHeight){}

Coordinate::~Coordinate()
{
}

double Coordinate::getQtRenderingXCoordinate()
{
    return m_xCoordinate;
}

double Coordinate::getQtRenderingYCoordinate()
{
    return m_frameHeight - m_yCoordinate;
}

double Coordinate::getFrameHeight()
{
    return m_frameHeight;
}


void Coordinate::changeFrameHeight(double change)
{
    m_frameHeight = change;
}

void Coordinate::setYCoordinateToZero(double offset)
{
    m_yCoordinate = offset;
}

void Coordinate::setXCoordinateToZero(double offset)
{
    m_xCoordinate = offset;
}

void Coordinate::changeInXCoordinate(double change)
{
    m_xCoordinate += change;
}

void Coordinate::changeInYCoordinate(double change)
{
    m_yCoordinate += change;
}
