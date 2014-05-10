/**
FILE NAME= hl_iborIndex.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131216
*/


#include <hl/underlyings/interestRates/hl_iborIndex.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLIR::HL_IborIndex);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLIR::HL_IborIndexCode);

namespace HorizonLib
{
namespace HL_MarketData
{
namespace HL_Underlyings
{
namespace HL_InterestRates
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IborIndexCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_IborIndexCode::HL_IborIndexCode()
{
    classDefaultInit();

} // end HL_IborIndexCode

//------------------------------------------------------------------------------------------------------

HL_IborIndexCode::~HL_IborIndexCode()
{} // end ~HL_IborIndexCode

//------------------------------------------------------------------------------------------------------

void HL_IborIndexCode::classDefaultInit()
{} // end classDefaultInit
//------------------------------------------------------------------------------------------------------

HLSTRING HL_IborIndexCode::objTypeImpl() const
{
    return "HL_IborIndexCode";
} // end objTypeImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IborIndex
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_IborIndex::HL_IborIndex()
{

    classDefaultInit();



} // end HL_IborIndex

//------------------------------------------------------------------------------------------------------

HL_IborIndex::~HL_IborIndex()
{} // end ~HL_IborIndex

//------------------------------------------------------------------------------------------------------

void HL_IborIndex::classDefaultInit()
{} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

date HL_IborIndex::accrualEndDate(const date & accrualStartDate) const
{

    date aed= calendar_->advance(accrualStartDate,
                                 tenor_,
                                 accrualEndDateBDC_/*HL_BusinessDayConvention_Following*/,
                                 accrualEndDatePreserveLastBusinessDayOfMonth_/*send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth*/
                                );

    return aed;


} // end accrualEndDate

//------------------------------------------------------------------------------------------------------
void HL_IborIndex::descriptionImpl(std::ostream & os) const
{

    HL_InterestRate::descriptionImpl(os);

    hl_fillDescriptionStream(accrualEndDateBDC_);
    hl_fillDescriptionStream(accrualEndDatePreserveLastBusinessDayOfMonth_);
    hl_fillDescriptionStream(dcc_);

} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

HLR HL_IborIndex::forecastedExpectation(const date & fixingDate, const HL_MeasurePtr & hl_MeasurePtr) const
{

    HL_FAIL("implement this method also sharing the quanto adjustment and the convexity adjustment between ibor indexes and equities.");

    //HL_DYN_SHARED_PTR_CAST(HL_FwdMeasure, hl_FwdMeasure, hl_MeasurePtr);

    //const date & fwdMeasurePayDate = hl_FwdMeasure->get_payDate();

    //HLR forecastedExp = accrualEOEned

    return HL_NULL_REAL;

} // end forecastedExpectation

} // end namespace HL_InterestRates
} // end namespace HL_Underlyings
} // end namespace HL_MarketData
} //end namespace HorizonLib
