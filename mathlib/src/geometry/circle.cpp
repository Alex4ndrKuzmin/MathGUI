#include "circle.h"

Circle::Circle()
{
    center = QSharedPointer<QPointF>(new QPointF(0, 0));
}
