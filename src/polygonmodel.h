#ifndef POLYGONMODEL_H
#define POLYGONMODEL_H


#include <qvector.h>

const int POLYGON_POINT_SIZE = 4;

class PolygonModel
{
public:
    enum Mode {
        Draw,  // begin new polygon
        DrawNoWire,   // draw current polygon without wire
        Finish  // finish current polygon
    };

    PolygonModel();
    virtual ~PolygonModel();

    virtual void addPoint(int x, int y);

    QPoint* getFirstPoint();
    QPoint* getLastPoint();
    int     getPointCount();
    const QVector<QPoint> &  getPoints();
    int     getAreaOfPolygon();

    bool isConvexPolygon(const QVector<QPoint>& points);
    bool isConvexWithThisPoint(const QPoint& point);

    void   draw()  { _mode = Draw; } // state to add
    void   drawNoWare() { _mode = DrawNoWire; }
    void   reset();
    void   finish() { _mode = Finish; }

    Mode    getMode() {return _mode;}

private:
    Mode _mode;
    QVector<QPoint> _points;
};

#endif // POLYGONMODEL_H
