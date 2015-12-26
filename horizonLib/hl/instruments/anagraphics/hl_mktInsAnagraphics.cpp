/**
FILE NAME= hl_mktInsAnagraphics.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20141207
*/

#include <hl/instruments/anagraphics/hl_mktInsAnagraphics.h>
#include <hl/underlyings/interestRates/hl_iborIndex.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLAN::HL_LegAnagraphics);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLAN::HL_FixedLegAnagraphics);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLAN::HL_VariableLegAnagraphics);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLAN::HL_SwapAnagraphics);




namespace HorizonLib
{
namespace HL_Instruments
{
namespace HL_Anagraphics
{





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_LegAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_LegAnagraphics::HL_LegAnagraphics()
{

    classDefaultInit();



} // end HL_LegAnagraphics

//------------------------------------------------------------------------------------------------------

HL_LegAnagraphics::~HL_LegAnagraphics()
{} // end ~HL_LegAnagraphics


//------------------------------------------------------------------------------------------------------

void HL_LegAnagraphics::classDefaultInit()
{

} // end classDefaultInit



//------------------------------------------------------------------------------------------------------


void HL_LegAnagraphics::descriptionImpl(std::ostream & os) const
{

    HL_Anagraphics::descriptionImpl(os);
    hl_fillDescriptionStream(ccyCode_);
    hl_fillDescriptionStream(scheduleAnagraphics_);
    hl_fillDescriptionStream(get_cashFlowType());
    hl_fillDescriptionStream(accrualDcc_);
    hl_fillDescriptionStream(payDateSettlementDays_);
    hl_fillDescriptionStream(payDateBusinessDayConvention_);




} // end descriptionImpl


//------------------------------------------------------------------------------------------------------

void HL_LegAnagraphics::checkAnagraphics() const
{

    HL_Anagraphics::checkAnagraphics();

} // end checkAnagraphics

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_LegAnagraphics: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedLegAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_FixedLegAnagraphics::HL_FixedLegAnagraphics()
{

    classDefaultInit();



} // end HL_FixedLegAnagraphics

//------------------------------------------------------------------------------------------------------

HL_FixedLegAnagraphics::~HL_FixedLegAnagraphics()
{} // end ~HL_FixedLegAnagraphics


//------------------------------------------------------------------------------------------------------

void HL_FixedLegAnagraphics::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------


void HL_FixedLegAnagraphics::descriptionImpl(std::ostream & os) const
{

    HL_LegAnagraphics::descriptionImpl(os);
    hl_fillDescriptionStream(fixedRate_);




} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_FixedLegAnagraphics::checkAnagraphics() const
{

    HL_LegAnagraphics::checkAnagraphics();

} // end checkAnagraphics



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedLegAnagraphics: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableLegAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_VariableLegAnagraphics::HL_VariableLegAnagraphics()
{

    classDefaultInit();



} // end HL_VariableLegAnagraphics

//------------------------------------------------------------------------------------------------------

HL_VariableLegAnagraphics::~HL_VariableLegAnagraphics()
{} // end ~HL_VariableLegAnagraphics


//------------------------------------------------------------------------------------------------------

void HL_VariableLegAnagraphics::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------


void HL_VariableLegAnagraphics::descriptionImpl(std::ostream & os) const
{

    HL_LegAnagraphics::descriptionImpl(os);
    hl_fillDescriptionStream(basketComposition_);

    hl_fillDescriptionStream(fixingSettlementDays_);
    hl_fillDescriptionStream(fixingBusinessDayConvention_);



} // end descriptionImpl


//------------------------------------------------------------------------------------------------------

void HL_VariableLegAnagraphics::checkAnagraphics() const
{

    HL_LegAnagraphics::checkAnagraphics();

    HL_PNN(basketComposition_);


} // end checkAnagraphics


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableLegAnagraphics: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_SwapAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_SwapAnagraphics::HL_SwapAnagraphics()
{

    classDefaultInit();



} // end HL_SwapAnagraphics

//------------------------------------------------------------------------------------------------------

HL_SwapAnagraphics::~HL_SwapAnagraphics()
{} // end ~HL_SwapAnagraphics


//------------------------------------------------------------------------------------------------------

void HL_SwapAnagraphics::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------


void HL_SwapAnagraphics::descriptionImpl(std::ostream & os) const
{

    HL_Anagraphics::descriptionImpl(os);
    hl_fillDescriptionStream(receiveLegAnagraphics_);
    hl_fillDescriptionStream(payLegAnagraphics_);




} // end descriptionImpl



//------------------------------------------------------------------------------------------------------

void HL_SwapAnagraphics::checkAnagraphics() const
{


    HL_Anagraphics::checkAnagraphics();

    HL_PNN(receiveLegAnagraphics_);
    HL_PNN(payLegAnagraphics_);


} // end checkAnagraphics



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_SwapAnagraphics: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_HL_FixedLegAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_FixedLegAnagraphicsPtr HL_TEST_get_HL_FixedLegAnagraphics(
        const HL_CcyCodePtr& ccyCode,
        const date & spotDate,
                                                             const HL_Period & scheduleLength,
                                                             const HL_Period & couponFrequency,
                                                             HLR fixedRate)
{

    HLI payDateSettlementDays=0;
    HL_BusinessDayConvention payDateBusinessDayConvention=HL_BusinessDayConvention_Following;
    HL_DccPtr accrualDcc(new HLDT::HL_Dcc_Act360);

    HL_ScheduleAnagraphicsPtr scheduleAnagraphics =  HL_TEST_get_HL_ScheduleAnagraphicsFromSpotDate(
                spotDate,
                scheduleLength,
                couponFrequency
                );

    HL_FixedLegAnagraphicsPtr fixedLegAnagraphics(new HLAN::HL_FixedLegAnagraphics);


    fixedLegAnagraphics->set_scheduleAnagraphics(scheduleAnagraphics);

    fixedLegAnagraphics->set_accrualDcc(accrualDcc);
    fixedLegAnagraphics->set_payDateSettlementDays(payDateSettlementDays);
    fixedLegAnagraphics->set_payDateBusinessDayConvention(payDateBusinessDayConvention);


    fixedLegAnagraphics->set_fixedRate(fixedRate);

    fixedLegAnagraphics->set_ccyCode(ccyCode);


    return fixedLegAnagraphics;

} // end HL_TEST_get_HL_FixedLegAnagraphics





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_HL_UnderlyingDeliveryLegAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_UnderlyingDeliveryLegAnagraphicsPtr HL_TEST_get_HL_UnderlyingDeliveryLegAnagraphics(
        const HL_CcyCodePtr& ccyCode,
        const date & spotDate,
        const HL_Period & scheduleLength,
        const HL_Period & couponFrequency,
        const HL_BasketCompositionPtr & basketComposition,
        const HL_BasketPtr & basket
        )
{

    HLI payDateSettlementDays=0;
    HL_BusinessDayConvention payDateBusinessDayConvention=HL_BusinessDayConvention_Following;
    HL_DccPtr accrualDcc(new HLDT::HL_Dcc_Act360);

    HL_ScheduleAnagraphicsPtr scheduleAnagraphics =  HL_TEST_get_HL_ScheduleAnagraphicsFromSpotDate(
                spotDate,
                scheduleLength,
                couponFrequency
                );


    HL_UnderlyingDeliveryLegAnagraphicsPtr underlyingDeliveryLegAnagraphics
            (new HLAN::HL_UnderlyingDeliveryLegAnagraphics);


    underlyingDeliveryLegAnagraphics->set_scheduleAnagraphics(scheduleAnagraphics);

    underlyingDeliveryLegAnagraphics->set_accrualDcc(accrualDcc);
    underlyingDeliveryLegAnagraphics->set_payDateSettlementDays(payDateSettlementDays);
    underlyingDeliveryLegAnagraphics->set_payDateBusinessDayConvention(payDateBusinessDayConvention);


    underlyingDeliveryLegAnagraphics->set_basketComposition(basketComposition);

    underlyingDeliveryLegAnagraphics->set_basket(basket);

    underlyingDeliveryLegAnagraphics->set_ccyCode(ccyCode);


    underlyingDeliveryLegAnagraphics->set_fixingSettlementDays(-2);

    underlyingDeliveryLegAnagraphics->set_fixingBusinessDayConvention(
                HL_BusinessDayConvention_Preceding);

    return underlyingDeliveryLegAnagraphics;


} // end HL_TEST_get_HL_UnderlyingDeliveryLegAnagraphics


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_Basket_Ibor
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



HL_BasketPtr HL_TEST_get_Basket_Ibor(HLS nbMonths)
{

    HL_IborIndexCodePtr iborIndexCode =
            HLIR::HL_TEST_get_HL_IborIndexCode(nbMonths);



    HL_BasketCodePtr basketCode(new HLINS::HL_BasketCode);

    basketCode->set_sCode("HL_TEST_get_Basket_Ibor_BASKET_NAME");

    basketCode->set_ccyCode(iborIndexCode->get_ccyCode());


    HL_BasketPtr basket(new HLINS::HL_Basket);

    basket->set_HL_ObjCodePtr(basketCode);

    std::vector<HL_UnderlyingCodePtr> underlyingCodes(1, iborIndexCode);

    basket->set_underlyingCodes(underlyingCodes);


    std::vector<HLSTRING> underlyingHistoryTags(1, HLUND::defaultHistoryTag());


    basket->set_underlyingHistoryTags(underlyingHistoryTags);

    return basket;


} // end HL_TEST_get_Basket_Ibor




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_HL_get_SwapAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_SwapAnagraphicsPtr HL_TEST_HL_get_SwapAnagraphics(const date & spotDate,
                                                     const HL_Period & scheduleLength,
                                                     const HL_Period & fixedCouponFrequency,
                                                     HLR fixedRate,
                                                     const HL_Period & floatCouponFrequency,
                                                     HLS iborNbMonths)
{

    HL_CcyCodePtr ccyCode = HLCCY::HL_TEST_get_HL_CcyCode();

    HL_FixedLegAnagraphicsPtr fixedLegAnagraphics = HL_TEST_get_HL_FixedLegAnagraphics(
                ccyCode,
                spotDate,
                scheduleLength,
                fixedCouponFrequency,
                fixedRate);



    HL_QuantBasketCompositionPtr quantBasketComposition(new HLINS::HL_QuantBasketComposition);

    quantBasketComposition->set_basketRuleType(HL_BasketRuleType_PlainSum);

    quantBasketComposition->set_issueTime(ptime(spotDate));

    VEC issueTimeQuantities(1, 1.);

    quantBasketComposition->set_issueTimeQuantities(issueTimeQuantities);


    const HL_BasketPtr & floatBasket = HL_TEST_get_Basket_Ibor(iborNbMonths);


    HL_UnderlyingDeliveryLegAnagraphicsPtr underlyingDeliveryLegAnagraphics =
            HL_TEST_get_HL_UnderlyingDeliveryLegAnagraphics(
                ccyCode,
                spotDate,
                scheduleLength,
                floatCouponFrequency,
                quantBasketComposition,
                floatBasket
                );

    HL_SwapAnagraphicsPtr swapAnagraphics(new HLAN::HL_SwapAnagraphics);


    swapAnagraphics->set_receiveLegAnagraphics(underlyingDeliveryLegAnagraphics);


    swapAnagraphics->set_payLegAnagraphics(fixedLegAnagraphics);

    return swapAnagraphics;

} // end HL_TEST_HL_get_SwapAnagraphics




} // end namespace HL_Anagraphics
} // end namespace HL_Instruments
} //end namespace HorizonLib
