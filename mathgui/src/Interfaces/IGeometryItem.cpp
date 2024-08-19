#include "IGeometryItem.h"

IGeometryItem::IGeometryItem(QObject *parent)
    : IGraphicLine{parent}
{
    menu = QSharedPointer<QMenu>(new QMenu);
}
