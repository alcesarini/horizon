/**
FILE NAME= hl_cashFlow.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140521
*/


#include <hl/instruments/hl_cashFlow.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_CashFlow);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_CashFlowCode);




namespace HorizonLib
{
namespace HL_Instruments
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowStructure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CashFlowStructure::HL_CashFlowStructure()
{

    classDefaultInit();



} // end HL_CashFlowStructure

//------------------------------------------------------------------------------------------------------

HL_CashFlowStructure::~HL_CashFlowStructure()
{
} // end ~HL_CashFlowStructure


//------------------------------------------------------------------------------------------------------

void HL_CashFlowStructure::classDefaultInit()
{
    notional_=0.;

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_CashFlowStructure::descriptionImpl(std::ostream & os) const
{

    os << "HL_CashFlowStructure:\n";

    Descriptable::descriptionImpl(os);

    hl_fillDescriptionStream(payDate_);
    hl_fillDescriptionStream(accrualPeriod_);
    hl_fillDescriptionStream(notional_);
    hl_fillDescriptionStream(payoffLeverage_);
    hl_fillDescriptionStream(spread_);
    hl_fillDescriptionStream(dccPtr_);


} // end descriptionImpl


//------------------------------------------------------------------------------------------------------

HL_Order HL_CashFlowStructure::getOrder(const HL_CashFlowStructure & cashFlowStructure) const
{

    return plainOrder(payDate_, cashFlowStructure.payDate_);



} // end getOrder

//------------------------------------------------------------------------------------------------------

void HL_CashFlowStructure::checkCashFlowStructure() const
{

    HL_PNN(accrualPeriod_);

    accrualPeriod_->checkAccrualPeriod();


    HL_PNN(dccPtr_);

} // end checkCashFlowStructure

//------------------------------------------------------------------------------------------------------

HLR HL_CashFlowStructure::tau(const date & d) const
{

    if(d<=get_accrualStartDate())
        return 0;


    HLR t = dccPtr_->yf(get_accrualStartDate(), std::min(get_accrualEndDate(), d));

    return t;


} // end tau



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CashFlowCode::HL_CashFlowCode()
{
    classDefaultInit();

} // end HL_CashFlowCode

//------------------------------------------------------------------------------------------------------

HL_CashFlowCode::~HL_CashFlowCode()
{
} // end ~HL_CashFlowCode

//------------------------------------------------------------------------------------------------------

void HL_CashFlowCode::classDefaultInit()
{

} // end classDefaultInit
//------------------------------------------------------------------------------------------------------

HLSTRING HL_CashFlowCode::objTypeImpl() const
{
    return "HL_CashFlowCode";
} // end objTypeImpl



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlow
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CashFlow::HL_CashFlow()
{

    classDefaultInit();



} // end HL_CashFlow

//------------------------------------------------------------------------------------------------------

HL_CashFlow::~HL_CashFlow()
{
} // end ~HL_CashFlow


//------------------------------------------------------------------------------------------------------

void HL_CashFlow::classDefaultInit()
{


} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_CashFlow::descriptionImpl(std::ostream & os) const
{
    os << "HL_CashFlow\n";
    /* do not call this to avoid infinite looping*/
    //HLINS::HL_Instrument::descriptionImpl(os);

    hl_fillDescriptionStream(cashFlowStructure_);
    HL_DESCRIBE_ENUM(os, get_cashFlowType());


} // end descriptionImpl



//------------------------------------------------------------------------------------------------------

void HL_CashFlow::set_HL_ObjCodePtr(const HL_ObjCodePtr & hl_ObjCodePtr)
{

    HL_EnginedInstrument::set_HL_ObjCodePtr(hl_ObjCodePtr);


    HL_DYN_SHARED_PTR_CAST_OPERATION(HL_CashFlowCode, cashFlowCode_ /*outPtr*/, hl_ObjCodePtr_ /*inPtr*/);



} // end set_HL_ObjCodePtr


//------------------------------------------------------------------------------------------------------

HL_Order HL_CashFlow::getOrder(const HL_CashFlow & hl_CashFlow) const
{

    return cashFlowStructure_->getOrder(*hl_CashFlow.get_cashFlowStructure());



} // end getOrder


//------------------------------------------------------------------------------------------------------

void HL_CashFlow::checkCashFlow() const
{

    HL_PNN(cashFlowStructure_);


    cashFlowStructure_->checkCashFlowStructure();



} // end checkCashFlow



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CashFlowPricingOutput::HL_CashFlowPricingOutput()
{
    classDefaultInit();

} // end HL_CashFlowPricingOutput

//------------------------------------------------------------------------------------------------------

HL_CashFlowPricingOutput::~HL_CashFlowPricingOutput()
{
} // end ~HL_CashFlowPricingOutput

//------------------------------------------------------------------------------------------------------

void HL_CashFlowPricingOutput::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_CashFlowPricingOutput::descriptionImpl(std::ostream & os) const
{


    os << "HL_CashFlowPricingOutput:\n";

    /* do not call this to avoid infinite looping*/
    //HLINS::HL_InstrumentOutput::descriptionImpl(os);

    hl_fillDescriptionStream(cashFlowStructure_);
    hl_fillDescriptionStream(payoff_);
    hl_fillDescriptionStream(zcToPayDate_);
    hl_fillDescriptionStream(isPayoffDeterministic_);
    hl_fillDescriptionStream(get_dirtyPrice());




} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

HLR HL_CashFlowPricingOutput::get_accrued(const date& d) const
{
    if(!get_isPayoffDeterministic())
        return 0;

    HLR accrued = get_notional()*get_rate()*tau(d);

    return accrued;
} // end get_accrued


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------








} // end namespace HL_Instruments
} //end namespace HorizonLib
