#ifndef POLYGONVIEW_H
#define POLYGONVIEW_H

#include <QObject>

class PolygonView
{
public:

    virtual void syncWithModel() {};
    virtual void enableCompleteButton(bool enable) {};
};

#endif // POLYGONVIEW_H
