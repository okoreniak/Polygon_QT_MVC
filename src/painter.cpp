#include <QtWidgets>
#include "painter.h"

Painter::Painter(PolygonModel *model) :
    _model(model)
{
    Q_CHECK_PTR(_model);
}
//--------------------------------------------
//
//--------------------------------------------
Painter::~Painter()
{

}
//--------------------------------------------
//
//--------------------------------------------
void Painter::drawWireFrame(QPainter& painter, const QPoint& currentPoint)
{
    QPen oldPen = painter.pen();
    bool isConvex = _model->isConvexWithThisPoint(currentPoint);
    QPen line1Pen ((isConvex) ? Qt::green : Qt::red, 1,
                  Qt::SolidLine, Qt::RoundCap);
    QPen line2Pen ((isConvex) ? Qt::green : Qt::red, 1,
                  isConvex ? Qt::SolidLine : Qt::DotLine, Qt::RoundCap);

    painter.setPen(line1Pen);
    painter.drawLine(currentPoint, *_model->getLastPoint());
    painter.setPen(line2Pen);
    painter.drawLine(currentPoint, *_model->getFirstPoint());
    painter.setPen(oldPen);
}

void Painter::drawPoints(QPainter& painter)
{
    QPen oldPen = painter.pen();
    QPen pointPen (Qt::black, POLYGON_POINT_SIZE , Qt::SolidLine, Qt::RoundCap);
    // draw points
    painter.setPen(pointPen);
    const QVector<QPoint>& points = _model->getPoints();
    for(int i = 0; i < points.size(); ++i)
    {
        painter.drawPoint(points[i]);
    }
    painter.setPen(oldPen);
}

void Painter::drawNoWireFrame(QPainter& painter)
// draw last line in no wire mode
{
    QPen oldPen = painter.pen();
    bool isConvex = _model->isConvexWithThisPoint(*_model->getLastPoint());
    QPen line1Pen ((isConvex) ? Qt::green : Qt::red, 1,
                   Qt::SolidLine, Qt::RoundCap);
    painter.setPen(line1Pen);
    painter.drawLine(*_model->getFirstPoint(), *_model->getLastPoint());
    painter.setPen(oldPen);
}

void Painter::drawReadyPolygon(QPainter& painter)
{
    painter.drawLine(*_model->getLastPoint(),*_model->getFirstPoint());
    if (_model->isConvexWithThisPoint(*_model->getLastPoint()))
    {
        QBrush fillbrash;
        fillbrash.setColor(Qt::green);
        fillbrash.setStyle(Qt::SolidPattern);
        QPolygon poly (_model->getPoints());
        QPainterPath path;
        path.addPolygon(poly);
        painter.fillPath(path,fillbrash);
        painter.drawPolygon(poly);
    }
}

void Painter::drawLines(QPainter& painter)
{
    const QVector<QPoint> &points = _model->getPoints();
    for(int i = 0; i < points.size()-1; ++i)
    {
        painter.drawLine(points[i],points[i+1]);
    }
}

//--------------------------------------------
//
//--------------------------------------------
void Painter::draw(QWidget &widget, const QPoint& currentPoint)
{
    QPixmap mPix(widget.width(), widget.height());

    mPix.fill(Qt::white);
    QPainter p (&widget);
    p.drawPixmap(0,0,mPix);

    if (!_model->getPointCount())
    {
        return;
    }

    QPainter painter (&mPix);
    painter.setRenderHint(
        QPainter::Antialiasing);
    QPen linePen (Qt::black, 1, Qt::SolidLine, Qt::RoundCap);
    painter.setPen(linePen);

    if (_model->getPointCount() == 1)
    {
        painter.drawLine(currentPoint, *_model->getFirstPoint());
        p.drawPixmap(0,0,mPix);
        painter.end();
        return;
    }

    drawLines(painter);

    switch(_model->getMode())
    {
    case PolygonModel::Draw :
        drawWireFrame(painter,currentPoint);
        break;
    case PolygonModel::DrawNoWire :
        drawNoWireFrame(painter);
        break;
    case PolygonModel::Finish:
            drawReadyPolygon(painter);
        break;
    default: break;
    }

    drawPoints(painter);


    painter.end();

    p.drawPixmap(0,0,mPix);
}
