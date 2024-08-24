#include "CircleItem.h"

CircleItem::CircleItem(QObject *parent)
    : IGeometryItem{parent}
{
    centerItem = QSharedPointer<PointItem>(new PointItem());
    centerItem->SetPoint(center);
    AddChildItem(centerItem);

    radiusEditorItem = QSharedPointer<LineSegmentItem>(new LineSegmentItem());
    radiusEditorItem->SetFirstPoint(center);
    radiusEditorItem->SetSecondPoint(center->x() + radius, center->y());
    radiusEditorItem->SetNormalPen(QPen(Qt::gray, 2, Qt::DashLine));
    radiusEditorItem->SetCursorAbovePen(QPen(Qt::gray, 2, Qt::DashLine));
    radiusEditorItem->SetEditingPen(QPen(Qt::gray, 2, Qt::DashLine));
    radiusEditorItem->Hide();
    AddChildItem(radiusEditorItem);
    connect(radiusEditorItem->SecondPointItem().get(), SIGNAL(Moved_signal(QPointF)), this, SLOT(RadiusChanged(QPointF)));
    connect(radiusEditorItem->FirstPointItem().get(), SIGNAL(Moved_signal(QPointF)), this, SLOT(RadiusEditorItemMoved(QPointF)));
    connect(radiusEditorItem.get(), SIGNAL(Moved_signal(QPointF)), this, SLOT(RadiusEditorItemMoved(QPointF)));

    menu->addAction(RADIUS_CHANGE_ACTION);
    connect(menu.get(), SIGNAL(triggered(QAction*)), (CircleItem*)this, SLOT(slotActivated(QAction*)));
}
