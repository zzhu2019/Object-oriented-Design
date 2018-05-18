#include "compositeball.h"
#include "math.h"

CompositeBall::CompositeBall(float radius, float mass,
                             const QVector2D& pos,
                             const QVector2D& vel,
                             const QColor& color,
                             double strength,
                             vector<unique_ptr<Ball>>& balls, bool contained)
    : Ball(radius, mass, pos, vel, contained), balls(std::move(balls)),
      color(color), strength(strength){}

void CompositeBall::draw(QPainter &painter) const
{
    bool visibility = false;//the visibility of conatined ball toggle
    QBrush brush(this->color);
    painter.setBrush(brush);
    painter.drawEllipse(
        this->position.toPointF(),
        this->radius, this->radius
    );

    if(visibility == true)
    {
        for (const auto& item: this->balls) {
            item->draw(painter);
        }
    }
}

void CompositeBall::changePforContained(const QVector2D& delta)
{
    for (auto a = this->balls.begin(); a != this->balls.end(); ++a)
    {
        Ball& ballA = **a;
        ballA.position+=delta;
        if(ballA.isContained)
        {
            ballA.changePforContained(delta);
        }
    }
}

float CompositeBall::getMass() const
{
    float m=this->mass;
    for (auto a = this->balls.begin(); a != this->balls.end(); ++a)
    {
        Ball& ballA = **a;
        if(ballA.isContained)
        {
            m+=ballA.getMass();
        }
        else
        {
            m+=ballA.mass;
        }
    }
    return m;
}

double CompositeBall::getStrength() const
{
    return this->strength;
}

int CompositeBall::getContainedBallNumber() const
{
    return int(this->balls.size());
}

void CompositeBall::changeVforContained(
        const QVector2D& ParentVelocity, float energyPerBall, const QVector2D& pointOfCollision) const
{
    for (auto a = this->balls.begin(); a != this->balls.end(); ++a)
    {
        Ball& ballA = **a;
        QVector2D componentBallVelocity = ParentVelocity + sqrt(energyPerBall/ballA.mass)*
            (ballA.position-pointOfCollision).normalized();// right?
        ballA.velocity.setX(componentBallVelocity.x());
        ballA.velocity.setY(componentBallVelocity.y());
    }
}

void CompositeBall::moveOut(std::vector<unique_ptr<Ball>>& ballsOnTable)
{
    while(this->balls.size())
    {
        unique_ptr<Ball> t(std::move(this->balls.back()));
        qDebug()<<"add a ball";
        ballsOnTable.emplace(ballsOnTable.end(), std::move(t));
        //for the conatined in the broken ball, add them
        this->balls.pop_back();
    }
}

std::string CompositeBall::getColour() const
{
    return this->color.name().toStdString();
}
