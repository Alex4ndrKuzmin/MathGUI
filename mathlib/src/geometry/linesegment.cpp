#include "linesegment.h"

LineSegment::LineSegment()
{
    point1 = QSharedPointer<QPointF>(new QPointF());
    point2 = QSharedPointer<QPointF>(new QPointF());
}
