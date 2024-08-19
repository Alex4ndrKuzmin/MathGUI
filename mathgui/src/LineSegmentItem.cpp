#include "LineSegmentItem.h"

LineSegmentItem::LineSegmentItem(QObject *parent)
    : IGeometryItem{parent}
{
    pointItem1 = QSharedPointer<PointItem>(new PointItem());
    pointItem2 = QSharedPointer<PointItem>(new PointItem());

    pointItem1->SetPoint(point1);
    pointItem2->SetPoint(point2);

    AddChildItem(pointItem1);
    AddChildItem(pointItem2);

    this->spread = 3;
}

