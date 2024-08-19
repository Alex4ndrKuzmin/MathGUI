#ifndef POINTITEM_H
#define POINTITEM_H

#include "Common/ObjectCounter.h"
#include "Interfaces/IGeometryItem.h"
#include "point.h"

class PointItem : public IGeometryItem, public Point, public ObjectCounter
{
    Q_OBJECT

public:
    explicit PointItem(QObject *parent = nullptr);

    void Draw(QPainter& painter) override
    {
        return_if(!show);
        return_if(point.isNull());

        painter.setPen(pen);
        painter.setBrush(pen.color());
        painter.drawEllipse(*point, pen.widthF()/2.0, pen.widthF()/2.0);
    }

    bool CursorAbove(QPointF position) override
    {
        double leftExpression = qPow(position.x() - point->x(), 2) + qPow(position.y() - point->y(), 2);
        return leftExpression <= qPow(3 + spread, 2) &&
                leftExpression >= qPow(3 - spread, 2);
    }

    void Scale(double scale) override { }

    void Rotate(double angle) override { }

    void Move(QPointF vector) override
    {
        *point = *point + vector;

        emit Moved_signal(vector);
    }

    using Point::SetPoint;
    void SetPoint(QSharedPointer<QPointF> point) override
    {
        this->point = point;
    }

public slots:


protected:

    void InitFigureName() override
    {
        figureName = "point";
    }

signals:

};

#endif // POINTITEM_H
