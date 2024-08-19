#ifndef POINT_H
#define POINT_H

#include <QSharedPointer>
#include <QPointF>

class Point
{
protected:

    QSharedPointer<QPointF> point;

public:
    Point();

    void SetPoint(const QPointF& point)
    {
        this->point->setX(point.x());
        this->point->setY(point.y());
    }

    void SetPoint(double x, double y)
    {
        this->point->setX(x);
        this->point->setY(y);
    }

    virtual void SetPoint(QSharedPointer<QPointF> point)
    {
        this->point = point;
    }

    QPointF GetPoint()
    {
        return *point;
    }

    QSharedPointer<QPointF> PointPointer()
    {
        return point;
    }
};

#endif // POINT_H
