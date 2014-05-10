/**
FILE NAME= hl_underlying.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131214
*/


#include <hl/underlyings/hl_underlying.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLUND::HL_Underlying);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLUND::HL_UnderlyingCode);

//------------------------------------------------------------------------------------------------------

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLUND::HL_FwdMeasure);

namespace HorizonLib
{
namespace HL_MarketData
{
namespace HL_Underlyings
{
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Measure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_Measure::HL_Measure()
{
    classDefaultInit();

} // end HL_Measure

//------------------------------------------------------------------------------------------------------

HL_Measure::~HL_Measure()
{} // end ~HL_Measure

//------------------------------------------------------------------------------------------------------

void HL_Measure::classDefaultInit()
{} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_Measure::descriptionImpl(std::ostream & os) const
{

    Descriptable::descriptionImpl(os);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FwdMeasure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_FwdMeasure::HL_FwdMeasure()
{
    classDefaultInit();

} // end HL_FwdMeasure

//------------------------------------------------------------------------------------------------------

HL_FwdMeasure::~HL_FwdMeasure()
{} // end ~HL_FwdMeasure

//------------------------------------------------------------------------------------------------------

void HL_FwdMeasure::classDefaultInit()
{} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_FwdMeasure::descriptionImpl(std::ostream & os) const
{

    HL_Measure::descriptionImpl(os);
    os << "HL_FwdMeasure:\n";
    hl_fillDescriptionStream(payDate_);
    hl_fillDescriptionStream(hl_CcyCode_);


} // end descriptionImpl

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


HLR HL_Underlying::expectation(const date & fixingDate, const HL_MeasurePtr & hl_MeasurePtr) const
{

    const HLR * fixPtr = hl_DateRealHistoryPtr_->getFixingPtr(historyTag_,
                         fixingDate /*time*/,
                         get_refDate()/*refTime*/);

    HLR expect;

    if(fixPtr)
    {

        /*
        case: fixingDate<= get_refDate()
        */
        expect = (*fixPtr);

    }
    else
    {
        /*
        case: fixingDate>get_refDate()
        */
        HL_SRE_OBJ(hl_MeasurePtr!=0, "need a non-null hl_MeasurePtr to compute expectation in case fixingDate>get_refDate(), "
                   << "fixingDate=" << fixingDate << ", get_refDate()=" << get_refDate());

        expect = forecastedExpectation(fixingDate, hl_MeasurePtr);
    } // end if..else..


    return expect;


} // end expectation




//------------------------------------------------------------------------------------------------------

void HL_Underlying::descriptionImpl(std::ostream & os) const
{
    HLMD::HL_MktData::descriptionImpl(os);
    hl_fillDescriptionStream(calendar_);
    hl_fillDescriptionStream(hl_DateRealHistoryPtr_);
    hl_fillDescriptionStream(historyTag_);

} // end descriptionImpl



} // end namespace HL_Underlyings
} // end namespace HL_MarketData
} //end namespace HorizonLib
