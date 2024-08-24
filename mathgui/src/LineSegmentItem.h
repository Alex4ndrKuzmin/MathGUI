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
    Q_OBJECT
protected:

    QSharedPointer<PointItem> pointItem1;
    QSharedPointer<PointItem> pointItem2;

    bool lockFirstPointFlag = false;
    bool lockSecondPointFlag = false;
    bool lockLengthFlag = false;

    double lockedLength = 0;

public:
    explicit LineSegmentItem(QObject *parent = nullptr);
    ~LineSegmentItem() {};

    void Hide() override
    {
        show = false;
        pointItem1->Hide();
        pointItem2->Hide();
    }

    void Show() override
    {
        show = true;
        pointItem1->Show();
        pointItem2->Show();
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

    void BindPoints()
    {
        connect(pointItem1.get(), SIGNAL(Moved_signal(QPointF)), this, SLOT(FirstPointMoved(QPointF)));
        connect(pointItem2.get(), SIGNAL(Moved_signal(QPointF)), this, SLOT(SecondPointMoved(QPointF)));
    }

    void UntiePoints()
    {
        disconnect(pointItem1.get(), SIGNAL(Moved_signal(QPointF)), this, SLOT(FirstPointMoved(QPointF)));
        disconnect(pointItem2.get(), SIGNAL(Moved_signal(QPointF)), this, SLOT(SecondPointMoved(QPointF)));
    }

    void LockFirstPoint()
    {
        lockFirstPointFlag = true;
    }

    void UnlockFirstPoint()
    {
        lockFirstPointFlag = false;
    }

    void LockSecondPoint()
    {
        lockSecondPointFlag = true;
    }

    void UnlockSecondPoint()
    {
        lockSecondPointFlag = false;
    }

    void LockLength()
    {
        lockLengthFlag = true;
        lockedLength = Length();
        pointItem1->LastPositionAlwaysInPointFlag(true);
        pointItem2->LastPositionAlwaysInPointFlag(true);
        connect(pointItem1.get(), SIGNAL(Moved_signal(QPointF)), this, SLOT(FirstPointMoved(QPointF)));
        connect(pointItem2.get(), SIGNAL(Moved_signal(QPointF)), this, SLOT(SecondPointMoved(QPointF)));
    }

    void UnlockLength()
    {
        lockLengthFlag = false;
        lockedLength = 0;
        pointItem1->LastPositionAlwaysInPointFlag(false);
        pointItem2->LastPositionAlwaysInPointFlag(false);
        disconnect(pointItem1.get(), SIGNAL(Moved_signal(QPointF)), this, SLOT(FirstPointMoved(QPointF)));
        disconnect(pointItem2.get(), SIGNAL(Moved_signal(QPointF)), this, SLOT(SecondPointMoved(QPointF)));
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

    void _Draw(QPainter& painter) override
    {
        return_if(point1.isNull());
        return_if(point2.isNull());
        return_if(pointItem1.isNull());
        return_if(pointItem1.isNull());

        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawLine(*point1, *point2);

        pointItem1->Draw(painter);
        pointItem2->Draw(painter);
    }

    bool _CursorAbove(QPointF position) override
    {
        return show ? IsPointOnSegment(position) : false;
    }

    void _Scale(double scale, QPointF scalingPoint) override
    {
        return_if(!show);
        *point1 = (*point1 - scalingPoint) * scale + scalingPoint;
        *point2 = (*point2 - scalingPoint) * scale + scalingPoint;
    }

    void _Move(QPointF vector) override
    {
        return_if(!show);

        if (!lockFirstPointFlag)
            *point1 = *point1 + vector;

        if (!lockSecondPointFlag)
            *point2 = *point2 + vector;
    }

    void _Rotate(double angle) override
    {
        return_if(!show);
        // Либо так и останется пустым, либо в случае, если
        // делать функционал сектора окружности в этом же классе,
        // добавить поворот.

        qDebug() << "angle = " << angle;
    }

    void UpdateItemBounds() override
    {
        double minX = qMin(point1->x(), point2->x());
        double minY = qMin(point1->y(), point2->y());
        double maxX = qMax(point1->x(), point2->x());
        double maxY = qMax(point1->y(), point2->y());
        bounds = QRect(minX, minY, maxX - minX, maxY - minY);
    }

protected slots:

    void FirstPointMoved(QPointF vector)
    {
        if (lockLengthFlag)
        {
            if (Length() == 0)
            {
                *point1 = *point1 - vector;
                return;
            }

            QPointF oldPosition = *point1 - vector;
            double oldLength = QLineF(*point2, oldPosition).length();
            *point1 = *point2 - (*point2 - *point1) / Length() * oldLength;
            return;
        }

        pointItem2->SetPoint(pointItem2->GetPoint() + vector);
    }

    void SecondPointMoved(QPointF vector)
    {
        if (lockLengthFlag)
        {
            if (Length() == 0)
            {
                *point2 = *point2 - vector;
                return;
            }

            QPointF oldPosition = *point2 - vector;
            double oldLength = QLineF(*point1, oldPosition).length();
            *point2 = *point1 - (*point1 - *point2) / Length() * oldLength;
            return;
        }

        pointItem1->SetPoint(pointItem1->GetPoint() + vector);
    }



};

#endif // LINESEGMENTITEM_H
