#include "pockettable.h"

PocketTable::PocketTable(unique_ptr<SimpleTable> table,
                         vector<unique_ptr<Pocket>>& pockets, const QSize &dim, float friction, vector<unique_ptr<Pocket>>& pockets1)
                        : Table(dim, friction, pockets1),table(std::move(table)), pockets(std::move(pockets)){}

void PocketTable::draw(QPainter &painter) const
{
    QBrush brush(table->color);
    painter.setBrush(brush);
    painter.drawRect(QRect(QPoint(), table->dimension));
    //draw all the pocket in the vector
    for (const auto& item: pockets) {
        QBrush brush("black");
        painter.setBrush(brush);
        painter.drawEllipse(
                    item->position.toPointF(),
                    item->radius, item->radius);
    }
}
