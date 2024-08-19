#ifndef EDITINGITEM_H
#define EDITINGITEM_H

#include "Interfaces/IGeometryItem.h"

///
/// \brief
/// Класс, от которого наследуются другие классы, редактирующие геометрические
/// фигуры объектов, таких, как пунктирная прямоугольная область для масштабирования
///
class EditingItem : public IGeometryItem
{
public:

    explicit EditingItem(QObject *parent = nullptr);

    void EnableEditing()
    {
        Show();
    }

    void DisableEditing()
    {
        Hide();
    }

signals:

    void EditingItemEnabled();
    void EditingItemDisabled();
};

#endif // EDITINGITEM_H
