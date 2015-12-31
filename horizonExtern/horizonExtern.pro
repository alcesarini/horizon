#-------------------------------------------------
#
# Project created by QtCreator 2015-12-12T16:59:50
#
#-------------------------------------------------

QT       -= core gui

TARGET = horizonExtern
TEMPLATE = lib


QMAKE_CXXFLAGS += -fPIC

#########################################################################################
#In data 20151231 ho ricompilato tutto con l'ultima versione di boost 1_66_0.
#Per farlo ho dovuto seguire le istruzioni in
#http://www.boost.org/doc/libs/1_60_0/more/getting_started/unix-variants.html
#In particolare ho seguito la sezione 5.2 di tale sito.
#Ho in pratica create le libs che sono in

#/home/ale/pro/boost_1_60_0/stage/lib

#Per farlo ho usato il comando customizzatto:

#./b2 --build-dir=/home/ale/pro/boost_1_60_0 link=static threading="multi" cxxflags='-fPIC' variant=release toolset=gcc stage

#Da notare che ho creato solo quelle release, multi thread, statiche (ovvero file .a e non .so).
#Inoltre ho dovuto aggiungere l'opzione cxxflags='-fPIC', perché altrimenti le lib statiche
#di boost (file .a) non avrebbero potuto essere usati per produrre horizionExtern,
#la quale è una shared lib (.so) e non un .exe come horizon.

#Inoltre, un altro punto critico si è avuto al momento di usare in python (tramite il modulo ctypes)
#la funzione extern dichiarata in horizonExtern.
#In pratica avevo un errore runtime "undefined symbol" legato a qualcosa di boost relativo ai log.
#Il problema era l'ordine dei link nei comandi qui sotto.
#In pratica, se una lib A usa un simbolo che è nella lib B, allora la lib A deve comparire
#prima della B nei comandi qui sotto (e dunque nel comand line di compilazione risultante g++ ...)
#Quindi per capirsi, le righe

#unix:!macx: LIBS += -L$$PWD/../build-horizonLib-Desktop_Qt_5_2_1_GCC_64bit-Debug/ -lhorizonLib
#unix:!macx: PRE_TARGETDEPS += $$PWD/../build-horizonLib-Desktop_Qt_5_2_1_GCC_64bit-Debug/libhorizonLib.a

#devono essere prima di tutte (perché horizonLib usa boost), poi DEVONO esserci le righe

#unix:!macx: LIBS += -L$$PWD/../boost_1_60_0/stage/lib/ -lboost_log
#unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_60_0/stage/lib/libboost_log.a

#perché boost_log probabilmente usa qualcosa nelle lib successive (es boost_system, boost_serialization, etc..)

#In sostanza, l'ordine conta!!! quindi se si hanno problemi, provare a modificarlo...

#Nel caso dei .exe l'ordine non sembra invece avere importanza.

#Questo è il command line risultante in DEBUG MODE:

#g++ -Wl,-rpath,/home/ale/Qt/5.2.1/gcc_64 -shared -Wl,
#-soname,libhorizonExtern.so.1 -o libhorizonExtern.so.1.0.0
#he_test.o he_defines.o
#-L/home/ale/pro/horizonExtern/../build-horizonLib-Desktop_Qt_5_2_1_GCC_64bit-Debug/ -lhorizonLib
#-L/home/ale/pro/horizonExtern/../boost_1_60_0/stage/lib/
#-lboost_log
#-lboost_system
#-lboost_serialization
#-lboost_thread
#-lboost_date_time
#-lpthread

#########################################################################################


CONFIG(debug,debug|release) {
# debug
message( "*** HORIZON DEBUG BUILD ***" ) # printed only when changing config debug/release
###################################################################################################################
###################################################################################################################
# linking debug configuration
###################################################################################################################
###################################################################################################################
# horizonLib  linking
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../build-horizonLib-Desktop_Qt_5_2_1_GCC_64bit-Debug/ -lhorizonLib
unix:!macx: PRE_TARGETDEPS += $$PWD/../build-horizonLib-Desktop_Qt_5_2_1_GCC_64bit-Debug/libhorizonLib.a
# boost linking
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_60_0/stage/lib/ -lboost_log
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_60_0/stage/lib/libboost_log.a
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_60_0/stage/lib/ -lboost_system
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_60_0/stage/lib/libboost_system.a
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_60_0/stage/lib/ -lboost_serialization
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_60_0/stage/lib/libboost_serialization.a
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_60_0/stage/lib/ -lboost_thread
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_60_0/stage/lib/libboost_thread.a
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_60_0/stage/lib/ -lboost_date_time
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_60_0/stage/lib/libboost_date_time.a
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
unix:!macx: LIBS += -L$$PWD/../boost_1_60_0/stage/lib/ -lboost_log
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_60_0/stage/lib/libboost_log.a
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_60_0/stage/lib/ -lboost_system
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_60_0/stage/lib/libboost_system.a
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_60_0/stage/lib/ -lboost_serialization
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_60_0/stage/lib/libboost_serialization.a
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_60_0/stage/lib/ -lboost_thread
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_60_0/stage/lib/libboost_thread.a
#------------------------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/../boost_1_60_0/stage/lib/ -lboost_date_time
unix:!macx: PRE_TARGETDEPS += $$PWD/../boost_1_60_0/stage/lib/libboost_date_time.a
#------------------------------------------------------------------------------------------------------------------
# end release
}


INCLUDEPATH += \
     /home/ale/pro/horizonExtern\
     /home/ale/pro/boost_1_60_0 \
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







#CONFIG(debug,debug|release) {
## debug
#message( "*** HORIZON DEBUG BUILD ***" ) # printed only when changing config debug/release
####################################################################################################################
####################################################################################################################
## linking debug configuration
####################################################################################################################
####################################################################################################################
##------------------------------------------------------------------------------------------------------------------
## horizonLib  linking
#unix:!macx: LIBS += -L$$PWD/../build-horizonLib-Desktop_Qt_5_2_1_GCC_64bit-Debug/ -lhorizonLib
#unix:!macx: PRE_TARGETDEPS += $$PWD/../build-horizonLib-Desktop_Qt_5_2_1_GCC_64bit-Debug/libhorizonLib.a
## end debug
#} else {
##release
#message( "*** HORIZON RELEASE BUILD ***" ) # printed only when changing config debug/release
####################################################################################################################
####################################################################################################################
## linking release configuration
####################################################################################################################
####################################################################################################################
##------------------------------------------------------------------------------------------------------------------
## horizonLib  linking
#unix:!macx: LIBS += -L$$PWD/../build-horizonLib-Desktop_Qt_5_2_1_GCC_64bit-Release/ -lhorizonLib
#unix:!macx: PRE_TARGETDEPS += $$PWD/../build-horizonLib-Desktop_Qt_5_2_1_GCC_64bit-Release/libhorizonLib.a
## end release
#}

