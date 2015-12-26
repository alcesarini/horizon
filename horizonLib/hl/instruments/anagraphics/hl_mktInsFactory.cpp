/**
FILE NAME= hl_mktInsFactory.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20141208
*/

#include <hl/instruments/anagraphics/hl_mktInsFactory.h>
#include <hl/instruments/hl_vanillaCashFlow.h>


namespace HorizonLib
{
namespace HL_Instruments
{
namespace HL_Anagraphics
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InsFactory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_InsFactory::HL_InsFactory()
{

    classDefaultInit();



} // end HL_InsFactory

//------------------------------------------------------------------------------------------------------

HL_InsFactory::~HL_InsFactory()
{} // end ~HL_InsFactory


//------------------------------------------------------------------------------------------------------

void HL_InsFactory::classDefaultInit()
{

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

HL_InstrumentPtr HL_InsFactory::build_instrument(const HL_AnagraphicsPtr & anagraphics) const
{

    HL_PNN(anagraphics);

    anagraphics->checkAnagraphics();

    return build_instrument_impl(anagraphics);

} // end build_instrument



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InsFactory: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_LegInsFactory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_LegInsFactory::HL_LegInsFactory()
{

    classDefaultInit();



} // end HL_LegInsFactory

//------------------------------------------------------------------------------------------------------

HL_LegInsFactory::~HL_LegInsFactory()
{} // end ~HL_LegInsFactory


//------------------------------------------------------------------------------------------------------

void HL_LegInsFactory::classDefaultInit()
{

} // end classDefaultInit







//------------------------------------------------------------------------------------------------------

HL_CashFlowStructurePtr HL_LegInsFactory::build_cashFlowStructure(const HL_AccrualPeriodPtr & accrualPeriod) const
{
    HL_CashFlowStructurePtr cashFlowStructure(new HLINS::HL_CashFlowStructure);



    cashFlowStructure->set_accrualPeriod(accrualPeriod);

    cashFlowStructure->set_notional(1);

    cashFlowStructure->set_payoffLeverage(1);

    cashFlowStructure->set_spread(0);

    cashFlowStructure->set_dccPtr(legAnagraphics_->get_accrualDcc());

    HL_ScheduleAnagraphicsPtr scheduleAnagraphics = legAnagraphics_->get_scheduleAnagraphics();


    date payDate = get_calendar()->advance(
                accrualPeriod->get_accrualEndDate(),
                HL_Period(legAnagraphics_->get_payDateSettlementDays(), HL_PeriodUnit_Days),
                legAnagraphics_->get_payDateBusinessDayConvention(),
                false/*send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth*/
                );

    cashFlowStructure->set_payDate(payDate);



    return cashFlowStructure;

} // end build_CashFlowStructure


//------------------------------------------------------------------------------------------------------


HL_ObjCodePtr HL_LegInsFactory::couponCodeBuildHelper(const HL_CashFlowStructurePtr &cashFlowStructure) const
{
    HL_CashFlowCodePtr couponCode = instantiateCouponCodeImpl();

    HL_PNN(couponCode);

    std::stringstream ss;
    ss << "COUPON_CODE=" << legAnagraphics_->get_cashFlowType() << "->" << *cashFlowStructure;

    couponCode->set_sCode(ss.str());

    couponCode->set_ccyCode(legAnagraphics_->get_ccyCode());

    return couponCode;


} // end couponCodeBuildHelper

//------------------------------------------------------------------------------------------------------

HL_InstrumentPtr HL_LegInsFactory::build_instrument_impl(const HL_AnagraphicsPtr & anagraphics) const
{

    HL_DYN_SHARED_PTR_CAST_OPERATION(HL_LegAnagraphics, legAnagraphics_, anagraphics);


    setDerivedLegAnagraphics();

    HL_ScheduleAnagraphicsPtr scheduleAnagraphics = legAnagraphics_->get_scheduleAnagraphics();

    HL_PNN(scheduleAnagraphics);

    HL_SchedulePtr schedule = buildSchedule(scheduleAnagraphics);

    HLS nbCoupons = schedule->nbCoupons();


    std::vector<HL_CashFlowPtr> cashFlows(nbCoupons);



    for(HLS couponIdx = 0;couponIdx<nbCoupons;++couponIdx)
    {

        const HL_AccrualPeriodPtr & accrualPeriod = schedule->accrualPeriod(couponIdx);


        HL_CashFlowStructurePtr cashFlowStructure = build_cashFlowStructure(accrualPeriod);

        cashFlows[couponIdx] = build_coupon(cashFlowStructure);



    } // end for couponIdx



    HL_CashFlowCollectionInstrumentPtr cashFlowCollectionIns(new HLINS::HL_CashFlowCollectionInstrument);

    cashFlowCollectionIns->set_cashFlows(cashFlows);


    return cashFlowCollectionIns;


} // end build_instrument


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_LegInsFactory: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedLegInsFactory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_FixedLegInsFactory::HL_FixedLegInsFactory()
{

    classDefaultInit();



} // end HL_FixedLegInsFactory

//------------------------------------------------------------------------------------------------------

HL_FixedLegInsFactory::~HL_FixedLegInsFactory()
{} // end ~HL_FixedLegInsFactory


//------------------------------------------------------------------------------------------------------

void HL_FixedLegInsFactory::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_FixedLegInsFactory::setDerivedLegAnagraphics() const
{


    HL_DYN_SHARED_PTR_CAST_OPERATION(HLAN::HL_FixedLegAnagraphics, fixedLegAnagraphics_, legAnagraphics_);




} // end setDerivedLegAnagraphics


//------------------------------------------------------------------------------------------------------

HL_CashFlowPtr HL_FixedLegInsFactory::build_coupon(const HL_CashFlowStructurePtr &cashFlowStructure) const
{


    HL_FixedCashFlowPtr fixedCashFlow(new HLINS::HL_FixedCashFlow);

    fixedCashFlow->set_cashFlowStructure(cashFlowStructure);

    fixedCashFlow->set_fixedRate(fixedLegAnagraphics_->get_fixedRate());



    fixedCashFlow->set_HL_ObjCodePtr(couponCodeBuildHelper(cashFlowStructure));



    return fixedCashFlow;


} // end build_coupon


//------------------------------------------------------------------------------------------------------

HL_CashFlowCodePtr HL_FixedLegInsFactory::instantiateCouponCodeImpl() const
{
    HL_FixedCashFlowCodePtr fixedCashFlowCode(new HLINS::HL_FixedCashFlowCode);
    return fixedCashFlowCode;
} // end instantiateCouponCodeImpl

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedLegInsFactory: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableLegInsFactory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_VariableLegInsFactory::HL_VariableLegInsFactory()
{

    classDefaultInit();



} // end HL_VariableLegInsFactory

//------------------------------------------------------------------------------------------------------

HL_VariableLegInsFactory::~HL_VariableLegInsFactory()
{} // end ~HL_VariableLegInsFactory


//------------------------------------------------------------------------------------------------------

void HL_VariableLegInsFactory::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_VariableLegInsFactory::setDerivedLegAnagraphics() const
{


    HL_DYN_SHARED_PTR_CAST_OPERATION(HLAN::HL_UnderlyingDeliveryLegAnagraphics,
                                     underlyingDeliveryLegAnagraphics_,
                                     legAnagraphics_);




} // end setDerivedLegAnagraphics


//------------------------------------------------------------------------------------------------------

HL_CashFlowPtr HL_VariableLegInsFactory::build_coupon(const HL_CashFlowStructurePtr &cashFlowStructure) const
{


    HL_UnderlyingDeliveryCashFlowPtr underlyingDeliveryCashFlow(new HLINS::HL_UnderlyingDeliveryCashFlow);

    underlyingDeliveryCashFlow->set_cashFlowStructure(cashFlowStructure);


    underlyingDeliveryCashFlow->set_basketComposition(
                underlyingDeliveryLegAnagraphics_->get_basketComposition());


    underlyingDeliveryCashFlow->set_basketPtr(underlyingDeliveryLegAnagraphics_->get_basket());


    underlyingDeliveryCashFlow->set_HL_ObjCodePtr(couponCodeBuildHelper(cashFlowStructure));


    date fixingDate = get_calendar()->advance(
                cashFlowStructure->get_accrualStartDate(),
                HL_Period(underlyingDeliveryLegAnagraphics_->get_fixingSettlementDays(), HL_PeriodUnit_Days),
                underlyingDeliveryLegAnagraphics_->get_fixingBusinessDayConvention(),
                false/*send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth*/
                );


    underlyingDeliveryCashFlow->set_nominalFixingTime(ptime(fixingDate));



    return underlyingDeliveryCashFlow;


} // end build_coupon


//------------------------------------------------------------------------------------------------------

HL_CashFlowCodePtr HL_VariableLegInsFactory::instantiateCouponCodeImpl() const
{
    HL_UnderlyingDeliveryCashFlowCodePtr underlyingDeliveryCashFlowCode(
                new HLINS::HL_UnderlyingDeliveryCashFlowCode);

    return underlyingDeliveryCashFlowCode;
} // end instantiateCouponCodeImpl



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableLegInsFactory: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------







//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_SwapInsFactory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_SwapInsFactory::HL_SwapInsFactory()
{

    classDefaultInit();



} // end HL_SwapInsFactory

//------------------------------------------------------------------------------------------------------

HL_SwapInsFactory::~HL_SwapInsFactory()
{} // end ~HL_SwapInsFactory


//------------------------------------------------------------------------------------------------------

void HL_SwapInsFactory::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------


HL_InstrumentPtr HL_SwapInsFactory::build_instrument_impl(const HL_AnagraphicsPtr & anagraphics) const
{

    HL_DYN_SHARED_PTR_CAST(HL_SwapAnagraphics, swapAnagraphics, anagraphics);

    std::vector<HL_InstrumentPtr> legs;

    HL_InstrumentPtr receiveLegIns=buildIns(swapAnagraphics->get_receiveLegAnagraphics());

    legs.push_back(receiveLegIns);

    HL_InstrumentPtr payLegIns=buildIns(swapAnagraphics->get_payLegAnagraphics());

    legs.push_back(payLegIns);

    HL_InstrumentPtr swapIns=HLINS::mergeInstruments(legs);

    return swapIns;

} // end setDerivedLegAnagraphics


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_SwapInsFactory: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_InsFactoryPtr getInsFactory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_InsFactoryPtr getInsFactory(const HL_AnagraphicsPtr & anagraphics)
{

    HL_PNN(anagraphics);

    HL_InsFactoryPtr insFactory;

    switch(anagraphics->anagraphicsType())
    {
    case HL_AnagraphicsType_FixedLegAnagraphics:
        insFactory.reset(new HL_FixedLegInsFactory);
        break;
    case HL_AnagraphicsType_UnderlyingDeliveryLegAnagraphics:
        insFactory.reset(new HL_UnderlyingDeliveryLegInsFactory);
        break;
    case HL_AnagraphicsType_SwapAnagraphics:
        insFactory.reset(new HL_SwapInsFactory);
        break;
    default:
        HL_FAIL("invalid anagraphics->anagraphicsType()=" << anagraphics->anagraphicsTypeString());
    } // end switch get_cashFlowType


    return insFactory;



} // end getInsFactory



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_InstrumentPtr buildIns
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_InstrumentPtr buildIns(const HL_AnagraphicsPtr & anagraphics)
{

    HL_InsFactoryPtr insFactory = getInsFactory(anagraphics);

    HL_InstrumentPtr ins = insFactory->build_instrument(anagraphics);

    return ins;

} // end buildIns



} // end namespace HL_Anagraphics
} // end namespace HL_Instruments
} //end namespace HorizonLib
