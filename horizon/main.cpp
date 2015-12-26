#include "mainwindow.h"
#include <QApplication>
#include <hl/math/interpolation/hl_cubicSpline.h>
#include <hl/serialization/hl_test_serialization.h>
#include <hl/math/rootFinding/hl_rootFinding.h>
#include <hl/mktData/yieldTermStructureBootstrap/hl_yieldTsBootstrap.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();


    using namespace HLEXC;

    HL_TRY
    {

        HLMA::HL_TEST_HL_RootFinder();

        //HLSER::HL_TEST_HL_Obj_serialization_sharedPtrCleverManagement();

        //HLINTP::HL_TEST_HL_1_D_CubicInterpAll();

        HLMD::HL_TEST_HL_IRCurveBootstrap();

    }
    HL_CATCH;

    //return a.exec();
    return 1;
}
