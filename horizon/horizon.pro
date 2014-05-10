#-------------------------------------------------
#
# Project created by QtCreator 2014-04-27T12:57:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = horizon
TEMPLATE = app

INCLUDEPATH += \
     /home/ale/pro/boost_1_55_0 \
     /home/ale/pro/horizonLib

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h


FORMS    += mainwindow.ui


CONFIG(debug,debug|release) {
# debug
message( "*** HORIZON DEBUG BUILD ***" ) # printed only when changing config debug/release
###################################################################################################################
###################################################################################################################
# linking debug configuration
###################################################################################################################
###################################################################################################################
#------------------------------------------------------------------------------------------------------------------
# horizonLib  linking
unix:!macx: LIBS += -L$$PWD/../build-horizonLib-Desktop_Qt_5_2_1_GCC_64bit-Debug/ -lhorizonLib
unix:!macx: PRE_TARGETDEPS += $$PWD/../build-horizonLib-Desktop_Qt_5_2_1_GCC_64bit-Debug/libhorizonLib.a
# boost linking
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_55_0/stage/lib/ -lboost_serialization-gcc48-mt-sd-1_55
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_55_0/stage/lib/libboost_serialization-gcc48-mt-sd-1_55.a
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_55_0/stage/lib/ -lboost_system-gcc48-mt-sd-1_55
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_55_0/stage/lib/libboost_system-gcc48-mt-sd-1_55.a
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_55_0/stage/lib/ -lboost_log-gcc48-mt-sd-1_55
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_55_0/stage/lib/libboost_log-gcc48-mt-sd-1_55.a
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_55_0/stage/lib/ -lboost_thread-gcc48-mt-sd-1_55
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_55_0/stage/lib/libboost_thread-gcc48-mt-sd-1_55.a
#------------------------------------------------------------------------------------------------------------------
# end debug
} else {
#release
message( "*** HORIZON RELEASE BUILD ***" ) # printed only when changing config debug/release
###################################################################################################################
###################################################################################################################
# linking release configuration
###################################################################################################################
###################################################################################################################
#------------------------------------------------------------------------------------------------------------------
# horizonLib  linking
unix:!macx: LIBS += -L$$PWD/../build-horizonLib-Desktop_Qt_5_2_1_GCC_64bit-Release/ -lhorizonLib
unix:!macx: PRE_TARGETDEPS += $$PWD/../build-horizonLib-Desktop_Qt_5_2_1_GCC_64bit-Release/libhorizonLib.a
# boost linking
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_55_0/stage/lib/ -lboost_serialization-gcc48-mt-s-1_55
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_55_0/stage/lib/libboost_serialization-gcc48-mt-s-1_55.a
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_55_0/stage/lib/ -lboost_system-gcc48-mt-s-1_55
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_55_0/stage/lib/libboost_system-gcc48-mt-s-1_55.a
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_55_0/stage/lib/ -lboost_log-gcc48-mt-s-1_55
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_55_0/stage/lib/libboost_log-gcc48-mt-s-1_55.a
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_55_0/stage/lib/ -lboost_thread-gcc48-mt-s-1_55
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_55_0/stage/lib/libboost_thread-gcc48-mt-s-1_55.a
#------------------------------------------------------------------------------------------------------------------
# end release
}
