/**
FILE NAME= hl_baseIns.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131109
*/


#include <hl/instruments/hl_baseIns.h>
#include <hl/instruments/hl_cashFlow.h>
#include <hl/pricingEngines/hl_pricingEngine.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_Instrument);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_InstrumentCode);

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_CashFlowCollectionInstrument);

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_EnginedInstrument);

namespace HorizonLib
{
namespace HL_Instruments
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InstrumentOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_InstrumentOutput::HL_InstrumentOutput()
{
    classDefaultInit();

} // end HL_InstrumentOutput

//------------------------------------------------------------------------------------------------------

HL_InstrumentOutput::~HL_InstrumentOutput()
{
} // end ~HL_InstrumentOutput

//------------------------------------------------------------------------------------------------------

void HL_InstrumentOutput::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_InstrumentOutput::descriptionImpl(std::ostream & os) const
{


    os << "HL_InstrumentOutput:\n";

    HLOBJ::HL_MachineOutput::descriptionImpl(os);

    hl_fillDescriptionStream(get_dirtyPrice());


    HLS nbCashFlowPricingOutputs = get_nbCashFlowPricingOutputs();

    hl_fillDescriptionStream(nbCashFlowPricingOutputs);

    for(HLS cashFlowPricingOutputIdx=0;cashFlowPricingOutputIdx<nbCashFlowPricingOutputs;cashFlowPricingOutputIdx++)
    {
        hl_fillDescriptionStream(get_CashFlowPricingOutput(cashFlowPricingOutputIdx));

    } // end for cashFlowPricingOutputIdx



} // end descriptionImpl
//------------------------------------------------------------------------------------------------------

HLR HL_InstrumentOutput::get_dirtyPrice() const
{


    HLR dirtyPrice=0;


    HLS nbCashFlowPricingOutputs = get_nbCashFlowPricingOutputs();

    for(HLS cashFlowPricingOutputIdx=0;cashFlowPricingOutputIdx<nbCashFlowPricingOutputs;cashFlowPricingOutputIdx++)
    {

        dirtyPrice+=get_CashFlowPricingOutput(cashFlowPricingOutputIdx).get_dirtyPrice();


    } // end for cashFlowPricingOutputIdx


    return dirtyPrice;


} // end get_dirtyPrice

//------------------------------------------------------------------------------------------------------

HLR HL_InstrumentOutput::get_accrued(const date& d) const
{


    HLR accrued=0;


    HLS nbCashFlowPricingOutputs = get_nbCashFlowPricingOutputs();

    for(HLS cashFlowPricingOutputIdx=0;cashFlowPricingOutputIdx<nbCashFlowPricingOutputs;cashFlowPricingOutputIdx++)
    {

        accrued+=get_CashFlowPricingOutput(cashFlowPricingOutputIdx).get_accrued(d);


    } // end for cashFlowPricingOutputIdx


    return accrued;



} // end get_accrued





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InstrumentOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InstrumentCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_InstrumentCode::HL_InstrumentCode()
{
    classDefaultInit();

} // end HL_InstrumentCode

//------------------------------------------------------------------------------------------------------

HL_InstrumentCode::~HL_InstrumentCode()
{
} // end ~HL_InstrumentCode

//------------------------------------------------------------------------------------------------------

void HL_InstrumentCode::classDefaultInit()
{

} // end classDefaultInit
//------------------------------------------------------------------------------------------------------

HLSTRING HL_InstrumentCode::objTypeImpl() const
{
    return "HL_InstrumentCode";
} // end objTypeImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Instrument
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_Instrument::HL_Instrument()
{

    classDefaultInit();



} // end HL_Instrument

//------------------------------------------------------------------------------------------------------

HL_Instrument::~HL_Instrument()
{
} // end ~HL_Instrument


//------------------------------------------------------------------------------------------------------

void HL_Instrument::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_Instrument::descriptionImpl(std::ostream & os) const
{
    HLOBJ::HL_FinObj::descriptionImpl(os);

    HLS nbCashFlows = get_nbCashFlows();

    hl_fillDescriptionStream(nbCashFlows);

    for(HLS cashFlowIdx=0;cashFlowIdx<nbCashFlows;cashFlowIdx++)
    {
        hl_fillDescriptionStream(get_cashFlow(cashFlowIdx));

    } // end for cashFlowIdx




} // end descriptionImpl


//------------------------------------------------------------------------------------------------------

void HL_Instrument::set_HL_ObjCodePtr(const HL_ObjCodePtr & hl_ObjCodePtr)
{

    HL_FinObj::set_HL_ObjCodePtr(hl_ObjCodePtr);


    HL_DYN_SHARED_PTR_CAST_OPERATION(HL_InstrumentCode, instrumentCode_ /*outPtr*/, hl_ObjCodePtr_ /*inPtr*/);



} // end set_HL_ObjCodePtr



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowCollectionInstrument
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CashFlowCollectionInstrument::HL_CashFlowCollectionInstrument()
{

    classDefaultInit();



} // end HL_CashFlowCollectionInstrument

//------------------------------------------------------------------------------------------------------

HL_CashFlowCollectionInstrument::~HL_CashFlowCollectionInstrument()
{
} // end ~HL_CashFlowCollectionInstrument


//------------------------------------------------------------------------------------------------------

void HL_CashFlowCollectionInstrument::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_CashFlowCollectionInstrument::descriptionImpl(std::ostream & os) const
{
    os << "HL_CashFlowCollectionInstrument:\n";
    HL_Instrument::descriptionImpl(os);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

HL_InstrumentOutputPtr HL_CashFlowCollectionInstrument::get_instrumentOutput() const
{



    std::vector<HL_CashFlowPricingOutputPtr> cashFlowPricingOutputs(get_nbCashFlows());

    HLS cashFlowIdx=0;

    BOOST_FOREACH(HL_CashFlowPricingOutputPtr & cashFlowPricingOutput, cashFlowPricingOutputs)
    {

        HL_InstrumentOutputPtr cashFlowPricingOutput_cashFlowIdx=
                get_cashFlow(cashFlowIdx).get_instrumentOutput();

        HL_DYN_SHARED_PTR_CAST_OPERATION(HLINS::HL_CashFlowPricingOutput/*OutPtrType*/,
                                         cashFlowPricingOutput /*outPtr*/,
                                         cashFlowPricingOutput_cashFlowIdx/*inPtr*/)



        cashFlowIdx++;
    } // end for cashFlowPricingOutput



    HL_CashFlowCollectionInstrumentOutputPtr cashFlowCollectionInstrumentOutput(
                new HLINS::HL_CashFlowCollectionInstrumentOutput);

    cashFlowCollectionInstrumentOutput->set_cashFlowPricingOutputs(cashFlowPricingOutputs);



    return cashFlowCollectionInstrumentOutput;

} // end get_instrumentOutput

//------------------------------------------------------------------------------------------------------

void HL_CashFlowCollectionInstrument::purgeAllComputations() const
{
    BOOST_FOREACH(const HL_CashFlowPtr & cashFlow, cashFlows_)
    {
        cashFlow->purgeAllComputations();

    } // end for cashFlow


} // end purgeAllComputations

//------------------------------------------------------------------------------------------------------


void HL_CashFlowCollectionInstrument::set_cashFlows(const std::vector<HL_CashFlowPtr> & cashFlows)
{

    cashFlows_=cashFlows;

    std::sort(cashFlows_.begin(), cashFlows_.end());

    HL_PNN_RANGE(cashFlows_);

} // end set_cashFlows


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowCollectionInstrumentOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CashFlowCollectionInstrumentOutput::HL_CashFlowCollectionInstrumentOutput()
{
    classDefaultInit();

} // end HL_CashFlowCollectionInstrumentOutput

//------------------------------------------------------------------------------------------------------

HL_CashFlowCollectionInstrumentOutput::~HL_CashFlowCollectionInstrumentOutput()
{
} // end ~HL_CashFlowCollectionInstrumentOutput

//------------------------------------------------------------------------------------------------------

void HL_CashFlowCollectionInstrumentOutput::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_CashFlowCollectionInstrumentOutput::descriptionImpl(std::ostream & os) const
{


    os << "HL_CashFlowCollectionInstrumentOutput:\n";

    HL_InstrumentOutput::descriptionImpl(os);




} // end descriptionImpl

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowCollectionInstrumentOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_EnginedInstrument
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_EnginedInstrument::HL_EnginedInstrument()
{

    classDefaultInit();



} // end HL_EnginedInstrument

//------------------------------------------------------------------------------------------------------

HL_EnginedInstrument::~HL_EnginedInstrument()
{
} // end ~HL_EnginedInstrument


//------------------------------------------------------------------------------------------------------

void HL_EnginedInstrument::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_EnginedInstrument::descriptionImpl(std::ostream & os) const
{
    os << "HL_EnginedInstrument: \n";

    HL_Instrument::descriptionImpl(os);





} // end descriptionImpl



//------------------------------------------------------------------------------------------------------

HL_InstrumentOutputPtr HL_EnginedInstrument::get_instrumentOutput() const
{

    return get_pricingEngineOutput()->get_instrumentOutput();

} // end get_instrumentOutput

//------------------------------------------------------------------------------------------------------


HL_PricingEngineOutputPtr HL_EnginedInstrument::get_pricingEngineOutput() const
{

    HL_PNN(pricingEngine_);

    const HL_MachineOutputPtr & machineOutput  = pricingEngine_->doJob();

    HL_DYN_SHARED_PTR_CAST(HLPE::HL_PricingEngineOutput/*OutPtrType*/,
                                     pricingEngineOutput/*outPtr*/,
                                     machineOutput/*inPtr*/);

    return pricingEngineOutput;

} // end get_pricingEngineOutput


//------------------------------------------------------------------------------------------------------

void HL_EnginedInstrument::purgeAllComputations() const
{

    if(pricingEngine_)
        pricingEngine_->resetOutputs();

} // end purgeAllComputations




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Utility Methods
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// mergeInstruments
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_InstrumentPtr mergeInstruments(const std::vector<HL_InstrumentPtr> & instruments)
{
    std::vector<HL_CashFlowPtr> mergedCashFlows;

    BOOST_FOREACH(const HL_InstrumentPtr & ins, instruments)
    {

        HL_PNN(ins);

        HL_DYN_SHARED_PTR_CAST(HL_CashFlowCollectionInstrument, cashFlowCollectionIns, ins);

        const std::vector<HL_CashFlowPtr> & cfs = cashFlowCollectionIns->get_cashFlows();

        mergedCashFlows.insert(mergedCashFlows.end(), cfs.begin(), cfs.end());

    } // end for ins

    HL_CashFlowCollectionInstrumentPtr mergedIns(new HL_CashFlowCollectionInstrument);

    mergedIns->set_cashFlows(mergedCashFlows);

    return mergedIns;

} // end mergeInstruments



} // end namespace HL_Instruments
} //end namespace HorizonLib
