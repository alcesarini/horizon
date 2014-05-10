#include "mainwindow.h"
#include <QApplication>
#include <hl/math/interpolation/hl_cubicSpline.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();






    HLINTP::HL_TEST_HL_CubicInterpAll();


    return a.exec();
}
