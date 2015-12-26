#-------------------------------------------------
#
# Project created by QtCreator 2014-04-28T21:10:51
#
#-------------------------------------------------

QT       -= core gui

TARGET = horizonLib
TEMPLATE = lib
CONFIG+= staticlib

DEFINES += HORIZONLIB_LIBRARY


INCLUDEPATH += \
    /home/ale/pro/boost_1_55_0 \
    /home/ale/pro/horizonLib

SOURCES += \
    hl/containers/hl_containerManip.cpp \
    hl/containers/hl_multiArray.cpp \
    hl/currencies/hl_ccyCode.cpp \
    hl/dateTime/calendar/hl_calendar.cpp \
    hl/dateTime/hl_dateTime.cpp \
    hl/dateTime/hl_dcc.cpp \
    hl/dateTime/hl_period.cpp \
    hl/enviroment/hl_enviromentInit.cpp \
    hl/exceptions/hl_exceptions.cpp \
    hl/logging/hl_logging.cpp \
    hl/math/interpolation/hl_bidimCubicSpline.cpp \
    hl/math/interpolation/hl_cubicSpline.cpp \
    hl/math/interpolation/hl_interpolator.cpp \
    hl/math/interpolation/hl_multiLinearInterp.cpp \
    hl/math/linearAlgebra/hl_tridiagonalOperator.cpp \
    hl/math/hl_basicFunctions.cpp \
    hl/math/hl_comparisonChecks.cpp \
    hl/math/hl_function.cpp \
    hl/math/hl_mathUtils.cpp \
    hl/mktData/termStructures/hl_termStructure.cpp \
    hl/mktData/volSurfaces/hl_volSurface.cpp \
    hl/mktData/hl_mktData.cpp \
    hl/mktData/hl_mktDataCollector.cpp \
    hl/object/hl_history.cpp \
    hl/object/hl_machine.cpp \
    hl/object/hl_object.cpp \
    hl/object/hl_objectCode.cpp \
    hl/patterns/hl_descriptable.cpp \
    hl/patterns/hl_ordering.cpp \
    hl/serialization/hl_coreSerializableObj.cpp \
    hl/serialization/hl_test_serialization.cpp \
    hl/underlyings/interestRates/hl_iborIndex.cpp \
    hl/underlyings/interestRates/hl_interestRate.cpp \
    hl/underlyings/hl_underlying.cpp \
    hl/instruments/hl_cashFlow.cpp \
    hl/instruments/hl_basket.cpp \
    hl/instruments/hl_basketWeights.cpp \
    hl/instruments/hl_vanillaCashFlow.cpp \
    hl/math/pricingFunctions/hl_vanillaPricingFunctions.cpp \
    hl/mktData/correlations/hl_correlationTermStructure.cpp \
    hl/mktData/mktQuotes/hl_mktQuote.cpp \
    hl/instruments/anagraphics/hl_anagraphics.cpp \
    hl/instruments/anagraphics/hl_scheduleAnagraphics.cpp \
    hl/math/probMeasures/hl_probMeasure.cpp \
    hl/math/probMeasures/hl_convAdjMeasureChange.cpp \
    hl/pricingEngines/hl_pricingEngine.cpp \
    hl/pricingEngines/hl_vanillaCashFlowPricingEngine.cpp \
    hl/instruments/hl_baseIns.cpp \
    hl/pricingEngines/hl_cashFlowPricingEngine.cpp \
    hl/mktData/yieldTermStructureBootstrap/hl_yieldTsBootstrap.cpp \
    hl/instruments/anagraphics/hl_mktInsAnagraphics.cpp \
    hl/instruments/anagraphics/hl_mktInsFactory.cpp \
    hl/mktData/hl_mktDataDescriptor.cpp \
    hl/pricingEngines/hl_pricingEngineFactory.cpp \
    hl/patterns/hl_modifier.cpp \
    hl/patterns/hl_calibAction.cpp \
    hl/math/rootFinding/hl_rootFinding.cpp \
    hl/mktData/hl_mktDataCollector_HL_TEST.cpp \
    hl/patterns/hl_baseAction.cpp \
    hl/test/hl_test.cpp

HEADERS += \
    hl/basicFiles/hl_auto_link.hpp \
    hl/basicFiles/hl_basicIncludes.h \
    hl/basicFiles/hl_boostIncludes.h \
    hl/basicFiles/hl_templates.h \
    hl/basicFiles/hl_workingIncludes.h \
    hl/containers/hl_containerManip.h \
    hl/containers/hl_multiArray.h \
    hl/currencies/hl_ccyCode.h \
    hl/dateTime/calendar/hl_calendar.h \
    hl/dateTime/hl_dateTime.h \
    hl/dateTime/hl_dcc.h \
    hl/dateTime/hl_period.h \
    hl/enviroment/hl_enviromentInit.h \
    hl/exceptions/hl_exceptions.h \
    hl/logging/hl_logging.h \
    hl/math/interpolation/hl_bidimCubicSpline.h \
    hl/math/interpolation/hl_cubicSpline.h \
    hl/math/interpolation/hl_interpolator.h \
    hl/math/interpolation/hl_multiLinearInterp.h \
    hl/math/linearAlgebra/hl_tridiagonalOperator.h \
    hl/math/hl_basicFunctions.h \
    hl/math/hl_comparisonChecks.h \
    hl/math/hl_function.h \
    hl/math/hl_mathUtils.h \
    hl/mktData/termStructures/hl_termStructure.h \
    hl/mktData/volSurfaces/hl_volSurface.h \
    hl/mktData/hl_mktData.h \
    hl/mktData/hl_mktDataCollector.h \
    hl/object/hl_history.h \
    hl/object/hl_machine.h \
    hl/object/hl_object.h \
    hl/object/hl_objectCode.h \
    hl/patterns/hl_descriptable.h \
    hl/patterns/hl_disposable.h \
    hl/patterns/hl_ordering.h \
    hl/serialization/hl_coreSerializableObj.h \
    hl/serialization/hl_test_serialization.h \
    hl/underlyings/interestRates/hl_iborIndex.h \
    hl/underlyings/interestRates/hl_interestRate.h \
    hl/underlyings/hl_underlying.h \
    hl/instruments/hl_cashFlow.h \
    hl/instruments/hl_basket.h \
    hl/instruments/hl_basketComposition.h \
    hl/instruments/hl_vanillaCashFlow.h \
    hl/math/pricingFunctions/hl_vanillaPricingFunctions.h \
    hl/basicFiles/hl_commonDeclarations.h \
    hl/mktData/correlations/hl_correlationTermStructure.h \
    hl/mktData/mktQuotes/hl_mktQuote.h \
    hl/instruments/anagraphics/hl_anagraphics.h \
    hl/instruments/anagraphics/hl_scheduleAnagraphics.h \
    hl/math/probMeasures/hl_probMeasure.h \
    hl/math/probMeasures/hl_convAdjMeasureChange.h \
    hl/pricingEngines/hl_pricingEngine.h \
    hl/pricingEngines/hl_vanillaCashFlowPricingEngine.h \
    hl/instruments/hl_baseIns.h \
    hl/pricingEngines/hl_cashFlowPricingEngine.h \
    hl/instruments/hl_basketWeights.h \
    hl/mktData/yieldTermStructureBootstrap/hl_yieldTsBootstrap.h \
    hl/instruments/anagraphics/hl_mktInsAnagraphics.h \
    hl/instruments/anagraphics/hl_mktInsFactory.h \
    hl/mktData/hl_mktDataDescriptor.h \
    hl/pricingEngines/hl_pricingEngineFactory.h \
    hl/patterns/hl_modifier.h \
    hl/patterns/hl_calibAction.h \
    hl/math/rootFinding/hl_rootFinding.h \
    hl/mktData/hl_mktDataCollector_HL_TEST.h \
    hl/patterns/hl_baseAction.h \
    hl/test/hl_test.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
