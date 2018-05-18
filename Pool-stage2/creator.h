#ifndef CREATOR_H
#define CREATOR_H

#include "scenemanager.h"
#include <QJsonObject>

class Creator
{
public:
	/**
	 * @brief used for initialising a SceneManager from a JSON configuration
	 *
	 * @param spec a JSON object detailing the initial property of the scene
	 *        including a table and balls
	 *
	 * @return a SceneManager with the specified properties
	 */
	unique_ptr<SceneManager> makeScene(const QJsonObject& spec);
protected:
	/**
	 * @brief makes a (concrete) Table from JSON config
	 *        implemented by subclass
	 *
	 * @param spec a JSON object detailing the properties of the table
	 *
	 * @return a Table with the specified property
	 */
    virtual unique_ptr<Table> makeTable(const QJsonObject& spec, int f=1) = 0;
	/**
	 * @brief makes a (concrete) Ball from JSON config
	 *        implemented by subclass
	 *
	 * @param spec a JSON object detailing the properties of the ball
	 *
	 * @return a Ball with the specified property
	 */
    virtual unique_ptr<Ball> makeBall(const QJsonObject& spec, int f=1) = 0;
};

#endif // CREATOR_H
