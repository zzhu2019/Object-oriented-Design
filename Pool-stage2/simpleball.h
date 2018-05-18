#ifndef SIMPLEBALL_H
#define SIMPLEBALL_H

#include "ball.h"
#include <QColor>

class SimpleBall : public Ball
{
public:
	/**
	 * @brief SimpleBall Constructor
	 *
	 * @param radius
	 * @param color
	 * @param mass : use 0 for infinite mass
	 * @param position
	 * @param velocity
	 */
	SimpleBall(
        float radius = 10, const QColor& color = QColor(255, 255, 255),//the default color for contained balls should be that of their parent balls
        float mass = 1.0,
        const QVector2D& position = QVector2D(0, 0),
        const QVector2D& velocity = QVector2D(0, 0),
        const double strength = std::numeric_limits<double>::max(), bool isContained=false
	);
	/**
	 * @brief Draws the ball onto the scene
	 *
	 * @param painter for rendering the ball
	 */
    void draw(QPainter& painter) const override;
    /**
     * @brief change the position for contained balls. Inherited from base class, if no contained ball, then do nothing.
     *
     * @param delta position
     */
    void changePforContained(const QVector2D& delta) override;
    /**
     * @brief get the mass of the ball
     *
     * @return a float type of mass
     */
    float getMass() const override;
    /**
     * @brief get the strength of the ball
     *
     * @return a double type of strength
     */
    double getStrength() const override;
    /**
     * @brief get the number of conatined ball
     *
     * @return return the integer of ball number
     */
    int getContainedBallNumber() const override;
    /**
     * @brief change the velocity for contained ball, inherited from base class, return 0 here
     *
     * @param parent's velocity
     * @param engergy gained by collison
     * @param the point of collision
     */
    void changeVforContained(
            const QVector2D& ParentVelocity, float energyPerBall, const QVector2D& pointOfCollision) const override;
    /**
     * @brief move the contained balls out into given vector, inherited from base calss, do nothing here
     *
     * @param the given vector for new balls
     */
    void moveOut(std::vector<unique_ptr<Ball>>& ballsOnTable) override;
    /**
     * @brief get the colour of this ball
     *
     * @return a string type of name of the colour
     */
    std::string getColour() const override;
private:
    double strength;// to be done
	QColor color;
};

#endif // SIMPLEBALL_H
