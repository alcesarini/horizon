/**
FILE NAME= hl_pricingEngine.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140902
*/

#include <hl/pricingEngines/hl_pricingEngine.h>
#include <hl/instruments/hl_cashFlow.h>
#include <hl/underlyings/interestRates/hl_iborIndex.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLPE::HL_PricingEngineInput);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLPE::HL_PricingEngineOutput);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLPE::HL_PricingEngineInputKey);



namespace HorizonLib
{
namespace HL_PricingEngines
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineInput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_PricingEngineInput::HL_PricingEngineInput()
{
    classDefaultInit();

} // end HL_PricingEngineInput

//------------------------------------------------------------------------------------------------------

HL_PricingEngineInput::~HL_PricingEngineInput()
{
} // end ~HL_PricingEngineInput

//------------------------------------------------------------------------------------------------------

void HL_PricingEngineInput::classDefaultInit()
{

    instrumentPtr_=NULL;


} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_PricingEngineInput::descriptionImpl(std::ostream & os) const
{


    os << "HL_PricingEngineInput:\n";

    HLOBJ::HL_MachineInput::descriptionImpl(os);

    hl_fillDescriptionStream(mktDataCollector_);
    hl_fillDescriptionStream(get_instrumentPtr());
    hl_fillDescriptionStream(riskFreeDiscounting_);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------


void HL_PricingEngineInput::check() const
{


    HL_MachineInput::check();

    HL_PNN(mktDataCollector_);
    HL_PNN(get_instrumentPtr());
    HL_PNN(riskFreeDiscounting_);


    HL_SR(get_instrumentPtr()->hl_CcyCode()==riskFreeDiscounting_->get_ccyCode());


} // end check


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineInput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineInputKey
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_PricingEngineInputKey::HL_PricingEngineInputKey()
{
    classDefaultInit();

} // end HL_PricingEngineInputKey

//------------------------------------------------------------------------------------------------------

HL_PricingEngineInputKey::~HL_PricingEngineInputKey()
{
} // end ~HL_PricingEngineInputKey

//------------------------------------------------------------------------------------------------------

void HL_PricingEngineInputKey::classDefaultInit()
{

} // end classDefaultInit



//------------------------------------------------------------------------------------------------------

void HL_PricingEngineInputKey::descriptionImpl(std::ostream & os) const
{


    os << "HL_PricingEngineInputKey:\n";

    HLOBJ::HL_MachineInputKey::descriptionImpl(os);
    hl_fillDescriptionStream(refDate_);
    hl_fillDescriptionStream(instrumentCode_);
    hl_fillDescriptionStream(riskFreeDiscounting_);



} // end descriptionImpl


//------------------------------------------------------------------------------------------------------

HL_Order HL_PricingEngineInputKey::getOrder(const HL_MachineInputKey & machineInputKey) const
{

    HL_DYN_C_PTR_CAST(const HL_PricingEngineInputKey *, externalPricingEngineInputKey, &machineInputKey);

    HL_PLAIN_ORDER_COMPARE(refDate_, externalPricingEngineInputKey->refDate_);

    HL_PLAIN_ORDER_COMPARE(instrumentCode_, externalPricingEngineInputKey->instrumentCode_);

    HL_PLAIN_ORDER_COMPARE(riskFreeDiscounting_, externalPricingEngineInputKey->riskFreeDiscounting_);


    return HL_Order_1_Eq_2;

} // end getOrder




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_PricingEngineOutput::HL_PricingEngineOutput()
{
    classDefaultInit();

} // end HL_PricingEngineOutput

//------------------------------------------------------------------------------------------------------

HL_PricingEngineOutput::~HL_PricingEngineOutput()
{
} // end ~HL_PricingEngineOutput

//------------------------------------------------------------------------------------------------------

void HL_PricingEngineOutput::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_PricingEngineOutput::descriptionImpl(std::ostream & os) const
{


    os << "HL_PricingEngineOutput:\n";

    HLOBJ::HL_MachineOutput::descriptionImpl(os);

    hl_fillDescriptionStream(refTime_);
    hl_fillDescriptionStream(instrumentOutput_);



} // end descriptionImpl



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngine
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_PricingEngine::HL_PricingEngine()
{

    classDefaultInit();



} // end HL_PricingEngine

//------------------------------------------------------------------------------------------------------

HL_PricingEngine::~HL_PricingEngine()
{
} // end ~HL_PricingEngine


//------------------------------------------------------------------------------------------------------

void HL_PricingEngine::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_PricingEngine::descriptionImpl(std::ostream & os) const
{
    HLOBJ::HL_Machine::descriptionImpl(os);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------


void HL_PricingEngine::buildInputKey(const HL_MachineInputPtr & input,
                                     HL_MachineInputKeyPtr & machineInputKey) const
{

    HL_Machine::buildInputKey(input, machineInputKey);


    HL_DYN_SHARED_PTR_CAST_OPERATION(HL_PricingEngineInput/*OutPtrType*/,
                                     pricingEngineDisposableData_.input/*outPtr*/,
                                     input/*inPtr*/);

    HL_DYN_SHARED_PTR_CAST_OPERATION(HL_PricingEngineInputKey/*OutPtrType*/,
                                     pricingEngineDisposableData_.inputKey/*outPtr*/,
                                     machineInputKey/*inPtr*/);


    pricingEngineDisposableData_.inputKey->set_refDate(
                pricingEngineDisposableData_.input->get_mktDataCollector()->get_refDate());

    pricingEngineDisposableData_.inputKey->set_instrumentCode(
                pricingEngineDisposableData_.input->get_instrumentPtr()->get_instrumentCode());

    pricingEngineDisposableData_.inputKey->set_riskFreeDiscounting(
                pricingEngineDisposableData_.input->get_riskFreeDiscounting());


} // end buildInputKey




//------------------------------------------------------------------------------------------------------

HL_MachineOutputPtr HL_PricingEngine::doJobImpl() const
{



    HL_PricingEngineOutputPtr pricingEngineOutput =  performEngineComputations();


    // set additional computation info
    pricingEngineOutput->set_refTime(get_refTime());


    return pricingEngineOutput;


} // end doJobImpl




} // end namespace HL_PricingEngines
} //end namespace HorizonLib
