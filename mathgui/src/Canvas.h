#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QVector>
#include <QDebug>
#include <QThread>

#include "Interfaces/IGeometryItem.h"
#include "Interfaces/IGeometryItem.h"
#include "PointItem.h"

class Canvas : public QWidget
{
    Q_OBJECT

private:

//    QThread selectTopLevelObject

protected:

    // Содержит только фигуры
    QVector<QSharedPointer<IGeometryItem>> geometryFigures;

    // Содержит абсолютно все items на полотне,
    // включая те, из которых состоят фигуры
    QVector<QSharedPointer<IGeometryItem>> geometryItems;

public:
    explicit Canvas(QWidget *parent = nullptr);
    virtual ~Canvas()
    {

    }

    void AddGeometryItem(QSharedPointer<IGeometryItem> item)
    {
        AddGeometryItem(item, false);
    }

protected:

    void AddGeometryItem(QSharedPointer<IGeometryItem> item, bool subItem)
    {
        connect(this, SIGNAL(MousePressEvent_signal(QMouseEvent*)), item.get(), SLOT(MousePressEvent(QMouseEvent*)));
        connect(this, SIGNAL(MouseMoveEvent_signal(QMouseEvent*)), item.get(), SLOT(MouseMoveEvent(QMouseEvent*)));
        connect(this, SIGNAL(MouseReleaseEvent_signal(QMouseEvent*)), item.get(), SLOT(MouseReleaseEvent(QMouseEvent*)));
        connect(this, SIGNAL(ContextMenuEvent_signal(QContextMenuEvent*)), item.get(), SLOT(ContextMenuEvent(QContextMenuEvent*)));
        connect(item.get(), SIGNAL(StateChanged_signal(IGraphicLine*, ItemState)), this, SLOT(ItemStateChanged(IGraphicLine*, ItemState)));

        if (!subItem)
        {
            geometryFigures.append(item);
        }
        geometryItems.append(item);

        auto childItems = item->ChildItems();
        for (int i = 0; i < childItems.size(); ++i)
        {
            auto childItem = childItems[i];
            AddGeometryItem(childItem, true);
        }
    }

    void mousePressEvent(QMouseEvent* event) override
    {
        emit MousePressEvent_signal(event);
        update();
    }

    void mouseMoveEvent(QMouseEvent* event) override
    {
        FindObjectUnderCursor(event->pos());
        emit MouseMoveEvent_signal(event);
        update();
    }

    void mouseReleaseEvent(QMouseEvent* event) override
    {
        emit MouseReleaseEvent_signal(event);
        update();
    }

    void paintEvent(QPaintEvent* event) override
    {
        QPainter painter;
        painter.begin(this);
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
        for (int i = 0; i < geometryFigures.size(); ++i)
            geometryFigures[i]->Draw(painter);
        painter.end();
    }

    void contextMenuEvent(QContextMenuEvent* pe) override
    {
        emit ContextMenuEvent_signal(pe);
    }

private:

    ///
    /// \brief Проверка всех объектов на то, что они находятся под курсором.
    /// Первый попавшийся объект, либо точка из списка всех объектов помечается флагом cursorAbove
    /// в том случае, когда курсор находится над этим объектом или точкой.
    /// \param pos
    ///
    void FindObjectUnderCursor(QPointF pos)
    {

        bool statesFinded = false;
        for (int i = 0; i < geometryItems.size(); ++i)
        {
            if (geometryItems[i]->State() == ItemState::hooked)
            {
                statesFinded = true;
                geometryItems[i]->SetCursorAboveFlag(true);

            }
            else
            {
                geometryItems[i]->SetCursorAboveFlag(false);
            }
        }

        if (statesFinded)
            return;

        PointItem* point = nullptr;
        IGeometryItem* item = nullptr;

        bool pointFinded = false;
        bool itemFinded = false;
        for (int i = 0; i < geometryItems.size(); ++i)
        {
            bool cursorAbove = geometryItems[i]->CursorAbove(pos);
            auto cast_ptr = dynamic_cast<PointItem*>(geometryItems[i].get());
            if ( cursorAbove && cast_ptr != nullptr && !pointFinded)
            {
                point = cast_ptr;
                pointFinded = true;
            }
            else if (cursorAbove && cast_ptr == nullptr && !itemFinded)
            {
                item = geometryItems[i].get();
                itemFinded = true;
            }
        }
        if (point != nullptr)
        {
            point->SetCursorAboveFlag(true);
        }
        else if (item != nullptr)
        {
            item->SetCursorAboveFlag(true);
        }

//        for (int i = 0; i < geometryItems.size(); ++i)
//        {
//            qDebug() << "i = " << i << "; " << geometryItems[i]->CursorAboveFlag();
//        }
//        qDebug() << "";
    }

public slots:

    void ItemStateChanged(IGraphicLine* line, ItemState newState)
    {
        IGeometryItem* item = dynamic_cast<IGeometryItem*>(line);
        if (item != nullptr)
        {
            if (newState == ItemState::hooked)
            {
                for (int i = 0; i < geometryItems.size(); ++i)
                    if (geometryItems[i].get() == item)
                    {
                        geometryItems.swapItemsAt(0, i);
                    }
            }
            else if (newState == ItemState::normal)
            {

            }
        }
    }

signals:

    void MousePressEvent_signal(QMouseEvent* event);
    void MouseMoveEvent_signal(QMouseEvent* event);
    void MouseReleaseEvent_signal(QMouseEvent* event);
    void ContextMenuEvent_signal(QContextMenuEvent* pe);
};

#endif // CANVAS_H
