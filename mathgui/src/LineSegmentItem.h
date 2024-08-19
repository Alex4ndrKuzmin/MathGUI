#ifndef LINESEGMENTITEM_H
#define LINESEGMENTITEM_H

#include <QLineF>
#include <QPointF>

#include "Interfaces/IGeometryItem.h"
#include "geometry/linesegment.h"
#include "PointItem.h"
#include "linesegment.h"

class LineSegmentItem : public IGeometryItem, public LineSegment, public ObjectCounter
{
protected:

    QSharedPointer<PointItem> pointItem1;
    QSharedPointer<PointItem> pointItem2;

public:
    explicit LineSegmentItem(QObject *parent = nullptr);

    void Draw(QPainter& painter) override
    {
        return_if(!show);
        return_if(point1.isNull());
        return_if(point2.isNull());
        return_if(pointItem1.isNull());
        return_if(pointItem1.isNull());

        pointItem1->Draw(painter);
        pointItem2->Draw(painter);

        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawLine(*point1, *point2);
    }

    bool CursorAbove(QPointF position) override
    {
        return IsPointOnSegment(position);
    }

    void Scale(double scale) override
    {
        //radius *= scale;
    }

    void Move(QPointF vector) override
    {
        *point1 = *point1 + vector;
        *point2 = *point2 + vector;

        //bounds.setTopLeft(bounds.topLeft() + vector);
    }

    void Rotate(double angle) override
    {
        // Либо так и останется пустым, либо в случае, если
        // делать функционал сектора окружности в этом же классе,
        // добавить поворот.

        qDebug() << "angle = " << angle;
    }

    using LineSegment::SetFirstPoint;
    void SetFirstPoint(QSharedPointer<QPointF> point) override
    {
        this->point1 = point;
        this->pointItem1->SetPoint(point);
    }

    using LineSegment::SetSecondPoint;
    void SetSecondPoint(QSharedPointer<QPointF> point) override
    {
        this->point2 = point;
        this->pointItem2->SetPoint(point);
    }

    QSharedPointer<PointItem> FirstPointItem()
    {
        return pointItem1;
    }

    QSharedPointer<PointItem> SecondPointItem()
    {
        return pointItem2;
    }

    bool IsPointOnSegment(QPointF& point)
    {
        double x1 = this->FirstPoint().x();
        double y1 = this->FirstPoint().y();

        double x2 = this->SecondPoint().x();
        double y2 = this->SecondPoint().y();

        double x = point.x();
        double y = point.y();

        return IsPointOnSegment(x1, y1, x2, y2, x, y, spread);
    }

    static bool IsPointOnSegment(LineSegment& lineSegment, QPointF& point, double spread = 3)
    {
        double x1 = lineSegment.FirstPoint().x();
        double y1 = lineSegment.FirstPoint().y();

        double x2 = lineSegment.SecondPoint().x();
        double y2 = lineSegment.SecondPoint().y();

        double x = point.x();
        double y = point.y();

        return IsPointOnSegment(x1, y1, x2, y2, x, y, spread);
    }

    static bool IsPointOnSegment(double x1, double y1, double x2, double y2, double x, double y, double spread = 3)
    {
        return DistancePointToSegment(x1, y1, x2, y2, x, y) <= spread;
    }

    double DistancePointToSegment(QPointF& point)
    {
        double x1 = this->FirstPoint().x();
        double y1 = this->FirstPoint().y();

        double x2 = this->SecondPoint().x();
        double y2 = this->SecondPoint().y();

        double x = point.x();
        double y = point.y();

        return DistancePointToSegment(x1, y1, x2, y2, x, y);
    }

    static double DistancePointToSegment(LineSegment& lineSegment, QPointF& point)
    {
        double x1 = lineSegment.FirstPoint().x();
        double y1 = lineSegment.FirstPoint().y();

        double x2 = lineSegment.SecondPoint().x();
        double y2 = lineSegment.SecondPoint().y();

        double x = point.x();
        double y = point.y();

        return DistancePointToSegment(x1, y1, x2, y2, x, y);
    }

    static double DistancePointToSegment(double x1, double y1, double x2, double y2, double x, double y)
    {
        double dx = x2 - x1;
        double dy = y2 - y1;

        if (dx == 0 && dy == 0)
        {
            return std::hypot(x - x1, y - y1);
        }

        double t = ((x - x1) * dx + (y - y1) * dy) / (dx * dx + dy * dy);
        t = qBound(0.0, t, 1.0);

        double projX = x1 + t * dx;
        double projY = y1 + t * dy;

        return std::hypot(x - projX, y - projY);
    }

protected:

    void InitFigureName() override
    {
        figureName = "line_segment";
    }
};

#endif // LINESEGMENTITEM_H
