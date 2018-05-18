#ifndef POCKETTABLE_H
#define POCKETTABLE_H

#include "simpletable.h"
#include "pocket.h"


class PocketTable : public Table//the decorator design pattern used here
{
public:
    /**
     * @brief constructor for table with pockets implemented by the decorator pattern
     *
     * @param a point of table
     * @param a vector of pockets
     * @param a QSize type of dimension
     * @param a float type of friction
     * @param a copy of vector of pockets for the base class table
     */
    PocketTable(unique_ptr<SimpleTable> table, vector<unique_ptr<Pocket>>& pockets, const QSize& dim, float friction, vector<unique_ptr<Pocket>>& pockets1);
    /**
     * @brief draw method for table with pocket
     *
     * @param painter
     */
    void draw(QPainter& painter) const;
    vector<unique_ptr<Pocket>> pockets;
private:
    unique_ptr<SimpleTable> table;
};

#endif // POCKETTABLE_H
