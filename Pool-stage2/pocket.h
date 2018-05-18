#ifndef POCKET_H
#define POCKET_H

#include "util.h"
#include "graphic.h"
#include <QVector2D>


class Pocket
{
public:
    float radius;
    QVector2D position;
    /**
     * @brief constructor for pocket
     *
     * @param position of the pocket
     * @param redius of the pocket
     */
    Pocket(const QVector2D& pos = NULL_2D
            ,float radius = 15);
};

#endif // POCKET_H
