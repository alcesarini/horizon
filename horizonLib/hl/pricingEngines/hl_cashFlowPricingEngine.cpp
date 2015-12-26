/**
FILE NAME= hl_cashFlowPricingEngine.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20141030
*/

#include <hl/pricingEngines/hl_cashFlowPricingEngine.h>
#include <hl/instruments/hl_vanillaCashFlow.h>
#include <hl/underlyings/interestRates/hl_iborIndex.h>

/*
 *  commented since they would repeat the ones of HL_PricingEngineInput and HL_PricingEngineOutput
 * being the former a typedef of the the latters.
 * */
//HL_SERIALIZATION_CLASS_EXPORT_GUID(HLPE::HL_CashFlowPricingEngineInput);
//HL_SERIALIZATION_CLASS_EXPORT_GUID(HLPE::HL_CashFlowPricingEngineOutput);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLPE::HL_CashFlowPricingEngineInputKey);



namespace HorizonLib
{
namespace HL_PricingEngines
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineInput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineInput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineInputKey
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CashFlowPricingEngineInputKey::HL_CashFlowPricingEngineInputKey()
{
    classDefaultInit();

} // end HL_CashFlowPricingEngineInputKey

//------------------------------------------------------------------------------------------------------

HL_CashFlowPricingEngineInputKey::~HL_CashFlowPricingEngineInputKey()
{
} // end ~HL_CashFlowPricingEngineInputKey

//------------------------------------------------------------------------------------------------------

void HL_CashFlowPricingEngineInputKey::classDefaultInit()
{

} // end classDefaultInit



//------------------------------------------------------------------------------------------------------

void HL_CashFlowPricingEngineInputKey::descriptionImpl(std::ostream & os) const
{


    os << "HL_CashFlowPricingEngineInputKey:\n";

    HL_PricingEngineInputKey::descriptionImpl(os);
    hl_fillDescriptionStream(zcToPayDate_);



} // end descriptionImpl


//------------------------------------------------------------------------------------------------------

HL_Order HL_CashFlowPricingEngineInputKey::getOrder(const HL_MachineInputKey & machineInputKey) const
{

    HL_Order baseClassOrder = HL_PricingEngineInputKey::getOrder(machineInputKey);

    if(baseClassOrder!=HL_Order_1_Eq_2)
        return baseClassOrder;


    HL_DYN_C_PTR_CAST(const HL_CashFlowPricingEngineInputKey *,
                      externalCashFlowPricingEngineInputKey,
                      &machineInputKey);



    HL_PLAIN_ORDER_COMPARE(zcToPayDate_, externalCashFlowPricingEngineInputKey->zcToPayDate_);




    return HL_Order_1_Eq_2;

} // end getOrder


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngine
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CashFlowPricingEngine::HL_CashFlowPricingEngine()
{

    classDefaultInit();



} // end HL_CashFlowPricingEngine

//------------------------------------------------------------------------------------------------------

HL_CashFlowPricingEngine::~HL_CashFlowPricingEngine()
{
} // end ~HL_CashFlowPricingEngine


//------------------------------------------------------------------------------------------------------

void HL_CashFlowPricingEngine::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_CashFlowPricingEngine::descriptionImpl(std::ostream & os) const
{
    HL_PricingEngine::descriptionImpl(os);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

const std::set<HLINS::HL_CashFlowType> & HL_CashFlowPricingEngine::get_allowedCashFlowTypes() const
{

    return get_cashFlowPricingEngineStaticAssociation()->get_allowedCashFlowTypes(get_cashFlowPricingEngineType());


} // end get_allowedCashFlowTypes

//------------------------------------------------------------------------------------------------------

void HL_CashFlowPricingEngine::ensureCashFlowTypeAllowed(HLINS::HL_CashFlowType cashFlowType) const
{

    ensureCashFlowPricingEngineAllowed(get_cashFlowPricingEngineType(), cashFlowType);

} // end ensureCashFlowTypeAllowed


//------------------------------------------------------------------------------------------------------

HL_FwdMeasurePtr HL_CashFlowPricingEngine::getRiskFreeDiscountingFwdMeasure() const
{

    HL_FwdMeasurePtr fwdMeasure(new HLMA::HL_FwdMeasure);

    fwdMeasure->set_riskFreeDiscounting(
                cashFlowPricingEngineDisposableData_.input->get_riskFreeDiscounting());

    fwdMeasure->set_payDate(cashFlowPricingEngineDisposableData_.cashFlow->get_payDate());

    return fwdMeasure;

} // end getRiskFreeDiscountingFwdMeasure

//------------------------------------------------------------------------------------------------------

void HL_CashFlowPricingEngine::buildInputKey(const HL_MachineInputPtr & input,
                                             HL_MachineInputKeyPtr & machineInputKey) const
{



    HL_PricingEngine::buildInputKey(input, machineInputKey);

    HL_DYN_SHARED_PTR_CAST_OPERATION(HL_CashFlowPricingEngineInput/*OutPtrType*/,
                                     cashFlowPricingEngineDisposableData_.input/*outPtr*/,
                                     input/*inPtr*/);

    HL_DYN_SHARED_PTR_CAST_OPERATION(HL_CashFlowPricingEngineInputKey/*OutPtrType*/,
                                     cashFlowPricingEngineDisposableData_.inputKey/*outPtr*/,
                                     machineInputKey/*inPtr*/);



    const HL_MktDataCollectorPtr & mktDataCollector =
            cashFlowPricingEngineDisposableData_.input->get_mktDataCollector();


    const HLINS::HL_Instrument * instrument = cashFlowPricingEngineDisposableData_.input->get_instrumentPtr();


    HL_DYN_C_PTR_CAST_OPERATION(const HLINS::HL_CashFlow */*OutPtrType*/,
                                cashFlowPricingEngineDisposableData_.cashFlow/*outPtr*/,
                                instrument/*inPtr*/);

    ensureCashFlowTypeAllowed(cashFlowPricingEngineDisposableData_.cashFlow->get_cashFlowType());


    const date & payDate = cashFlowPricingEngineDisposableData_.cashFlow->get_payDate();


    const HL_TermStructureCodePtr & riskFreeDiscountingTermStructureCode =
            cashFlowPricingEngineDisposableData_.input->get_riskFreeDiscountingTermStructureCode();



    HL_TermStructurePtr riskFreeDiscountingTermStructure =
            mktDataCollector->get_mktData<HL_TermStructurePtr>(riskFreeDiscountingTermStructureCode);


    cashFlowPricingEngineDisposableData_.inputKey->zcToPayDate_=riskFreeDiscountingTermStructure->df(payDate);


    cashFlowPricingEngineDisposableData_.cashFlowStructure=
            cashFlowPricingEngineDisposableData_.cashFlow->get_cashFlowStructure();




} // end buildInputKey

//------------------------------------------------------------------------------------------------------

HL_PricingEngineOutputPtr HL_CashFlowPricingEngine::performEngineComputations() const
{


    instantiateCashFlowPricingOutput();

    fillCashFlowPricingOutput();

    cashFlowPricingEngineDisposableData_.cashFlowPricingOutput->set_payoff(computeCashFlowPayoff());

    /*
    Being this method at a base class level, you may add all computation statisics (time, etc..) here.
    */
    instantiateCashFlowPricingEngineOutput();

    cashFlowPricingEngineDisposableData_.cashFlowPricingEngineOutput
            ->set_instrumentOutput(cashFlowPricingEngineDisposableData_.cashFlowPricingOutput);

    return cashFlowPricingEngineDisposableData_.cashFlowPricingEngineOutput;


} // end performEngineComputations


//------------------------------------------------------------------------------------------------------

void HL_CashFlowPricingEngine::fillCashFlowPricingOutput() const
{

    HL_PNN(cashFlowPricingEngineDisposableData_.cashFlowPricingOutput);

    cashFlowPricingEngineDisposableData_.cashFlowPricingOutput->set_cashFlowStructure(cashFlowPricingEngineDisposableData_.cashFlowStructure);

    cashFlowPricingEngineDisposableData_.cashFlowPricingOutput->set_zcToPayDate(cashFlowPricingEngineDisposableData_.inputKey->zcToPayDate_);

    cashFlowPricingEngineDisposableData_.cashFlowPricingOutput->set_isPayoffDeterministic(
                isPayoffDeterministic());


} // end fillCashFlowPricingOutput





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineAssociation
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CashFlowPricingEngineAssociation::HL_CashFlowPricingEngineAssociation()
{

    classDefaultInit();



} // end HL_CashFlowPricingEngineAssociation

//------------------------------------------------------------------------------------------------------

HL_CashFlowPricingEngineAssociation::~HL_CashFlowPricingEngineAssociation()
{
} // end ~HL_CashFlowPricingEngineAssociation


//------------------------------------------------------------------------------------------------------

void HL_CashFlowPricingEngineAssociation::classDefaultInit()
{
    associations_.clear();

    associations_[HL_CashFlowPricingEngineType_FixedCashFlow].insert(HLINS::HL_CashFlowType_Fixed);

    associations_[HL_CashFlowPricingEngineType_UnderlyingDelivery].insert(HLINS::HL_CashFlowType_UnderlyingDelivery);

    associations_[HL_CashFlowPricingEngineType_AnalyticVanilla].insert(HLINS::HL_CashFlowType_Vanilla);

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_CashFlowPricingEngineAssociation::descriptionImpl(std::ostream & os) const
{
    Descriptable::descriptionImpl(os);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

const std::set<HLINS::HL_CashFlowType> &
HL_CashFlowPricingEngineAssociation::get_allowedCashFlowTypes(HL_CashFlowPricingEngineType cashFlowPricingEngineType) const
{


    std::map<HL_CashFlowPricingEngineType, std::set<HLINS::HL_CashFlowType> >::const_iterator c_it =
            associations_.find(cashFlowPricingEngineType);

    HL_SRE(c_it!=associations_.end(),
           "cashFlowPricingEngineType not in HL_CashFlowPricingEngineAssociation::associations_, "
           << "cashFlowPricingEngineType=" << getEnumString(cashFlowPricingEngineType));


    return c_it->second;

} // end get_AllowedCashFlowTypes


//------------------------------------------------------------------------------------------------------

std::set<HL_CashFlowPricingEngineType>
HL_CashFlowPricingEngineAssociation::get_allowedCashFlowPricingEngineTypes(HLINS::HL_CashFlowType cashFlowType) const
{


    HL_ENUM_CHECK(HLINS::HL_CashFlowType, cashFlowType);

    std::map<HL_CashFlowPricingEngineType, std::set<HLINS::HL_CashFlowType> >::const_iterator c_it
            =associations_.begin();

    std::set<HL_CashFlowPricingEngineType> cashFlowPricingEngineTypes;

    while(c_it!=associations_.end())
    {

        if(c_it->second.find(cashFlowType)!=c_it->second.end())
            cashFlowPricingEngineTypes.insert(c_it->first);
        c_it++;
    } // end while



    return cashFlowPricingEngineTypes;

} // end get_allowedCashFlowPricingEngineTypes


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineAssociation: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



HL_CashFlowPricingEngineAssociationPtr get_cashFlowPricingEngineStaticAssociation()
{


    static HL_CashFlowPricingEngineAssociationPtr cashFlowPricingEngineAssociation;

    if(!cashFlowPricingEngineAssociation)
        cashFlowPricingEngineAssociation.reset(new HL_CashFlowPricingEngineAssociation);

    return cashFlowPricingEngineAssociation;

} // end get_cashFlowPricingEngineStaticAssociation

//------------------------------------------------------------------------------------------------------

void ensureCashFlowPricingEngineAllowed(HL_CashFlowPricingEngineType cashFlowPricingEngineType,
                                    HLINS::HL_CashFlowType cashFlowType)
{

    HL_CashFlowPricingEngineAssociationPtr cashFlowPricingEngineAssociation=
            get_cashFlowPricingEngineStaticAssociation();

    const std::set<HLINS::HL_CashFlowType> & allowedCashFlowTypes =
            cashFlowPricingEngineAssociation->get_allowedCashFlowTypes(cashFlowPricingEngineType);

    HL_SRE(allowedCashFlowTypes.find(cashFlowType)!=allowedCashFlowTypes.end(),
           "cashFlowType=" << getEnumString(cashFlowType) << " cannot be managed by cashFlowPricingEngineType="
           << getEnumString(cashFlowPricingEngineType));


} // end ensureCashFlowPricingEngineAllowed


} // end namespace HL_PricingEngines
} //end namespace HorizonLib
