#ifndef SIMPLECREATOR_H
#define SIMPLECREATOR_H

#include "creator.h"

class SimpleCreator : public Creator
{
protected:
	/**
	 * @brief makes a SimpleTable from JSON config
	 *
	 * @param spec a JSON configuration for the table
	 *
	 * @return a SimpleTable with the specified configuration
	 */
    unique_ptr<Table> makeTable(const QJsonObject &spec, int f=1);
	/**
	 * @brief makes a SimpleBall from the JSON config
	 *
	 * @param spec a JSON configuration for the ball
	 *
	 * @return a SimpleBall with the specified configuration
	 */
    unique_ptr<Ball> makeBall(const QJsonObject &spec, int f=1);
    /**
     * @brief make contained ball, can be in a recursive way
     *
     * @param QJsonObject to get config information from json file
     * @param the colour from its mother ball for default use
     * @param the position from its mother ball
     *
     * @return a contained ball with the specified configuration
     */
    unique_ptr<Ball> makeContainedBall(const QJsonObject &spec, const QColor &colour, const QVector2D &position);

    float tableHeight;
    float tableWidth;
};

#endif // SIMPLECREATOR_H
