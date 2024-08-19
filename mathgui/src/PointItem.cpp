#include "PointItem.h"

PointItem::PointItem(QObject *parent)
    : IGeometryItem{parent}
{
    point = QSharedPointer<QPointF>(new QPointF(0, 0));
}
