#ifndef COMPOSITEBALL_H
#define COMPOSITEBALL_H
#include "simpleball.h"


class CompositeBall : public Ball//composite pattern used here
{
public:
    /**
     * @brief constructor for composite ball
     *
     * @param radius for the ball
     * @param mass for the ball
     * @param QVector2D position for the ball
     * @param QVector2D velocity for the ball
     * @param colour for the ball
     * @param strength for the ball
     */
    CompositeBall(float radius, float mass,
                  const QVector2D& pos,
                  const QVector2D& vel,
                  const QColor& color,
                  double strength,
                  vector<unique_ptr<Ball>>& balls, bool isContained);
    /**
     * @brief override the draw method to draw composite ball
     *
     * @param painter for drawing
     */
    void draw(QPainter& painter) const override;
    /**
     * @brief change the position for contained balls inside this ball
     *
     * @param delta position for changing
     */
    void changePforContained(const QVector2D& delta) override;
    /**
     * @brief get the mass for this ball
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
     * @brief get the contained ball's number
     *
     * @return an interger of number
     */
    int getContainedBallNumber() const override;
    /**
     * @brief change the velocity for contained balls inside this ball
     *
     * @param parent's velocity
     * @param after collision gained energy
     * @param the point of collision
     */
    void changeVforContained(
            const QVector2D& ParentVelocity, float energyPerBall, const QVector2D& pointOfCollision) const override;
    /**
     * @brief move the contained balls out into the given vector
     *
     * @param given vector as destination for contained balls
     */
    void moveOut(std::vector<unique_ptr<Ball>>& ballsOnTable) override;
    /**
     * @brief get the colour of this ball
     *
     * @return return the string type of the colour name
     */
    std::string getColour() const override;
private:
    vector<unique_ptr<Ball>> balls;
    QColor color;
    double strength;
};

#endif // COMPOSITEBALL_H
