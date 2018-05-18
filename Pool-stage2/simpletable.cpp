#include "simpletable.h"
#include <QBrush>
#include <QPolygon>

SimpleTable::SimpleTable(const QSize& dim, const QColor& color, float friction, vector<unique_ptr<Pocket>>& pockets)
: Table(dim, friction, pockets), color(color) {}

void SimpleTable::draw(QPainter& painter) const {
	QBrush brush(this->color);
	painter.setBrush(brush);
	painter.drawRect(QRect(QPoint(), this->dimension));
}
