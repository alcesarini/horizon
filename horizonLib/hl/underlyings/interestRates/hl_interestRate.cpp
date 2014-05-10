/**
FILE NAME= hl_interestRate.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131214
*/


#include <hl/underlyings/interestRates/hl_interestRate.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLIR::HL_InterestRate);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLIR::HL_InterestRateCode);

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
// class HL_InterestRateCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_InterestRateCode::HL_InterestRateCode()
{
    classDefaultInit();
} // end HL_InterestRateCode

//------------------------------------------------------------------------------------------------------

HL_InterestRateCode::~HL_InterestRateCode()
{} // end ~HL_InterestRateCode

//------------------------------------------------------------------------------------------------------

void HL_InterestRateCode::classDefaultInit()
{
} // end classDefaultInit
//------------------------------------------------------------------------------------------------------

HLSTRING HL_InterestRateCode::objTypeImpl() const
{
    return "HL_InterestRateCode";
} // end objTypeImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterestRate
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_InterestRate::HL_InterestRate()
{

    classDefaultInit();



} // end HL_InterestRate

//------------------------------------------------------------------------------------------------------

HL_InterestRate::~HL_InterestRate()
{} // end ~HL_InterestRate


//------------------------------------------------------------------------------------------------------

void HL_InterestRate::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_InterestRate::descriptionImpl(std::ostream & os) const
{
    HL_Underlying::descriptionImpl(os);
    hl_fillDescriptionStream(tenor_);
    hl_fillDescriptionStream(fixingDays_);


} // end descriptionImpl


//------------------------------------------------------------------------------------------------------

date HL_InterestRate::fixingDate(const date & accrualStartDate) const
{
    date fd= calendar_->advance(accrualStartDate,
                                HL_Period(-fixingDays_, HL_PeriodUnit_Days),
                                HL_BusinessDayConvention_Preceding
                               );

    return fd;

} // end fixingDate

//------------------------------------------------------------------------------------------------------


date HL_InterestRate::accrualStartDate(const date & fixingDate) const
{
    HL_SR(isValidFixingDate(fixingDate));

    date asd= calendar_->advance(fixingDate,
                                 HL_Period(+fixingDays_, HL_PeriodUnit_Days),
                                 HL_BusinessDayConvention_Following
                                );

    return asd;
} // end accrualStartDate

//------------------------------------------------------------------------------------------------------


bool HL_InterestRate::isValidFixingDate(const date & fixingDate) const
{
    return calendar_->isBusiness(fixingDate);
} // end isValidFixingDate


//------------------------------------------------------------------------------------------------------



} // end namespace HL_InterestRates
} // end namespace HL_Underlyings
} // end namespace HL_MarketData
} //end namespace HorizonLib
