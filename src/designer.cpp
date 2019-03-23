#include <QMouseEvent>
#include "designer.h"
#include "ui_designer.h"
#include "painter.h"
#include "polygoncontroller.h"
#include "polygonmodel.h"

Designer::Designer(PolygonController * controller,
                   PolygonModel * model,
                   QWidget *parent) :
    _controller(controller),
    _model(model),
    QMainWindow(parent),
    ui(new Ui::Designer)
{
    ui->setupUi(this);
    ui->actionComplete->setEnabled(false);

    connect(ui->actionComplete,SIGNAL(triggered(bool)),this,SLOT(slotComplete()));
    connect(ui->actionReset, SIGNAL(triggered(bool)),this, SLOT(slotReset()));
    connect(this,SIGNAL(signalPosition(int,int)), this, SLOT(slotNewPosition(int,int)));

    centralWidget()->setCursor(Qt::CrossCursor);
    centralWidget()->setMouseTracking(true);
    centralWidget()->installEventFilter(this);

    _controller->addView(this);
    _controller->startPolygon();

}

Designer::~Designer()
{
    delete ui;
}

void Designer::enableCompleteButton(bool enable)
{
    ui->actionComplete->setEnabled(enable);
}

void Designer::syncWithModel()
{
    centralWidget()->update();
}

void Designer::slotReset()
{
    _controller->reset();
}

void Designer::slotComplete()
{
    _controller->finishPolygon();

    QString polygon = _model->isConvexWithThisPoint(*_model->getLastPoint())
            ? "convex" : "non convex";
    QString msg = QString(tr("Built a polygo. "
                             "It is %1, its area: %2.1")).arg(polygon).arg(
                _model->getAreaOfPolygon());
    ui->statusBar->showMessage(msg);
}

void Designer::slotNewPosition(int x, int y)
{
    if (_model->getMode() == PolygonModel::Finish)
        return ;
    ui->statusBar->showMessage(QString("%1 %2").arg(x).arg(y));
}

void Designer::paint()
{
    Painter p (_model);
    p.draw(*centralWidget(),currentPoint);
}

bool Designer::eventFilter(QObject* target, QEvent* event)
{
    if (target == centralWidget() )
    {

        if (event->type() == QEvent::MouseButtonPress ||
                event->type() == QEvent::MouseMove )
        {

            QMouseEvent * mouseEvent = static_cast<QMouseEvent*>(event);
            int x = mouseEvent->x();
            int y = mouseEvent->y();

            currentPoint.setX(x);
            currentPoint.setY(y);

            emit signalPosition(x,y);

            if (event->type() == QEvent::MouseButtonPress)
            {
                _controller->buttonPressed(x,y);
            }
            centralWidget()->update();
        }
        if (event->type() == QEvent::Paint)
        {
            paint();
        }
        if (event->type() == QEvent::Enter)
        {
            _controller->drawWire();
        }
        if (event->type() == QEvent::Leave)
        {
            _controller->drawNoWire();
        }
    }
    return QMainWindow::eventFilter(target,event);
}
