/**
FILE NAME= hl_pricingEngineFactory.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20150512
*/

#include <hl/pricingEngines/hl_pricingEngineFactory.h>
#include <hl/instruments/hl_cashFlow.h>
#include <hl/pricingEngines/hl_vanillaCashFlowPricingEngine.h>

namespace HorizonLib
{
namespace HL_PricingEngines
{




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineChoices
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_PricingEngineChoices::HL_PricingEngineChoices()
{

    classDefaultInit();



} // end HL_PricingEngineChoices

//------------------------------------------------------------------------------------------------------

HL_PricingEngineChoices::~HL_PricingEngineChoices()
{} // end ~HL_PricingEngineChoices


//------------------------------------------------------------------------------------------------------

void HL_PricingEngineChoices::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_PricingEngineChoices::descriptionImpl(std::ostream & os) const
{
    os << "HL_PricingEngineChoices:\n";

    Descriptable::descriptionImpl(os);


    BOOST_FOREACH(const MapType::value_type & v, associations_)
    {

        hl_fillDescriptionStream("HL_CashFlowType=" << v.first);
        hl_fillDescriptionStream("HL_CashFlowPricingEngineType=" << v.first);

    } // end for v

} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_PricingEngineChoices::setAssociation(HLINS::HL_CashFlowType cashFlowType,
                                             HL_CashFlowPricingEngineType cashFlowPricingEngineType)
{


    HL_ENUM_CHECK(HLINS::HL_CashFlowType, cashFlowType);

    HL_ENUM_CHECK(HL_CashFlowPricingEngineType, cashFlowPricingEngineType);


    bool alreadyExists;
    HL_CashFlowPricingEngineType & engineType = HL_mapFind(associations_, cashFlowType, alreadyExists);

    HL_SRE(!alreadyExists, "HL_CashFlowType already given: " << getEnumString(cashFlowType));

    ensureCashFlowPricingEngineAllowed(cashFlowPricingEngineType, cashFlowType);

    engineType=cashFlowPricingEngineType;

} // end setAssociation

//------------------------------------------------------------------------------------------------------


HL_CashFlowPricingEngineType
HL_PricingEngineChoices::get_cashFlowPricingEngineType(HLINS::HL_CashFlowType cashFlowType) const
{


    HL_ENUM_CHECK(HLINS::HL_CashFlowType, cashFlowType);

    MapType::const_iterator cIt = associations_.find(cashFlowType);

    HL_SRE(cIt!=associations_.end(), "HL_CashFlowType not given: " << getEnumString(cashFlowType));


    return cIt->second;

} // end get_cashFlowPricingEngineType


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineData
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_PricingEngineData::HL_PricingEngineData()
{

    classDefaultInit();



} // end HL_PricingEngineData

//------------------------------------------------------------------------------------------------------

HL_PricingEngineData::~HL_PricingEngineData()
{} // end ~HL_PricingEngineData


//------------------------------------------------------------------------------------------------------

void HL_PricingEngineData::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_PricingEngineData::descriptionImpl(std::ostream & os) const
{
    os << "HL_PricingEngineData:\n";

    Descriptable::descriptionImpl(os);


    hl_fillDescriptionStream(mktDataCollector_);
    hl_fillDescriptionStream(riskFreeDiscounting_);
    hl_fillDescriptionStream(pricingEngineChoices_);


} // end descriptionImpl





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineData: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineFactory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CashFlowPricingEngineFactory::HL_CashFlowPricingEngineFactory()
{

    classDefaultInit();



} // end HL_CashFlowPricingEngineFactory

//------------------------------------------------------------------------------------------------------

HL_CashFlowPricingEngineFactory::~HL_CashFlowPricingEngineFactory()
{} // end ~HL_CashFlowPricingEngineFactory


//------------------------------------------------------------------------------------------------------

void HL_CashFlowPricingEngineFactory::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_CashFlowPricingEngineFactory::descriptionImpl(std::ostream & os) const
{
    os << "HL_CashFlowPricingEngineFactory:\n";

    Descriptable::descriptionImpl(os);


    hl_fillDescriptionStream(pricingEngineData_);


} // end descriptionImpl



//------------------------------------------------------------------------------------------------------

HL_CashFlowPricingEnginePtr
HL_CashFlowPricingEngineFactory::get_cashFlowPricingEngine(const HL_CashFlowPtr & cashFlow)
{
    HL_PNN(cashFlow);

    HLINS::HL_CashFlowType cashFlowType = cashFlow->get_cashFlowType();

    HL_ENUM_CHECK(HLINS::HL_CashFlowType, cashFlowType);

    HL_PNN(pricingEngineData_);

    HL_CashFlowPricingEngineType cashFlowPricingEngineType =
            pricingEngineData_->get_pricingEngineChoices()->get_cashFlowPricingEngineType(cashFlowType);



    HL_CashFlowPricingEnginePtr cashFlowPricingEngine = instantiate_cashFlowPricingEngine(cashFlowPricingEngineType);


    HL_CashFlowPricingEngineInputPtr cashFlowPricingEngineInput = get_cashFlowPricingEngineInput(cashFlow);


    cashFlowPricingEngine->set_input(cashFlowPricingEngineInput);

    return cashFlowPricingEngine;


} // end get_cashFlowPricingEngine

//------------------------------------------------------------------------------------------------------

HL_CashFlowPricingEngineInputPtr HL_CashFlowPricingEngineFactory::get_cashFlowPricingEngineInput(const HL_CashFlowPtr & cashFlow) const
{


    HL_CashFlowPricingEngineInputPtr cashFlowPricingEngineInput(new HLPE::HL_CashFlowPricingEngineInput);

    cashFlowPricingEngineInput->set_mktDataCollector(pricingEngineData_->get_mktDataCollector());
    cashFlowPricingEngineInput->set_instrumentPtr(cashFlow.get() /* instrumentPtr */);
    cashFlowPricingEngineInput->set_riskFreeDiscounting(pricingEngineData_->get_riskFreeDiscounting());


    return cashFlowPricingEngineInput;

} // end get_cashFlowPricingEngineInput

//------------------------------------------------------------------------------------------------------

HL_CashFlowPricingEnginePtr HL_CashFlowPricingEngineFactory::instantiate_cashFlowPricingEngine(
        HL_CashFlowPricingEngineType cashFlowPricingEngineType) const
{

    HL_CashFlowPricingEnginePtr cashFlowPricingEngine;



    switch(cashFlowPricingEngineType)
    {
    case HLPE::HL_CashFlowPricingEngineType_FixedCashFlow:
        cashFlowPricingEngine.reset(new HLPE::HL_FixedCashFlowPricingEngine);
        break;
    case HLPE::HL_CashFlowPricingEngineType_UnderlyingDelivery:
        cashFlowPricingEngine.reset(new HLPE::HL_UnderlyingDeliveryCashFlowPricingEngine);
        break;
    case HLPE::HL_CashFlowPricingEngineType_AnalyticVanilla:
        cashFlowPricingEngine.reset(new HLPE::HL_AnalyticVanillaCashFlowPricingEngine);
        break;
    default:
        HL_FAIL("invalid cashFlowPricingEngineType " << getEnumString(cashFlowPricingEngineType));
    }; // end switch(cashFlowPricingEngineType)



    return cashFlowPricingEngine;


} // end instantiate_cashFlowPricingEngine

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineFactory: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------






//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// setPricingEngineIntoIns
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

void setPricingEngineIntoIns(const HL_InstrumentPtr & instrument,
                             const HL_PricingEngineDataPtr & pricingEngineData
                             )
{

    HL_PNN(instrument);

    HL_CashFlowPtr cashFlow = boost::dynamic_pointer_cast<HLINS::HL_CashFlow>(instrument);


    if(cashFlow){

        setPricingEngineIntoCashFlow(cashFlow, pricingEngineData);
    }else{

        HL_DYN_SHARED_PTR_CAST(HLINS::HL_CashFlowCollectionInstrument,
                               cashFlowCollectionInstrument,
                               instrument);

        const std::vector<HL_CashFlowPtr> & cashFlows = cashFlowCollectionInstrument->get_cashFlows();



        BOOST_FOREACH(const HL_CashFlowPtr & cashFlow, cashFlows)
        {


            setPricingEngineIntoCashFlow(cashFlow, pricingEngineData);

        } // end for cashFlow

    } // end if..else..




} // end setPricingEngineIntoIns


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// setPricingEngineIntoCashFlow
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


void setPricingEngineIntoCashFlow(const HL_CashFlowPtr & cashFlow,
                                  const HL_PricingEngineDataPtr & pricingEngineData)
{


    HL_CashFlowPricingEngineFactoryPtr cashFlowPricingEngineFactory(new HLPE::HL_CashFlowPricingEngineFactory);

    cashFlowPricingEngineFactory->set_pricingEngineData(pricingEngineData);


    HL_CashFlowPricingEnginePtr cashFlowPricingEngine =
            cashFlowPricingEngineFactory->get_cashFlowPricingEngine(cashFlow);


    cashFlow->set_pricingEngine(cashFlowPricingEngine);



} // end setPricingEngineIntoCashFlow






} // end namespace HL_PricingEngines
} //end namespace HorizonLib
