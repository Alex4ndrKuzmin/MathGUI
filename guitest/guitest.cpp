#include <QtWidgets>
#include <QApplication>
#include <QLabel>

#include "Canvas.h"
#include "CircleItem.h"
#include "PointItem.h"
#include "LineSegmentItem.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Canvas canvas;
    canvas.show();

    QSharedPointer<CircleItem> circle(new CircleItem(&canvas));
    circle->SetCenter(50, 50);
    circle->SetRadius(25);
    canvas.AddGeometryItem(circle);

    //QSharedPointer<CircleItem> circle2(new CircleItem(&canvas));
    //circle2->SetCenter(circle->CenterPointer()/*50, 50*/);
    //circle2->SetRadius(50);
    //circle2->CenterItemPointer()->Hide();
    //canvas.AddGeometryItem(circle2);

    //QSharedPointer<PointItem> point(new PointItem(&canvas));
    //point->SetPoint(100, 100);
    //canvas.AddGeometryItem(point);

    //QVector<QSharedPointer<PointItem>> points;
    //for (int i = 0; i < 100; i++)
    //{
    //    auto pnt = QSharedPointer<PointItem>(new PointItem(&canvas));
    //    points.append(pnt);
    //    pnt->SetPoint(200 + i*2, 200 + i*2);
    //    canvas.AddGeometryItem(pnt);
    //}

    QPolygonF poly = QPolygonF({QPointF(0,0), QPointF(1,1), QPointF(1,0)});
    QPolygonF poly2 = QPolygonF({QPointF(0,0), QPointF(0,1), QPointF(1,0)});

    QPolygonF poly3 = poly.intersected(poly2);

    //QSharedPointer<LineSegmentItem> segment(new LineSegmentItem(&canvas));
    //segment->SetFirstPoint(20, 100);
    //segment->SetSecondPoint(40, 120);
    //canvas.AddGeometryItem(segment);

    return app.exec();
}
