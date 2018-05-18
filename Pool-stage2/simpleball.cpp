#include "simpleball.h"
#include <QBrush>
#include <QPen>

SimpleBall::SimpleBall(
	float radius, const QColor& color, float mass,
    const QVector2D& pos, const QVector2D& vel, const double strength, bool contained
) : Ball(radius, mass, pos, vel, contained), strength(strength), color(color) {}

void SimpleBall::draw(QPainter& painter) const {
	QBrush brush(this->color);
	painter.setBrush(brush);
	painter.drawEllipse(
		this->position.toPointF(),
		this->radius, this->radius
	);
}

void SimpleBall::changePforContained(const QVector2D& delta)
{
    qDebug()<<delta<<"it is useless :)";
}

float SimpleBall::getMass() const
{
    return this->mass;
}

double SimpleBall::getStrength() const
{
    return this->strength;
}

int SimpleBall::getContainedBallNumber() const
{
    return 0;
}

void SimpleBall::changeVforContained(
        const QVector2D& ParentVelocity, float energyPerBall, const QVector2D& pointOfCollision) const
{
    qDebug()<<"useless"<<ParentVelocity<<energyPerBall<<pointOfCollision;
}

void SimpleBall::moveOut(std::vector<unique_ptr<Ball>>& ballsOnTable)
{
    qDebug()<<"useless";
}

std::string SimpleBall::getColour() const
{
    return this->color.name().toStdString();
}
