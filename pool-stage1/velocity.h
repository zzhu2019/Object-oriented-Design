/*!
  It is a velocity class, it will be used in pool ball to show the velocty of moving balls.
  It has two member variables: x velocity and y velocity.
  It also has some other helpful functions for velocity management.
*/
#ifndef VELOCITY_H
#define VELOCITY_H


class Velocity
{
private:
    double m_XVelocity;///< x velocity
    double m_YVelocity;///< y velocity
public:
    Velocity(double XVelocity, double YVelocity);
    ~Velocity();
    double getXVelocity();///< get x velocity
    double getYVelocity();///< get y velocity
    void changeXVelocity(double change);///<change x velocity by increasing the value of change
    void changeYVelocity(double change);///<change y velocity by increasing the value of change
    void setXOffset();///<set x velocity to 0
    void setYOffset();///<set y velocity to 0
    void changeXDirection();///<change the direction of x velocity into opposite.
    void changeYDirection();///<change the direction of y velocity into opposite.
};

#endif // VELOCITY_H
