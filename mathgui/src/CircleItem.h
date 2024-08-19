#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include "Interfaces/IGeometryItem.h"
#include "Common/ObjectCounter.h"
#include "circle.h"
#include "PointItem.h"
#include "LineSegmentItem.h"

class CircleItem : public IGeometryItem, public Circle, public ObjectCounter
{
    Q_OBJECT
protected:

    QSharedPointer<PointItem> centerItem;
    QSharedPointer<LineSegmentItem> radiusEditorItem;

public:
    explicit CircleItem(QObject *parent = nullptr);

    void Draw(QPainter& painter) override
    {
        return_if(!show);
        return_if(center.isNull());
        return_if(centerItem.isNull());

        centerItem->Draw(painter);

        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawEllipse(*center, radius, radius);
    }

    bool CursorAbove(QPointF position) override
    {
        double leftExpression = qPow(position.x() - center->x(), 2) + qPow(position.y() - center->y(), 2);
        return leftExpression <= qPow(radius + spread, 2) &&
                leftExpression >= qPow(radius - spread, 2);
    }

    void Scale(double scale) override
    {
        radius *= scale;
    }

    void Move(QPointF vector) override
    {
        *center = *center + vector;
        radiusEditorItem->SetSecondPoint(radiusEditorItem->SecondPoint() + vector);
    }

    void Rotate(double angle) override
    {
        // Либо так и останется пустым, либо в случае, если
        // делать функционал сектора окружности в этом же классе,
        // добавить поворот.

        qDebug() << "angle = " << angle;
    }

    using Circle::SetCenter;
    void SetCenter(QSharedPointer<QPointF> center) override
    {
        this->centerItem->SetPoint(center);
        this->center = center;
    }

    QSharedPointer<PointItem> CenterItemPointer()
    {
        return centerItem;
    }

    void SetRadius(double radius) override
    {
        this->radius = radius;
        radiusEditorItem->SetSecondPoint(center->x() + radius, center->y());
    }

public slots:

    void slotActivated(QAction* action)
    {
        if (action->text() == RADIUS_CHANGE_ACTION)
        {
            RadiusChangeMenuActionClicked();
        }

        //state = ItemState::normal;
    }

protected:

    void InitFigureName() override
    {
        figureName = "circle";
    }

protected slots:

    void RadiusChanged(QPointF)
    {
        radius = radiusEditorItem->Length();
    }

private:

    void RadiusChangeMenuActionClicked()
    {
        radiusEditorItem->Show();
        SetState(ItemState::editing);
    }

};

#endif // CIRCLEITEM_H
