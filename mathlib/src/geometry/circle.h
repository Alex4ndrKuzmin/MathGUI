#ifndef CIRCLE_H
#define CIRCLE_H
#include <QPointF>
#include <QPoint>
#include <QSharedPointer>
#include <QtMath>

class Circle
{
protected:

    double radius = 0;
    QSharedPointer<QPointF> center;

public:
    Circle();

    void SetCenter(const QPointF& center)
    {
        this->center->setX(center.x());
        this->center->setY(center.y());
    }

    void SetCenter(double x, double y)
    {
        this->center->setX(x);
        this->center->setY(y);
    }

    virtual void SetCenter(QSharedPointer<QPointF> center)
    {
        this->center = center;
    }

    virtual void SetRadius(double radius)
    {
        this->radius = radius;
    }

    QSharedPointer<QPointF> CenterPointer()
    {
        return center;
    }

    double Area()
    {
        return M_PI * radius * radius;
    }

    double Length()
    {
        return 2.0 * M_PI * radius;
    }
};

#endif // CIRCLE_H
