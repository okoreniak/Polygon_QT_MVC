#ifndef POLYGONCONTROLLER_H
#define POLYGONCONTROLLER_H

#include <QObject>
#include <qvector.h>

class PolygonModel;
class PolygonView;

class PolygonController
{
public:
    PolygonController(PolygonModel* model);
    virtual ~PolygonController();

    void addView(PolygonView* view);

    void syncViews();
    void enableButtonComplete(bool enable);

    void buttonPressed(int x, int y);


    void startPolygon();
    void finishPolygon();
    void drawNoWire();
    void drawWire();
    void reset();

private:
    PolygonModel * _model;
    QVector<PolygonView*>  _views;
};

#endif // POLYGONCONTROLLER_H
