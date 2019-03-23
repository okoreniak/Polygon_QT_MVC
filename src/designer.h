#ifndef DESIGNER_H
#define DESIGNER_H

#include <QMainWindow>
#include "polygonview.h"

namespace Ui {
class Designer;
}

class PolygonModel;
class PolygonController;

class Designer : public QMainWindow, public PolygonView
{
    Q_OBJECT

public:
    explicit Designer(PolygonController* controller,
                      PolygonModel* model,
                      QWidget *parent = 0);
    ~Designer();

    void syncWithModel() override;
    void enableCompleteButton(bool enable) override;

private slots:
    void slotReset();
    void slotComplete();
    void slotNewPosition(int x, int y);

signals:
    void signalPosition(int x, int y);

protected:

    void paint();
private:
    bool eventFilter(QObject* target,QEvent* event);
 private:
    Ui::Designer *ui;
    QPoint currentPoint;
    PolygonController* _controller;
    PolygonModel *     _model;
};

#endif // DESIGNER_H
