#include "velocity.h"
#include "iostream"

Velocity::Velocity(double XVelocity, double YVelocity):
    m_XVelocity(XVelocity), m_YVelocity(YVelocity){}
Velocity::~Velocity() {}
double Velocity::getXVelocity()
{
    return m_XVelocity;
}
double Velocity::getYVelocity()
{
    return m_YVelocity;
}
void Velocity::changeXVelocity(double change)
{
    //std::cout<<m_XVelocity<<std::endl;
    //std::cout<<"---------"<<std::endl;
    //std::cout<<change<<std::endl;
    //std::cout<<"---"<<std::endl;
    m_XVelocity += change;
    //std::cout<<m_XVelocity<<std::endl;
    //std::cout<<"---------\n"<<std::endl;
}
void Velocity::changeYVelocity(double change)
{
    m_YVelocity += change;
    //std::cout<<"in"<<std::endl;
}
void Velocity::setXOffset()
{
    m_XVelocity = 0;
}
void Velocity::setYOffset()
{
    m_YVelocity = 0;
}
void Velocity::changeXDirection()
{
    m_XVelocity = m_XVelocity * (-1);
}
void Velocity::changeYDirection()
{
    m_YVelocity = m_YVelocity * (-1);
}
