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

    QPoint lastPosition = QPoint(-1, -1);

protected:

    QVector<QSharedPointer<IGeometryItem>> childItems;

    bool show = true;

    QString figureName = "";
    QString objectName = "";

    QRectF bounds;

    bool cursorAbove = false;

    QSharedPointer<QMenu> menu;

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

    virtual void Hide()
    {
        show = false;
    }

    virtual void Show()
    {
        show = true;
    }

    virtual void SetCursorAboveFlag(bool flag)
    {
        cursorAbove = flag;
    }

    virtual bool CursorAboveFlag()
    {
        return cursorAbove;
    }

    ///
    /// \brief Метод возвращает true, если
    /// point находится в пределах описывающей
    /// прямоугольной области объекта, расширенной
    /// на extend единиц без её изменения.
    /// \return
    ///
    bool ContainsExt(QPointF point, double extend = 0)
    {
        QRectF extendedBound = QRectF(
                    bounds.left() - extend,
                    bounds.top() - extend,
                    bounds.right() + extend,
                    bounds.bottom() + extend);
        return extendedBound.contains(point);
    }

    virtual bool CursorAbove(QPointF position) = 0;
    virtual void Scale(double scale) = 0;
    virtual void Rotate(double angle) = 0;
    virtual void Move(QPointF vector) = 0;

protected:

    virtual void InitFigureName() = 0;

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
            else if (state == ItemState::editing)
            {
                SetState(ItemState::normal);
            }
            break;
        }
        default:
            break;
        }
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
    }

    virtual void ContextMenuEvent(QContextMenuEvent* pe)
    {
        if (state == ItemState::cursorAbove)
        {
            menu->exec(pe->globalPos());
            state = ItemState::contexMenuOpened;
        }
    }
};

#endif // IGEOMETRYITEM_H
