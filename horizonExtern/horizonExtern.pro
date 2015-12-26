#-------------------------------------------------
#
# Project created by QtCreator 2015-12-12T16:59:50
#
#-------------------------------------------------

QT       -= core gui

TARGET = horizonExtern
TEMPLATE = lib

INCLUDEPATH += \
     /home/ale/pro/horizonExtern\
     /home/ale/pro/boost_1_55_0 \
     /home/ale/pro/horizonLib


DEFINES += HORIZONEXTERN_LIBRARY

SOURCES += \
    he/test/he_test.cpp \
    he/basicFiles/he_defines.cpp

HEADERS += \
    he/test/he_test.h \
    he/basicFiles/he_defines.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}



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
# end release
}


