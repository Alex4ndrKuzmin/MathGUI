#ifndef LINESEGMENT_H
#define LINESEGMENT_H
#include <QPointF>
#include <QPoint>
#include <QSharedPointer>
#include <QtMath>

class LineSegment
{

protected:

    QSharedPointer<QPointF> point1;
    QSharedPointer<QPointF> point2;

public:
    LineSegment();

    void SetFirstPoint(const QPointF& point)
    {
        this->point1->setX(point.x());
        this->point1->setY(point.y());
    }

    void SetSecondPoint(const QPointF& point)
    {
        this->point2->setX(point.x());
        this->point2->setY(point.y());
    }

    void SetFirstPoint(double x, double y)
    {
        this->point1->setX(x);
        this->point1->setY(y);
    }

    void SetSecondPoint(double x, double y)
    {
        this->point2->setX(x);
        this->point2->setY(y);
    }

    virtual void SetFirstPoint(QSharedPointer<QPointF> point)
    {
        this->point1 = point;
    }

    virtual void SetSecondPoint(QSharedPointer<QPointF> point)
    {
        this->point2 = point;
    }

    QSharedPointer<QPointF> FirstPointPointer()
    {
        return point1;
    }

    QSharedPointer<QPointF> SecondPointPointer()
    {
        return point2;
    }

    QPointF FirstPoint()
    {
        return *point1;
    }

    QPointF SecondPoint()
    {
        return *point2;
    }

    double Length()
    {
        return sqrt(qPow(point1->x() - point2->x(), 2) + qPow(point1->y() - point2->y(), 2));
    }
};

#endif // LINESEGMENT_H
