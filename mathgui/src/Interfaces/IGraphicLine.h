#ifndef IGRAPHICLINE_H
#define IGRAPHICLINE_H

#include <algorithm>
#include <QObject>
#include <QString>
#include <QPen>
#include <QBrush>

#define return_if(cond) if (cond) return;

enum ItemState
{
    normal = 0, cursorAbove, hooked, editing, contexMenuOpened, another
};

///
/// \brief Базовый класс для графических объектов,
/// состоящих из набора линий и кривых
///
class IGraphicLine : public QObject
{
    Q_OBJECT

protected:

    ItemState state = ItemState::normal;

    QPen pen = QPen(Qt::black, 2);
    QPen normalPen = QPen(Qt::black, 2);
    QPen cursorAbovePen = QPen(Qt::blue, 3);
    QPen hookedPen = QPen(Qt::red, 3);
    QPen editingPen = QPen(Qt::gray, 2);
    QPen anotherPen = QPen(Qt::red, 2);

    QBrush brush = QBrush(QColor(0, 0, 0, 0));

    double spread = 3;

public:
    explicit IGraphicLine(QObject *parent = nullptr);

    virtual void SetState(ItemState state)
    {
        this->state = state;
        switch(state)
        {
        case ItemState::normal:
            pen = normalPen;
            break;
        case ItemState::cursorAbove:
            pen = cursorAbovePen;
            break;
        case ItemState::hooked:
            pen = hookedPen;
            break;
        case ItemState::editing:
            pen = editingPen;
            break;
        case ItemState::another:
            pen = anotherPen;
            break;
        }
        emit StateChanged_signal(this, state);
    }

    ItemState State()
    {
        return state;
    }

    QPen CurrentPen()
    {
        return pen;
    }

    QBrush CurrentBrush()
    {
        return brush;
    }

    QPen NormalPen()
    {
        return normalPen;
    }

    QPen CursorAbovePen()
    {
        return cursorAbovePen;
    }

    QPen HookedPen()
    {
        return hookedPen;
    }

    QPen EditingPen()
    {
        return editingPen;
    }

    QPen AnotherPen()
    {
        return anotherPen;
    }

    void SetBrush(QBrush brush)
    {
        this->brush = brush;
    }

    void SetNormalPen(QPen pen)
    {
        normalPen = pen;
    }

    void SetCursorAbovePen(QPen pen)
    {
        cursorAbovePen = pen;
    }

    void SetHookedPen(QPen pen)
    {
        hookedPen = pen;
    }

    void SetEditingPen(QPen pen)
    {
        editingPen = pen;
    }

    void SetAnotherPen(QPen pen)
    {
        anotherPen = pen;
    }

    void SetSpread(double spread)
    {
        this->spread = spread;
    }

    double Spread()
    {
        return spread;
    }

    virtual void Draw(QPainter& painter) = 0;

protected:

signals:

    void SelectedForAction_signal();
    void StateChanged_signal(IGraphicLine* line, ItemState newState);
};

#endif // IGRAPHICLINE_H
