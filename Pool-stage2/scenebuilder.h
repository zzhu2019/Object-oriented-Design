#ifndef SCENEBUILDER_H
#define SCENEBUILDER_H

#include "scenemanager.h"

class SceneBuilder
{
public:
	/**
	 * @brief Constructor
	 */
	SceneBuilder() {}
	~SceneBuilder() {}

	/**
	 * @brief sets the table for the scene
	 *        table can only be used once
	 *
	 * @param table
	 */
    void setTable(unique_ptr<Table> table);//add table
	/**
	 * @brief adds ball to scene
	 *        ball can only be used once
	 *
	 * @param ball
	 */
	void addBall(unique_ptr<Ball> ball);
	/**
	 * @brief remove all balls from scene
	 */
	void resetBalls();
	/**
     * @brief creates scene,
     *        a table and balls must be set
	 *
	 * @return the scene with set table and balls
	 */
    unique_ptr<SceneManager> build();
    /**
     * @brief set the stage flag of this table: it is a stage 2 table or not
     *
     * @param a boolean type of f
     */
    void setStageFlag(bool f);

private:
	unique_ptr<Table> table;
    vector<unique_ptr<Ball>> balls;
    bool stage2;
};

#endif // SCENEBUILDER_H
