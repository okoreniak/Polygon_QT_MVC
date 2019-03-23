#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include "polygonmodel.h"

class Painter
{
public:
    Painter(PolygonModel *model);
    virtual void draw(QWidget &widget,const QPoint &currentPoint);
    virtual ~Painter() ;

protected:
    void drawWireFrame(QPainter& painter, const QPoint& currentPoint);
    void drawPoints(QPainter& painter);
    void drawNoWireFrame(QPainter& painter);
    void drawReadyPolygon(QPainter& painter);
    void drawLines(QPainter& painter);
private:

    PolygonModel *_model;
};

#endif // PAINTER_H
