#ifndef POLYGON_H
#define POLYGON_H
#include <QVector>
#include <QSharedPointer>
#include <QPointF>

#include "linesegment.h"

class Polygon
{
protected:
    QVector<QSharedPointer<LineSegment>> lines;

    bool closedFlag;

public:
    Polygon();

    void SetClosedFlag(bool flag)
    {
        closedFlag = flag;
    }

    bool ClosedFlag()
    {
        return closedFlag;
    }

    void SetPoints(const QVector<QSharedPointer<QPointF>>& points)
    {
        this->lines.resize(points.size() - 1);
    }

    void SetPoints(const QVector<QPointF>& points)
    {

    }

    void SetLines(const QVector<QSharedPointer<LineSegment>>& lines)
    {
        this->lines.resize(lines.size());
        std::copy(lines.begin(), lines.end(), this->lines.begin());
    }

    void SetLines(const QVector<LineSegment>& lines)
    {
        this->lines.resize(lines.size());
        std::copy(lines.begin(), lines.end(), this->lines.begin());
    }

    virtual void AppendLine(const QSharedPointer<LineSegment>& line)
    {
        lines.append(line);
    }

    virtual void AppendPoint(const QSharedPointer<QPointF>& point)
    {
        QSharedPointer<LineSegment> line(new LineSegment);
        line->SetFirstPoint(lines.last()->SecondPointPointer());
        line->SetSecondPoint(*point);
    }

};

#endif // POLYGON_H
