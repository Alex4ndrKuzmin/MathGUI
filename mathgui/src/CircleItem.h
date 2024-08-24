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

    using Circle::SetCenter;
    void SetCenter(QSharedPointer<QPointF> center) override
    {
        this->centerItem->SetPoint(center);
        this->center = center;
        UpdateItemBounds();
    }

    QSharedPointer<PointItem> CenterItemPointer()
    {
        return centerItem;
    }

    void SetRadius(double radius) override
    {
        this->radius = radius;
        this->radiusEditorItem->SetSecondPoint(*center + QPointF(radius, 0));
        UpdateItemBounds();
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

    void _Draw(QPainter& painter) override
    {
        return_if(center.isNull());
        return_if(centerItem.isNull());

        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawEllipse(*center, radius, radius);

        centerItem->Draw(painter);
        radiusEditorItem->Draw(painter);
    }

    bool _CursorAbove(QPointF position) override
    {
        double leftExpression = qPow(position.x() - center->x(), 2) + qPow(position.y() - center->y(), 2);
        return leftExpression <= qPow(radius + spread, 2) &&
                leftExpression >= qPow(radius - spread, 2);
    }

    void _Scale(double scale, QPointF) override
    {
        radius *= scale;
    }

    void _Move(QPointF vector) override
    {
        *center = *center + vector;
        radiusEditorItem->SetSecondPoint(radiusEditorItem->SecondPoint() + vector);
    }

    void _Rotate(double angle) override
    {
        // Либо так и останется пустым, либо в случае, если
        // делать функционал сектора окружности в этом же классе,
        // добавить поворот.

        qDebug() << "angle = " << angle;
    }

    void AdditionalMousePressAction(QMouseEvent* event) override
    {
        qDebug() << "Click position: " << event->pos();
        qDebug() << "Extended rect: " << ExtendRect(bounds, 5);
        if (EditingFlag() && !ExtendRect(bounds, 5).contains(event->pos()))
        {
            centerItem->Show();
            radiusEditorItem->Hide();
            disconnect(radiusEditorItem->FirstPointItem().get(),
                    SIGNAL(Moved_signal(QPointF)),
                    radiusEditorItem.get(),
                    SLOT(FirstPointMoved(QPointF)));
            SetEditingFlag(false);
        }
    }

    void UpdateItemBounds() override
    {
        bounds = QRect(center->x() - radius, center->y() - radius, 2*radius, 2*radius);;
        qDebug() << bounds;
    }

protected slots:

    void RadiusChanged(QPointF)
    {
        radius = radiusEditorItem->Length();
        UpdateItemBounds();
    }

    void RadiusEditorItemMoved(QPointF)
    {
        UpdateItemBounds();
    }

private:

    void RadiusChangeMenuActionClicked()
    {
        radiusEditorItem->SetSecondPoint(center->x() + radius, center->y());

        centerItem->Hide();
        radiusEditorItem->Show();
        connect(radiusEditorItem->FirstPointItem().get(),
                SIGNAL(Moved_signal(QPointF)),
                radiusEditorItem.get(),
                SLOT(FirstPointMoved(QPointF)));
        SetEditingFlag(true);
    }

};

#endif // CIRCLEITEM_H
