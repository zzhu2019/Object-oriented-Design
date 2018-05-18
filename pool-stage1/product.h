/*!
  It is the product file including ball, table and pool game class.
  Two classes for ball: ball(abstract) and pool ball (derived and concrete)
  The pool ball class has color, coordinate, radius, mass and velocity member variable, and other functions.
  Twp classes for table: table(abstract) nad pool table (derived and concrete)
  The pool table class has color, coordinate and friction memeber variable and other fucntion.
  One class for pool game: it contain a pointer to pool table and a vector of pointers to pool balls.
*/
#ifndef PRODUCT_H
#define PRODUCT_H
#include "string"
#include "coordinate.h"
#include "velocity.h"
#include "QPainter"
#include "vector"
#include "iostream"
#include "QVector2D"
#include "cmath"
#include <QDebug>
using namespace std;

class table{//normal table
public:
    virtual ~table() {}
};

class poolTable : public table{
    //table is stable, so there is no need for rendering.
private:
    double m_xsize;///< table x size
    double m_ysize;///< table y size
    string m_color;///< table color
    double m_friction;///< table friction
public:
    poolTable(double xsize = 100, double ysize = 100, string color = "white", double friction = 0):
        m_xsize(xsize), m_ysize(ysize), m_color(color), m_friction(friction){}
    
    double getxsize()///<get table x size
    {
        return m_xsize;
    }

    double getysize()///<get table y size
    {
        return m_ysize;
    }

    double getfriction()///<get table friction
    {
        return m_friction;
    }
    
    string getcolor()///<get table color
    {
        return m_color;
    }
};

class ball{//normal ball
public:
    virtual ~ball() {}
};

class poolBall : public ball{
    //balls
private:
    Coordinate m_coordinate;///< ball coordinate
    double m_radius;///< ball radius
    string m_color;///< ball color
    double m_mass;///< ball mass
    Velocity m_velocity;///< ball velocity
public:
    poolBall(Coordinate coordinate, double radius, string color, double mass, Velocity velocity):
        m_coordinate(coordinate), m_radius(radius), m_color(color), m_mass(mass), m_velocity(velocity){}

    void changeVX(double change)///< change the value of x velocity
    {
        m_velocity.changeXVelocity(change);
    }

    void changeVY(double change)///< change the value of y velocity
    {
        m_velocity.changeYVelocity(change);
    }

    Coordinate getcoordinate()///< get ball coordinate
    {
        return m_coordinate;
    }
    
    double getradius()///< get ball radius
    {
        return m_radius;
    }
    
    string getcolor()///< get ball color
    {
        return m_color;
    }
    
    double getmass()///< get ball mass
    {
        return m_mass;
    }
    
    Velocity getvelocity()///< get ball velocity
    {
        return m_velocity;
    }

    void isCollisionWall(QPainter &painter, unsigned int time, double x, double y, double fri)///< check the ball-wall collision and calculate velocity change and cooridnate change
    {
        m_coordinate.changeFrameHeight(y);
        //when collision
        if(m_coordinate.getQtRenderingYCoordinate() > (m_coordinate.getFrameHeight() - m_radius)) // bottom
        {
            m_coordinate.setYCoordinateToZero(this->getradius());
            m_velocity.changeYDirection();
            //velocity and coordinate change
        }
        else if(m_coordinate.getQtRenderingYCoordinate() < m_radius)// top
        {
            m_coordinate.setYCoordinateToZero(y - (this->getradius()));
            m_velocity.changeYDirection();
        }
        else if(m_coordinate.getQtRenderingXCoordinate()<m_radius)// left
        {
            m_coordinate.setXCoordinateToZero(this->getradius());
            m_velocity.changeXDirection();
        }
        else if(x - m_coordinate.getQtRenderingXCoordinate() < m_radius)// right
        {
            m_coordinate.setXCoordinateToZero(x - (this->getradius()));
            m_velocity.changeXDirection();
        }
        painter.setPen ( Qt::black );
        QString color = QString::fromStdString(m_color);
        QBrush brush("white");
        brush.setColor(color);
        painter.setBrush(brush);
        painter.drawEllipse(int(m_coordinate.getQtRenderingXCoordinate()) - (int) m_radius,
            int(m_coordinate.getQtRenderingYCoordinate()) - (int) m_radius,
            int(m_radius) * 2,
            int(m_radius) * 2);

        //change the velocity because of infriction
        double xv, yv;
        if(m_velocity.getXVelocity() < 0)
        {
            if(m_velocity.getXVelocity() > - (fri / 32.0))
            {
                m_velocity.setXOffset();
            }
            else
            {
                xv = m_velocity.getXVelocity();
                m_velocity.changeXVelocity(fri / 32.0);
            }
        }
        else if(m_velocity.getXVelocity() > 0)
        {
            if(m_velocity.getXVelocity() < (fri / 32.0))
            {
                m_velocity.setXOffset();
            }
            else
            {
                xv = m_velocity.getXVelocity();
                m_velocity.changeXVelocity(- fri / 32.0);
            }
        }

        if(m_velocity.getYVelocity() < 0)
        {
            if(m_velocity.getYVelocity() > -(fri / 32.0))
            {
                m_velocity.setYOffset();
            }
            else
            {
                yv = m_velocity.getYVelocity();
                m_velocity.changeYVelocity(fri / 32.0);
            }
        }
        else if(m_velocity.getYVelocity() > 0)
        {
            if(m_velocity.getYVelocity() < (fri / 32.0))
            {
                m_velocity.setYOffset();
            }
            else
            {
                yv = m_velocity.getYVelocity();
                m_velocity.changeYVelocity(- fri / 32.0);
            }
        }
        m_coordinate.changeInXCoordinate(m_velocity.getXVelocity());
        m_coordinate.changeInYCoordinate(m_velocity.getYVelocity());
    }
};

class poolGame{//normal table
private:
    poolTable *m_table;///< the pointer to pool table
    std::vector<poolBall*> m_balls;///< the vector of pointers to pool balls
public:
    poolGame(){}
    //poolGame(poolTable* pt, std::vector<poolBall*> balls) : m_table(pt), m_balls(balls) {}
    ~poolGame()
    {
        delete m_table;
        for (poolBall* i : m_balls) delete i;//method to get ball from ball vector
        m_balls.clear();
    }
    void addTable(poolTable *table)///< add a pool table
    {
        m_table = table;
    }

    void addBall(poolBall *ball)///< add a pool ba;;
    {
        m_balls.push_back(ball);
    }

    poolTable * getpooltable()///< get pool table
    {
        return m_table;
    }

    poolBall * getOnePoolball(int n)///< get a pool ball from vector
    {
        if (n < int(m_balls.capacity()))
        {
            return m_balls[n];
        }
        else
        {
            return 0;
        }
    }

    std::vector<poolBall*> getpoolBalls()///< get the vector
    {
        return m_balls;
    }

    bool isBallCollision(poolBall *A, poolBall *B)///< check the ball-ball collision
    {
        double r1 = A->getradius();
        double r2 = B->getradius();
        double d1 = A->getcoordinate().getQtRenderingXCoordinate() - B->getcoordinate().getQtRenderingXCoordinate();
        double d2 = A->getcoordinate().getQtRenderingYCoordinate() - B->getcoordinate().getQtRenderingYCoordinate();
        double d3 = sqrt(d1 * d1 + d2 * d2);
        if(d3 < r1 + r2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    void CollisionBall(poolBall *A, poolBall *B)///< calculate the velocity and cooridnate change of two collided balls
    //the given code coordinate of A and B, velocity of A and B, mass of A and B.
    {
         //Properties of two colliding balls,
        //cout<<"-----"<<endl;

         QVector2D posA(A->getcoordinate().getQtRenderingXCoordinate(), A->getcoordinate().getQtRenderingYCoordinate());
         QVector2D velA(A->getvelocity().getXVelocity(), A->getvelocity().getYVelocity());
         float massA = A->getmass();
         //and ball B
         QVector2D posB(B->getcoordinate().getQtRenderingXCoordinate(), B->getcoordinate().getQtRenderingYCoordinate());
         QVector2D velB(B->getvelocity().getXVelocity(), B->getvelocity().getYVelocity());
         float massB = B->getmass();

         //calculate their mass ratio
         float mR = massB / massA;

         //calculate the axis of collision
         QVector2D collisionVector = posB - posA;
         collisionVector.normalize();

        //the proportion of each balls velocity along the axis of collision
         double vA = QVector2D::dotProduct(collisionVector, velA);
         double vB = QVector2D::dotProduct(collisionVector, velB);
         //the balls are moving away from each other so do nothing
         if (vA <= 0 && vB >= 0) {
          return ;
         }

         //The velocity of each ball after a collision can be found by solving the quadratic equation
         //given by equating momentum and energy before and after the collision and finding the velocities
         //that satisfy this
         //-(mR+1)x^2 2*(mR*vB+vA)x -((mR-1)*vB^2+2*vA*vB)=0
         //first we find the discriminant
         double a = -(mR + 1);
         double b = 2 * (mR * vB + vA);
         double c = -((mR - 1) * vB * vB + 2 * vA * vB);
         double discriminant = sqrt(b * b - 4 * a * c);
         double root = (-b + discriminant)/(2 * a);
         //only one of the roots is the solution, the other pertains to the current velocities
         if (root - vB < 0.01) {
           root = (-b - discriminant)/(2 * a);
         }


         //The resulting changes in velocity for ball A and B
         QVector2D deltaVA = mR * (vB - root) * collisionVector;
         QVector2D deltaVB = (root - vB) * collisionVector;

         float x1 = deltaVA.x();
         float y1 = deltaVA.y();
         float x2 = deltaVB.x();
         float y2 = deltaVB.y();

         A->changeVX(x1);
         A->changeVY(y1);
         B->changeVX(x2);
         B->changeVY(y2);
    }
};

#endif // PRODUCT_H
