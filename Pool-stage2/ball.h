#ifndef BALL_H
#define BALL_H

#include "util.h"
#include "graphic.h"
#include <QVector2D>

/**
 * @brief The Ball class is not responsible for physics calculation
 *        it exposes public radius position, velocity and mass fields
 *        so the responsible class can access them directly.
 *        You can pretend it's a struct if you like.
 */
class Ball : public Graphic
{
public:
    bool isContained;
	float radius;
	float mass;
	QVector2D position;
	QVector2D velocity;
    bool isRemove;
	/**
	 * @brief Constructor for ball
	 *
	 * @param radius used for collision detection
	 * @param mass used for physics
	 * @param pos initial poisiton for the ball
	 * @param vel inital velocity for the ball
	 */
	Ball(
		float radius = 0, float mass = 0,
		const QVector2D& pos = NULL_2D,
        const QVector2D& vel = NULL_2D, bool contained = false, bool isRemove = false
    ) : isContained(contained), radius(radius), mass(mass), position(pos), velocity(vel), isRemove(isRemove) {}
	virtual ~Ball() {}
    /**
     * @brief change the position for the contained ball inside this ball, it is virtual and need to be overridden
     *
     * @param a QVector type carries the delta for position change
     */
    virtual void changePforContained(const QVector2D& delta) = 0;
    /**
     * @brief get the mass of the ball, virtual and need to be overridden
     *
     * @return a float type of mass
     */
    virtual float getMass() const = 0;
    /**
     * @brief get the stregnth of the ball, virtual and need to be overridden
     *
     * @return a double type of strength
     */
    virtual double getStrength() const = 0;
    /**
     * @brief get the number of contained balls inside this ball, is virtual and need to be overridden
     *
     * @return an interger of contained balls' number
     */
    virtual int getContainedBallNumber() const = 0;
    /**
     * @brief change the velocity for contained balls inside this ball, is virtual and need to be overridden
     *
     * @param a QVector2D of parent's velocity
     * @param a float of each ball's energy
     * @param a QVector2D of the collision's point
     */
    virtual void changeVforContained(
        const QVector2D& ParentVelocity, float energyPerBall, const QVector2D& pointOfCollision) const = 0;
    /**
     * @brief move the contained balls out into the input vector parameter, is virtual and need to be overridden
     *
     * @param a vector for balls on the table currently
     */
    virtual void moveOut(std::vector<unique_ptr<Ball>>& ballsOnTable) = 0;// to be done: use virtual rather than pure virtual
    /**
     * @brief get the colour of the ball, is virtual and need to be overridden
     *
     * @return a string of the name of this colour
     */
    virtual std::string getColour() const = 0;
};

#endif // BALL_H
