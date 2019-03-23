#include "polygonmodel.h"
#include <qdebug.h>
//--------------------------------------------
//
//--------------------------------------------
PolygonModel::PolygonModel() :
    _mode(Draw)
{

}
//--------------------------------------------
//
//--------------------------------------------
PolygonModel::~PolygonModel()
{

}

//--------------------------------------------
//
//--------------------------------------------
void PolygonModel::addPoint(int x, int y)
{
    _points.push_back(QPoint(x,y));
}

//--------------------------------------------
//
//--------------------------------------------
int PolygonModel::getAreaOfPolygon()
{
    if (_points.size() < 2) return 0;
    int area = 0;
    for(int i = 0; i < _points.size(); ++i)
    {
        QPoint* p1 = i ? &_points[i-1] : &_points.back();
        QPoint* p2 = &_points[i];
        area += (p1->x() - p2->x()) * (p1->y() + p2->y());
    }
    area = abs(area)/2;
    return area;
}

//--------------------------------------------
//
//--------------------------------------------
bool intersect(const QPoint &a1, const QPoint &a2,
               const QPoint &b1, const QPoint &b2)
{
    qint64 v1 = (b2.x()-b1.x())*(a1.y()-b1.y())-(b2.y()-b1.y())*(a1.x()-b1.x());
    qint64 v2 = (b2.x()-b1.x())*(a2.y()-b1.y())-(b2.y()-b1.y())*(a2.x()-b1.x());
    qint64 v3 = (a2.x()-a1.x())*(b1.y()-a1.y())-(a2.y()-a1.y())*(b1.x()-a1.x());
    qint64 v4 = (a2.x()-a1.x())*(b2.y()-a1.y())-(a2.y()-a1.y())*(b2.x()-a1.x());
// Intersection:=(v1*v2<0) and (v3*v4<0);
//    qDebug() << "v1=" << v1 << " v2=" << v2 << " v3=" << v3 << " v4-" << v4;
//    qDebug() << "vi*v2=" << v1*v2  << " v3*v4=" << v3*v4;
    return (v1*v2 <0) && (v3*v4 <0) ;
}
//--------------------------------------------
//
//--------------------------------------------
bool PolygonModel::isConvexWithThisPoint(const QPoint& point)
{
    size_t size =_points.size();

    if (size < 3)
        return true;
    const QPoint * pt1 = getFirstPoint();
    const QPoint * pt2 = getLastPoint();
    Q_ASSERT (pt1 != nullptr);
    Q_ASSERT (pt2 != nullptr);
    for (int i = 0; i < size-1; ++i)
    {
        QPoint *p11  = &_points[i];
        QPoint *p12 =  &_points[i+1];
        if (intersect(point,*pt1,*p11,*p12))
            return false;
        if (intersect(point,*pt2, *p11, *p12))
            return false;
    }

    return true;
}
//--------------------------------------------
//
//--------------------------------------------
bool PolygonModel::isConvexPolygon(const QVector<QPoint>& points)
{
    int i, j, k;
    double z;

    int flag    = 0;
    size_t size =points.size();

    if (size < 3)
        return true;

    for (i = 0; i < size; ++i)
    {
        j = (i + 1) % size;
        k = (i + 2) % size;

        z = (points[j].x() - points[i].x()) * (points[k].y() - points[j].y());
        z-= (points[j].y() - points[i].y()) * (points[k].x() - points[j].x());

        if      (z < 0.0) flag |= 1;
        else if (z > 0.0) flag |= 2;

        if (flag == 3)
            return false;
    }

    if (flag)
        return true;

    return false;
}
//--------------------------------------------
//
//--------------------------------------------
QPoint* PolygonModel::getFirstPoint()
{
    QPoint * p = nullptr;
    if (_points.size())
        p = &_points[0];
    return p;
}
//--------------------------------------------
//
//--------------------------------------------
QPoint* PolygonModel::getLastPoint()
{
    QPoint * p = nullptr;
    if (_points.size())
        p = &_points[_points.size()-1];
    return p;
}
//--------------------------------------------
//
//--------------------------------------------
int    PolygonModel::getPointCount()
{
    return _points.size();
}
//--------------------------------------------
//
//--------------------------------------------
void PolygonModel::reset()
{
    _points.clear();
    _mode = Draw;
}
//--------------------------------------------
//
//--------------------------------------------
const QVector<QPoint> & PolygonModel::getPoints()
{
    return _points;
}
