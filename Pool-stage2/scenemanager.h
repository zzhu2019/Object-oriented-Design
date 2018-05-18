#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "util.h"
#include "graphic.h"
#include "table.h"
#include "ball.h"

#include <QElapsedTimer>
#include <QSize>
#include <QPaintEvent>



class SceneManager : public Graphic
{
public:
	/**
	 * @brief SceneManager Constructor
	 *
	 * @param table
	 * @param balls
	 */
    SceneManager(unique_ptr<Table> table, vector<unique_ptr<Ball>>& balls, bool f=false);
	~SceneManager() {}
	/**
	 * @brief take a timestep of size dtime
	 *
	 * @param dtime
	 */
	void tick(float dtime);
	/**
	 * @brief draw the current scene
	 *
	 * @param painter for rendering objects
	 */
	void draw(QPainter& painter) const;
	/**
	 * @brief retrives the size of the scene
	 *
	 * @return the size of the scene
	 */
	QSize veiwPort() const;
    /**
     * @brief set the cue ball's velocity
     *
     * @param the velocity
     */
    void setCueBallV(QVector2D vel);
    /**
     * @brief set the bool member stage2
     *
     * @param a bool type named f
     */
    void setStage2Bool(bool f);
    /**
     * @brief get the bool flag stage2
     *
     * @return a bool type of stage2
     */
    bool getFlag() const;
    /**
     * @brief reset the ball's velocity to zero, to prevent the ball doesnt stop with a really small vecolity
     */
    void resetBallV();

private:
    unique_ptr<Table> table;
	vector<unique_ptr<Ball>> balls;
	QPoint offset;
    bool stage2;
};

#endif // SCENEMANAGER_H
