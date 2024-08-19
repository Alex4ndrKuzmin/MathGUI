#ifndef ABSTRACTPOINT_H
#define ABSTRACTPOINT_H
#include <QPointF>
#include <QSharedPointer>

class AbstractRealPoint
{
protected:

    QSharedPointer<QPointF> point = nullptr;

public:
    AbstractRealPoint();

    void SetPointer(QPointF* center)
    {
        this->point = QSharedPointer<QPointF>(center);
    }

    void SetPoint(const QPointF& center)
    {
        this->point->setX(center.x());
        this->point->setY(center.y());
    }

    void SetPoint(double x, double y)
    {
        this->point->setX(x);
        this->point->setY(y);
    }

    void ResetPoint()
    {
        point.reset();
    }

    void ResetPoint(QPointF* newPointer)
    {
        point.reset();
    }
};

#endif // ABSTRACTPOINT_H
