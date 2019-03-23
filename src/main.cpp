#include "designer.h"
#include <QApplication>
#include "polygonmodel.h"
#include "polygoncontroller.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PolygonModel model;
    PolygonController controller(&model);
    Designer w(&controller,&model);
    w.show();

    return a.exec();
}
