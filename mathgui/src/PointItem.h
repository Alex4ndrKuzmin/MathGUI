#ifndef POINTITEM_H
#define POINTITEM_H

#include "Common/ObjectCounter.h"
#include "Interfaces/IGeometryItem.h"
#include "point.h"

class PointItem : public IGeometryItem, public Point, public ObjectCounter
{
    Q_OBJECT
protected:

    bool lastPositionAlwaysInPointFlag = false;

public:
    explicit PointItem(QObject *parent = nullptr);

    using Point::SetPoint;
    void SetPoint(QSharedPointer<QPointF> point) override
    {
        this->point = point;
    }

    void LastPositionAlwaysInPointFlag(bool flag)
    {
        lastPositionAlwaysInPointFlag = flag;
    }

public slots:


protected:

    void InitFigureName() override
    {
        figureName = "point";
    }

    void _Draw(QPainter& painter) override
    {
        return_if(point.isNull());

        painter.setPen(pen);
        painter.setBrush(pen.color());
        painter.drawEllipse(*point, pen.widthF()/2.0, pen.widthF()/2.0);
    }

    bool _CursorAbove(QPointF position) override
    {
        double leftExpression = qPow(position.x() - point->x(), 2) + qPow(position.y() - point->y(), 2);
        return leftExpression <= qPow(3 + spread, 2) &&
                leftExpression >= qPow(3 - spread, 2);
    }

    void _Scale(double, QPointF) override { }

    void _Rotate(double) override { }

    void _Move(QPointF vector) override
    {
        *point = *point + vector;
    }

    void AdditionalMovePressAction(QMouseEvent*) override
    {
        if (lastPositionAlwaysInPointFlag)
            lastPosition = *point;
    }

    void UpdateItemBounds() override
    {
        bounds = QRect(point->x(), point->y(), 0, 0);
    }

signals:

};

#endif // POINTITEM_H
