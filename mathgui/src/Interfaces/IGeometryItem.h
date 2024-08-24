#ifndef IGEOMETRYITEM_H
#define IGEOMETRYITEM_H

#define RADIUS_CHANGE_ACTION "Изменить радиус"

#include <QObject>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QPointF>
#include <QSharedPointer>
#include <QtMath>
#include <QDebug>
#include <QMenu>

#include "IGraphicLine.h"

///
/// \brief Интерфейс для классов двумерных геометрических объектов
///
class IGeometryItem : public IGraphicLine
{
    Q_OBJECT
private:


protected:

    QVector<QSharedPointer<IGeometryItem>> childItems;

    QString figureName = "";
    QString objectName = "";

    QRectF bounds;

    bool cursorAbove = false;
    bool editing = false;

    QSharedPointer<QMenu> menu;

    QPointF lastPosition = QPointF(0, 0);

public:
    explicit IGeometryItem(QObject *parent = nullptr);

    QVector<QSharedPointer<IGeometryItem>> ChildItems()
    {
        return childItems;
    }

    void AddChildItem(QSharedPointer<IGeometryItem> item)
    {
        childItems.append(item);
    }

    virtual void SetCursorAboveFlag(bool flag)
    {
        cursorAbove = flag;
    }

    virtual bool CursorAboveFlag()
    {
        return cursorAbove;
    }

    virtual void SetEditingFlag(bool flag)
    {
        editing = flag;
    }

    virtual bool EditingFlag()
    {
        return editing;
    }

    //TODO: Переместить в отдельный файл
    QRectF ExtendRect(QRectF rect, double extend)
    {
        return QRectF(rect.left() - extend,
                        rect.top() - extend,
                        rect.width() + 2*extend,
                        rect.height() + 2*extend);
    }

    bool CursorAbove(QPointF position)
    {
        return show ? _CursorAbove(position) : false;
    }

    void Scale(double scale, QPointF scalingPoint = QPointF(0, 0))
    {
        return_if(!show);
        _Scale(scale, scalingPoint);
        UpdateItemBounds();
        emit Scaled_signal(scale);
    }

    void Rotate(double angle)
    {
        return_if(!show);
        _Rotate(angle);
        UpdateItemBounds();
        emit Rotated_signal(angle);
    }

    void Move(QPointF vector)
    {
        return_if(!show);
        _Move(vector);
        UpdateItemBounds();
        emit Moved_signal(vector);
    }

protected:

    virtual void InitFigureName() = 0;
    virtual void UpdateItemBounds() = 0;
    virtual bool _CursorAbove(QPointF position) = 0;
    virtual void _Scale(double scale, QPointF scalingPoint) = 0;
    virtual void _Rotate(double angle) = 0;
    virtual void _Move(QPointF vector) = 0;

    // Эти методы стоит переопределять, если в производном классе
    // требуется как-либо дополнительно обработать соответствующее действие

    virtual void AdditionalMousePressAction(QMouseEvent*) {};
    virtual void AdditionalMovePressAction(QMouseEvent*) {};
    virtual void AdditionalReleasePressAction(QMouseEvent*) {};

signals:

    void Scaled_signal(double scale);
    void Rotated_signal(double angle);
    void Moved_signal(QPointF vector);

public slots:

    virtual void MousePressEvent(QMouseEvent* event)
    {
        switch (event->button())
        {
        case Qt::MouseButton::LeftButton:
        {
            if (state == ItemState::cursorAbove)
            {
                SetState(ItemState::hooked);
            }

            break;
        }
        default:
            break;
        }
        AdditionalMousePressAction(event);
    }



    virtual void MouseMoveEvent(QMouseEvent* event)
    {
        if (state == ItemState::hooked)
        {
            // Объект захвачен мышкой -> перемещаем вслед за курсором
            Move(event->pos() - lastPosition);
        }

        else
        {
            SetState( cursorAbove ?
                      ItemState::cursorAbove :
                      ItemState::normal );
        }
        lastPosition = event->pos();
        AdditionalMovePressAction(event);
    }

    virtual void MouseReleaseEvent(QMouseEvent* event)
    {
        switch (event->button())
        {
        case Qt::MouseButton::LeftButton:
        {
            if (state == ItemState::hooked)
            {
                SetState(ItemState::cursorAbove);
            }
            break;
        }
        default:
            break;
        }
        AdditionalReleasePressAction(event);
    }

    virtual void ContextMenuEvent(QContextMenuEvent* pe)
    {
        if (state == ItemState::cursorAbove)
        {
            menu->exec(pe->globalPos());
        }
    }
};

#endif // IGEOMETRYITEM_H
