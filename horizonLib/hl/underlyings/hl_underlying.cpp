/**
FILE NAME= hl_underlying.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131214
*/


#include <hl/underlyings/hl_underlying.h>
#include <hl/math/probMeasures/hl_convAdjMeasureChange.h>
#include <hl/math/probMeasures/hl_convAdjMeasureChange.h>
#include <hl/mktData/hl_mktDataCollector.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLUND::HL_Underlying);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLUND::HL_UnderlyingCode);

namespace HorizonLib
{
namespace HL_MarketData
{
namespace HL_Underlyings
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_UnderlyingCode::HL_UnderlyingCode()
{
    classDefaultInit();

} // end HL_UnderlyingCode

//------------------------------------------------------------------------------------------------------

HL_UnderlyingCode::~HL_UnderlyingCode()
{} // end ~HL_UnderlyingCode

//------------------------------------------------------------------------------------------------------

void HL_UnderlyingCode::classDefaultInit()
{} // end classDefaultInit
//------------------------------------------------------------------------------------------------------

HLSTRING HL_UnderlyingCode::objTypeImpl() const
{
    return "HL_UnderlyingCode";
} // end objTypeImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Underlying
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_Underlying::HL_Underlying()
{

    classDefaultInit();



} // end HL_Underlying

//------------------------------------------------------------------------------------------------------

HL_Underlying::~HL_Underlying()
{} // end ~HL_Underlying



//------------------------------------------------------------------------------------------------------

void HL_Underlying::classDefaultInit()
{} // end classDefaultInit



//------------------------------------------------------------------------------------------------------

void HL_Underlying::descriptionImpl(std::ostream & os) const
{
    HLMD::HL_MktData::descriptionImpl(os);
    hl_fillDescriptionStream(calendar_);
    hl_fillDescriptionStream(hl_TimeRealHistoryPtr_);
    hl_fillDescriptionStream(impliedVolSurfaceCode_);

} // end descriptionImpl



//------------------------------------------------------------------------------------------------------


HL_ExpectationPtr HL_Underlying::expectation(const ptime & fixingTime,
                                             const HL_MeasurePtr & measure,
                                             const HLSTRING & historyTag) const
{




    bool pastFixingFound;

    HL_ExpectationPtr expectation = getServiceExpectation(pastFixingFound,
                                                          fixingTime,
                                                          measure,
                                                          historyTag);



    if(!pastFixingFound)
    {
        /*
        case: fixingDate>get_refDate()
        */
        HL_SRE_OBJ(measure!=0, "need a non-null measure to compute expectation in case fixingDate>get_refDate(), "
                   << "fixingTime=" << fixingTime << ", get_refTime()=" << get_refTime());

        expectation->set_value(forecastExpectation(fixingTime, measure));


    } // end if..else..


    return expectation;


} // end expectation


//------------------------------------------------------------------------------------------------------

HL_ExpectationPtr HL_Underlying::quotingMeasureExpectation(const ptime & fixingTime,
                                                           const HLSTRING & historyTag) const
{

    bool pastFixingFound;

    HL_ExpectationPtr expectation = getServiceExpectation(pastFixingFound,
                                                          fixingTime,
                                                          get_quotingMeasure(fixingTime),
                                                          historyTag);


    if(!pastFixingFound)
        expectation->set_value(forecastQuotingMeasureExpectationImpl(fixingTime));

    return expectation;


} // end quotingMeasureExpectation

//------------------------------------------------------------------------------------------------------

HL_VolSurfacePtr HL_Underlying::get_impliedVolSurface() const
{

    HL_VolSurfacePtr volSurface =
            get_mktDataCollector()->get_mktData<HL_VolSurfacePtr>(impliedVolSurfaceCode_);

    return volSurface;

} // end get_impliedVolSurface

//------------------------------------------------------------------------------------------------------


HLR HL_Underlying::forecastExpectation(const ptime & fixingTime, const HL_MeasurePtr & measure) const
{

    HL_ExpectationPtr quotingMeasureExpect = quotingMeasureExpectation(fixingTime);


    if(measure->operator ==( quotingMeasureExpect->get_measure()))
    {
        return quotingMeasureExpect->get_value();
    }

    /*
     * We require this cast since we only know how to change expectations between T_i and T_j fwd measures possibly
     * of different ccys.
    */
    HL_DYN_SHARED_PTR_CAST(HLMA::HL_FwdMeasure, arrivalFwdMeasure, measure);

    HL_MeasureChangePtr measureChange(new HLMA::HL_MeasureChange);



    HLR adjustedExpectation =
            measureChange->getAdjustedExpectation(fixingTime /*underlyingFixingTime*/,
                                                  *this /*underlying*/,
                                                  arrivalFwdMeasure,
                                                  get_mktDataCollector());



    return adjustedExpectation;



} // end forecastExpectation




//------------------------------------------------------------------------------------------------------


HL_ExpectationPtr HL_Underlying::getServiceExpectation(bool & pastFixingFound,
                                                       const ptime & fixingTime,
                                                       const HL_MeasurePtr & measure,
                                                       const HLSTRING & historyTag) const
{



    const HLR * fixPtr = hl_TimeRealHistoryPtr_->getFixingPtr(historyTag,
                                                              fixingTime /*time*/
                                                              );


    HL_ExpectationPtr expectation(new HLMA::HL_Expectation);
    expectation->set_measure(measure);

    if(fixPtr)
    {
        pastFixingFound=true;

        /*
        case: fixingDate<= get_refDate()
        */
        expectation->set_value(*fixPtr);

    }
    else
    {
        pastFixingFound=false;

    } // end if..else..


    return expectation;

} // end getServiceExpectation



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//  defaultHistoryTag()
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HLSTRING defaultHistoryTag()
{

    return "defaultHistoryTag";
} // end defaultHistoryTag()


} // end namespace HL_Underlyings
} // end namespace HL_MarketData
} //end namespace HorizonLib
