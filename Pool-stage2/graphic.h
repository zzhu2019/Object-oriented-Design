#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QPainter>

class Graphic {
public:
	/**
	 * @brief an interface for rendering object on Qt
	 *
	 * @param painter for rendering the object
	 */
	virtual void draw(QPainter& painter) const = 0;
};

#endif // GRAPHIC_H
