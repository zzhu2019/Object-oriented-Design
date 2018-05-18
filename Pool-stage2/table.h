#ifndef TABLE_H
#define TABLE_H

#include "util.h"
#include "graphic.h"
#include "pocket.h"

class Table : public Graphic
{
public:
	QSize dimension;
	float surface_friction;
    vector<unique_ptr<Pocket>> pockets;

	/**
	 * @brief Constructor for Table
	 *
	 * @param dimension
	 * @param friction
	 */
    Table(const QSize& dimension, float friction, vector<unique_ptr<Pocket>>& pockets)
        : dimension(dimension), surface_friction(friction), pockets(std::move(pockets)){}
	virtual ~Table() {}
};

#endif // TABLE_H
