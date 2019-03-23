#include "polygoncontroller.h"
#include "polygonmodel.h"
#include "polygonview.h"

//--------------------------------------------
//
//--------------------------------------------
PolygonController::PolygonController(PolygonModel* model):
    _model(model)
{
    Q_CHECK_PTR(model);
}
//--------------------------------------------
//
//--------------------------------------------
PolygonController::~PolygonController()
{

}
//--------------------------------------------
//
//--------------------------------------------
void PolygonController::addView(PolygonView * view)
{
    Q_CHECK_PTR(view);
    if (_views.contains(view))
        return;
    _views.push_back(view);
}
//--------------------------------------------
//
//--------------------------------------------
void PolygonController::buttonPressed(int x, int y)
{
   if (_model->isConvexWithThisPoint(QPoint(x,y)))
   {
       bool enable = false;
       _model->addPoint(x,y);
       if (_model->getPointCount()> 2 &&
                _model->isConvexWithThisPoint(*_model->getLastPoint()))
       {
           enable = true;
       }
       enableButtonComplete(enable);
       syncViews();
   }
}

void PolygonController::enableButtonComplete(bool enable)
{
    foreach (PolygonView* view , _views)
    {
        view->enableCompleteButton(enable);
    }
}

//--------------------------------------------
//
//--------------------------------------------
void PolygonController::syncViews()
{
    foreach (PolygonView* view , _views)
    {
        view->syncWithModel();
    }
}
//--------------------------------------------
//
//--------------------------------------------
void PolygonController::reset()
{
    _model->reset();
    syncViews();
    enableButtonComplete(false);
}
//--------------------------------------------
//
//--------------------------------------------
void PolygonController::finishPolygon()
{
    if (_model->getPointCount() > 2)
    {
        if (_model->getMode() != PolygonModel::Finish)
        {
            _model->finish();
            syncViews();
        }
    }
}
//--------------------------------------------
//
//--------------------------------------------
void PolygonController::drawNoWire()
{
    // set drawnoware only if model in draw mode
    if (_model->getMode() == PolygonModel::Draw)
    {
        _model->drawNoWare();
        syncViews();
    }
}
//--------------------------------------------
//
//--------------------------------------------
void PolygonController::drawWire()
{
    // restore draw mode only in draw_no_wire mode
    if (_model->getMode() == PolygonModel::DrawNoWire)
    {
        _model->draw();
        syncViews();
    }
}
//--------------------------------------------
//
//--------------------------------------------
void PolygonController::startPolygon()
{
    _model->draw();
    syncViews();
}
