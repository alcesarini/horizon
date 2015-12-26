/**
FILE NAME= hl_vanillaCashFlowPricingEngine.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140920
*/

#include <hl/pricingEngines/hl_vanillaCashFlowPricingEngine.h>
#include <hl/instruments/hl_vanillaCashFlow.h>
#include <hl/underlyings/interestRates/hl_iborIndex.h>
#include <hl/math/pricingFunctions/hl_vanillaPricingFunctions.h>

// same type as HL_CashFlowPricingEngineInput
//HL_SERIALIZATION_CLASS_EXPORT_GUID(HLPE::HL_FixedCashFlowPricingEngineInput);
// same type as HL_CashFlowPricingEngineOuput
//HL_SERIALIZATION_CLASS_EXPORT_GUID(HLPE::HL_FixedCashFlowPricingEngineOutput);
// same type as HL_CashFlowPricingEngineInputKey
//HL_SERIALIZATION_CLASS_EXPORT_GUID(HLPE::HL_FixedCashFlowPricingEngineInputKey);

// same type as HL_CashFlowPricingEngineInput
//HL_SERIALIZATION_CLASS_EXPORT_GUID(HLPE::HL_VariableCashFlowPricingEngineInput);
// same type as HL_CashFlowPricingEngineOuput
//HL_SERIALIZATION_CLASS_EXPORT_GUID(HLPE::HL_VariableCashFlowPricingEngineOutput);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLPE::HL_VariableCashFlowPricingEngineInputKey);



namespace HorizonLib
{
namespace HL_PricingEngines
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowPricingEngineInput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowPricingEngineInput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowPricingEngineInputKey
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowPricingEngineInputKey:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowPricingEngineOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowPricingEngineOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowPricingEngine
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_FixedCashFlowPricingEngine::HL_FixedCashFlowPricingEngine()
{

    classDefaultInit();



} // end HL_FixedCashFlowPricingEngine

//------------------------------------------------------------------------------------------------------

HL_FixedCashFlowPricingEngine::~HL_FixedCashFlowPricingEngine()
{
} // end ~HL_FixedCashFlowPricingEngine


//------------------------------------------------------------------------------------------------------

void HL_FixedCashFlowPricingEngine::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_FixedCashFlowPricingEngine::descriptionImpl(std::ostream & os) const
{
    HL_CashFlowPricingEngine::descriptionImpl(os);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_FixedCashFlowPricingEngine::buildInputKey(const HL_MachineInputPtr & input,
                                                  HL_MachineInputKeyPtr & machineInputKey) const
{

    /*
     * Being this a concrete class to be derived no more, we expect
     * to be it to instantiate machineInputKey (of the mosty derived type).
    */
    HL_SR(!machineInputKey);

    fixedCashFlowPricingEngineDisposableData_.inputKey.reset(new HL_FixedCashFlowPricingEngineInputKey);

    machineInputKey=fixedCashFlowPricingEngineDisposableData_.inputKey;

    HL_CashFlowPricingEngine::buildInputKey(input, machineInputKey);

    HL_DYN_SHARED_PTR_CAST_OPERATION(HL_FixedCashFlowPricingEngineInput/*OutPtrType*/,
                                     fixedCashFlowPricingEngineDisposableData_.input/*outPtr*/,
                                     input/*inPtr*/);



    HL_DYN_C_PTR_CAST_OPERATION(const HLINS::HL_FixedCashFlow */*OutPtrType*/,
                                     fixedCashFlowPricingEngineDisposableData_.fixedCashFlow/*outPtr*/,
                                     cashFlowPricingEngineDisposableData_.cashFlow/*inPtr*/);

} // end buildInputKey

//------------------------------------------------------------------------------------------------------

void HL_FixedCashFlowPricingEngine::instantiateCashFlowPricingOutput() const
{
    fixedCashFlowPricingEngineDisposableData_.cashFlowPricingOutput.reset(new HLINS::HL_CashFlowPricingOutput);

    cashFlowPricingEngineDisposableData_.cashFlowPricingOutput=fixedCashFlowPricingEngineDisposableData_.cashFlowPricingOutput;

} // end instantiateCashFlowPricingOutput

//------------------------------------------------------------------------------------------------------

void HL_FixedCashFlowPricingEngine::fillCashFlowPricingOutput() const
{

    HL_CashFlowPricingEngine::fillCashFlowPricingOutput();


} // end fillCashFlowPricingOutput

//------------------------------------------------------------------------------------------------------

bool HL_FixedCashFlowPricingEngine::isPayoffDeterministic() const
{

    return true;
} // end isPayoffDeterministic
//------------------------------------------------------------------------------------------------------

HLR HL_FixedCashFlowPricingEngine::computeCashFlowPayoff() const
{
    return fixedCashFlowPricingEngineDisposableData_.fixedCashFlow->get_fixedRate();

} // end computeCashFlowPayoff

//------------------------------------------------------------------------------------------------------

void HL_FixedCashFlowPricingEngine::instantiateCashFlowPricingEngineOutput() const
{

    fixedCashFlowPricingEngineDisposableData_.cashFlowPricingEngineOutput.reset(
                new HLPE::HL_FixedCashFlowPricingEngineOutput);

    cashFlowPricingEngineDisposableData_.cashFlowPricingEngineOutput =
            fixedCashFlowPricingEngineDisposableData_.cashFlowPricingEngineOutput;

} // end instantiateCashFlowPricingEngineOutput


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingEngineInput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingEngineInput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingEngineInputKey
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_VariableCashFlowPricingEngineInputKey::HL_VariableCashFlowPricingEngineInputKey()
{
    classDefaultInit();

} // end HL_VariableCashFlowPricingEngineInputKey

//------------------------------------------------------------------------------------------------------

HL_VariableCashFlowPricingEngineInputKey::~HL_VariableCashFlowPricingEngineInputKey()
{
} // end ~HL_VariableCashFlowPricingEngineInputKey

//------------------------------------------------------------------------------------------------------

void HL_VariableCashFlowPricingEngineInputKey::classDefaultInit()
{

} // end classDefaultInit



//------------------------------------------------------------------------------------------------------

void HL_VariableCashFlowPricingEngineInputKey::descriptionImpl(std::ostream & os) const
{


    os << "HL_VariableCashFlowPricingEngineInputKey:\n";

    HL_CashFlowPricingEngineInputKey::descriptionImpl(os);
    hl_fillDescriptionStream(fwds_);
    hl_fillDescriptionStream(vols_);
    hl_fillDescriptionStream(underlyingQuantities_);



} // end descriptionImpl


//------------------------------------------------------------------------------------------------------

HL_Order HL_VariableCashFlowPricingEngineInputKey::getOrder(const HL_MachineInputKey & machineInputKey) const
{

    HL_Order baseClassOrder = HL_CashFlowPricingEngineInputKey::getOrder(machineInputKey);

    if(baseClassOrder!=HL_Order_1_Eq_2)
        return baseClassOrder;


    HL_DYN_C_PTR_CAST(const HL_VariableCashFlowPricingEngineInputKey *,
                      externalVariableCashFlowPricingEngineInputKey,
                      &machineInputKey);


    HL_PLAIN_ORDER_COMPARE(fwds_, externalVariableCashFlowPricingEngineInputKey->fwds_);

    HL_PLAIN_ORDER_COMPARE(vols_, externalVariableCashFlowPricingEngineInputKey->vols_);

    HL_PLAIN_ORDER_COMPARE(underlyingQuantities_, externalVariableCashFlowPricingEngineInputKey->underlyingQuantities_);

    return HL_Order_1_Eq_2;

} // end getOrder








//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingEngineOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingEngineOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingEngine
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_VariableCashFlowPricingEngine::HL_VariableCashFlowPricingEngine()
{

    classDefaultInit();



} // end HL_VariableCashFlowPricingEngine

//------------------------------------------------------------------------------------------------------

HL_VariableCashFlowPricingEngine::~HL_VariableCashFlowPricingEngine()
{
} // end ~HL_VariableCashFlowPricingEngine


//------------------------------------------------------------------------------------------------------

void HL_VariableCashFlowPricingEngine::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_VariableCashFlowPricingEngine::descriptionImpl(std::ostream & os) const
{
    HL_CashFlowPricingEngine::descriptionImpl(os);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_VariableCashFlowPricingEngine::buildInputKey(const HL_MachineInputPtr & input,
                                                     HL_MachineInputKeyPtr & machineInputKey) const
{


    HL_CashFlowPricingEngine::buildInputKey(input, machineInputKey);




    HL_DYN_SHARED_PTR_CAST_OPERATION(HL_VariableCashFlowPricingEngineInput/*OutPtrType*/,
                                     variableCashFlowPricingEngineDisposableData_.input/*outPtr*/,
                                     input/*inPtr*/);

    HL_DYN_SHARED_PTR_CAST_OPERATION(HL_VariableCashFlowPricingEngineInputKey/*OutPtrType*/,
                                     variableCashFlowPricingEngineDisposableData_.inputKey/*outPtr*/,
                                     machineInputKey/*inPtr*/);

    HL_DYN_C_PTR_CAST_OPERATION(const HLINS::HL_VariableCashFlow */*OutPtrType*/,
                                     variableCashFlowPricingEngineDisposableData_.variableCashFlow/*outPtr*/,
                                     cashFlowPricingEngineDisposableData_.cashFlow/*inPtr*/);


    variableCashFlowPricingEngineDisposableData_.variableCashFlow->checkCashFlow();


} // end buildInputKey




//------------------------------------------------------------------------------------------------------

void HL_VariableCashFlowPricingEngine::instantiateCashFlowPricingOutput() const
{

    HL_UNEXPECTED_FUNCTION_CALL;

} // end instantiateCashFlowPricingOutput

//------------------------------------------------------------------------------------------------------

void HL_VariableCashFlowPricingEngine::fillCashFlowPricingOutput() const
{

    HL_CashFlowPricingEngine::fillCashFlowPricingOutput();


    variableCashFlowPricingEngineDisposableData_.variableCashFlowPricingOutput->set_nominalFixings(
                variableCashFlowPricingEngineDisposableData_.nominalFixings);



} // end fillCashFlowPricingOutput

//------------------------------------------------------------------------------------------------------

bool HL_VariableCashFlowPricingEngine::isPayoffDeterministic() const
{
    HL_UNEXPECTED_FUNCTION_CALL;

} // end isPayoffDeterministic
//------------------------------------------------------------------------------------------------------

HLR HL_VariableCashFlowPricingEngine::computeCashFlowPayoff() const
{
    HL_UNEXPECTED_FUNCTION_CALL;

} // end computeCashFlowPayoff

//------------------------------------------------------------------------------------------------------

void HL_VariableCashFlowPricingEngine::instantiateCashFlowPricingEngineOutput() const
{

    HL_UNEXPECTED_FUNCTION_CALL;


} // end instantiateCashFlowPricingEngineOutput

//------------------------------------------------------------------------------------------------------

void HL_VariableCashFlowPricingEngine::computeNominalFixings(bool extractAtmVol, HLR strikeToExtractVol) const
{

    variableCashFlowPricingEngineDisposableData_.nominalFixingTime=get_nominalFixingTime();

    HL_BasketPtr basket = variableCashFlowPricingEngineDisposableData_.variableCashFlow->get_basketPtr();

    HL_FwdMeasurePtr riskFreeDiscountingFwdMeasure = getRiskFreeDiscountingFwdMeasure();

    variableCashFlowPricingEngineDisposableData_.nominalFixings.resize(basket->nbComponents());

    const ptime & fixTime = variableCashFlowPricingEngineDisposableData_.nominalFixingTime;


    const ptime & refTime = pricingEngineDisposableData_.input->get_mktDataCollector()
            ->get_refTime();


    const HL_BasketCompositionPtr & basketComposition=
            variableCashFlowPricingEngineDisposableData_.variableCashFlow->get_basketComposition();

    HLINS::HL_BasketCompositionType basketCompositionType =
            basketComposition->get_basketCompositionType();


    const ptime & basketIssueTime = basketComposition->get_issueTime();

    VEC fwds(basket->nbComponents());
    VEC vols(basket->nbComponents());


    VEC underlyingQuantities;


    switch(basketCompositionType)
    {
    case HLINS::HL_BasketCompositionType_FwdStart:
    {
        HL_DYN_SHARED_PTR_CAST(HLINS::HL_FwdStartBasketComposition/*OutPtrType*/,
                               fwdStartBasketComposition/*outPtr*/,
                               basketComposition/*inPtr*/);

        underlyingQuantities = fwdStartBasketComposition->get_issueTimeWeights();
        break;
    }
    case HLINS::HL_BasketCompositionType_Quant:
    {
        HL_DYN_SHARED_PTR_CAST(HLINS::HL_QuantBasketComposition/*OutPtrType*/,
                               quantBasketComposition/*outPtr*/,
                               basketComposition/*inPtr*/);

        underlyingQuantities = quantBasketComposition->get_issueTimeQuantities();
        break;
    }
    default:
        HL_FAIL("invalid basketCompositionType " << getEnumString(basketCompositionType));

    } // end switch(basketCompositionType)


    HLS i=0;
    BOOST_FOREACH(HL_FixingStatePtr & fixState, variableCashFlowPricingEngineDisposableData_.nominalFixings)
    {


        const HL_UnderlyingCodePtr & underlyingCode = basket->get_underlyingCode(i);

        const HL_UnderlyingPtr & underlying = pricingEngineDisposableData_.input->get_mktDataCollector()
                ->get_mktData<HL_UnderlyingPtr>(underlyingCode);

        HLR & fixValue = fwds[i];


        fixValue = underlying->expectation(fixTime,
                                           riskFreeDiscountingFwdMeasure,
                                           basket->get_underlyingHistoryTag(i)
                                           )->get_value();

        if(basketCompositionType==HLINS::HL_BasketCompositionType_FwdStart)
        {

            HLR startFix = underlying->expectation(basketIssueTime,
                                                   riskFreeDiscountingFwdMeasure,
                                                   basket->get_underlyingHistoryTag(i)
                                                   )->get_value();

            HL_SR(startFix!=0.);

            underlyingQuantities[i]/=startFix;
        }

        HLR k;

        if(extractAtmVol)
        {

            k=underlying->quotingMeasureExpectation(fixTime)->get_value();
        }
        else
        {
            k=strikeToExtractVol;
        }



        HL_VolStatePtr volState =
                underlying->get_impliedVolSurface()->vol(
                    fixTime /*t*/,
                    k,
                    fixTime/*fwdMaturityTime*/);


        fixState.reset(new HLINS::HL_FixingState);

        fixState->set_fixingTime(fixTime);

        fixState->set_fwdValue(fixValue);

        fixState->set_fixingDescription(underlying->sCode());

        fixState->set_volState(volState);


        HLR & vol_i = vols[i];

        vol_i = volState->get_vol();

        ++i;
    } // end for x


    variableCashFlowPricingEngineDisposableData_.inputKey->set_fwds(fwds);

    variableCashFlowPricingEngineDisposableData_.inputKey->set_vols(vols);

    variableCashFlowPricingEngineDisposableData_.inputKey->set_underlyingQuantities(underlyingQuantities);


} // end computeNominalFixings



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingEngineInput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingEngineInput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingEngineInputKey
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingEngineInputKey:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingEngineOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingEngineOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingEngine
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_VanillaCashFlowPricingEngine::HL_VanillaCashFlowPricingEngine()
{

    classDefaultInit();



} // end HL_VanillaCashFlowPricingEngine

//------------------------------------------------------------------------------------------------------

HL_VanillaCashFlowPricingEngine::~HL_VanillaCashFlowPricingEngine()
{
} // end ~HL_VanillaCashFlowPricingEngine


//------------------------------------------------------------------------------------------------------

void HL_VanillaCashFlowPricingEngine::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_VanillaCashFlowPricingEngine::descriptionImpl(std::ostream & os) const
{
    HL_VariableCashFlowPricingEngine::descriptionImpl(os);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_VanillaCashFlowPricingEngine::buildInputKey(const HL_MachineInputPtr & input,
                                                    HL_MachineInputKeyPtr & machineInputKey) const
{


    HL_PNN(machineInputKey);


    HL_VariableCashFlowPricingEngine::buildInputKey(input, machineInputKey);


    HL_DYN_SHARED_PTR_CAST_OPERATION(HL_VanillaCashFlowPricingEngineInput/*OutPtrType*/,
                                     vanillaCashFlowPricingEngineDisposableData_.input/*outPtr*/,
                                     input/*inPtr*/);


    HL_DYN_C_PTR_CAST_OPERATION(const HLINS::HL_VanillaCashFlow */*OutPtrType*/,
                                     vanillaCashFlowPricingEngineDisposableData_.vanillaCashFlow/*outPtr*/,
                                     cashFlowPricingEngineDisposableData_.cashFlow/*inPtr*/);







} // end buildInputKey




//------------------------------------------------------------------------------------------------------

void HL_VanillaCashFlowPricingEngine::instantiateCashFlowPricingOutput() const
{


    vanillaCashFlowPricingEngineDisposableData_.vanillaCashFlowPricingOutput.reset(new HLINS::HL_VanillaCashFlowPricingOutput);

    variableCashFlowPricingEngineDisposableData_.variableCashFlowPricingOutput = vanillaCashFlowPricingEngineDisposableData_.vanillaCashFlowPricingOutput;

    cashFlowPricingEngineDisposableData_.cashFlowPricingOutput=vanillaCashFlowPricingEngineDisposableData_.vanillaCashFlowPricingOutput;


} // end instantiateCashFlowPricingOutput

//------------------------------------------------------------------------------------------------------

void HL_VanillaCashFlowPricingEngine::fillCashFlowPricingOutput() const
{

    HL_VariableCashFlowPricingEngine::fillCashFlowPricingOutput();



} // end fillCashFlowPricingOutput

//------------------------------------------------------------------------------------------------------

bool HL_VanillaCashFlowPricingEngine::isPayoffDeterministic() const
{

    const ptime & refTime = get_refTime();

    const ptime & nominalFixingTime =
            variableCashFlowPricingEngineDisposableData_.nominalFixingTime;

    HL_SR(nominalFixingTime!=ptime());

    bool isDeterm = (refTime>=nominalFixingTime);

    return isDeterm;


} // end isPayoffDeterministic
//------------------------------------------------------------------------------------------------------

HLR HL_VanillaCashFlowPricingEngine::computeCashFlowPayoff() const
{

    HL_UNEXPECTED_FUNCTION_CALL;

} // end computeCashFlowPayoff

//------------------------------------------------------------------------------------------------------

void HL_VanillaCashFlowPricingEngine::instantiateCashFlowPricingEngineOutput() const
{


    HL_UNEXPECTED_FUNCTION_CALL;

} // end instantiateCashFlowPricingEngineOutput



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_AnalyticVanillaCashFlowPricingEngine
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_AnalyticVanillaCashFlowPricingEngine::HL_AnalyticVanillaCashFlowPricingEngine()
{

    classDefaultInit();



} // end HL_AnalyticVanillaCashFlowPricingEngine

//------------------------------------------------------------------------------------------------------

HL_AnalyticVanillaCashFlowPricingEngine::~HL_AnalyticVanillaCashFlowPricingEngine()
{
} // end ~HL_AnalyticVanillaCashFlowPricingEngine


//------------------------------------------------------------------------------------------------------

void HL_AnalyticVanillaCashFlowPricingEngine::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_AnalyticVanillaCashFlowPricingEngine::descriptionImpl(std::ostream & os) const
{
    HL_VanillaCashFlowPricingEngine::descriptionImpl(os);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_AnalyticVanillaCashFlowPricingEngine::buildInputKey(const HL_MachineInputPtr & input,
                                                            HL_MachineInputKeyPtr & machineInputKey) const
{

    /*
     * Being this a concrete class to be derived no more, we expect
     * to be it to instantiate machineInputKey (of the mosty derived type).
    */
    HL_SR(!machineInputKey);

    analyticVanillaCashFlowPricingEngineDisposableData_.inputKey.reset(new HL_AnalyticVanillaCashFlowPricingEngineInputKey);

    machineInputKey=vanillaCashFlowPricingEngineDisposableData_.inputKey;

    HL_VanillaCashFlowPricingEngine::buildInputKey(input, machineInputKey);

    HL_DYN_SHARED_PTR_CAST_OPERATION(HL_AnalyticVanillaCashFlowPricingEngineInput/*OutPtrType*/,
                                     analyticVanillaCashFlowPricingEngineDisposableData_.input/*outPtr*/,
                                     input/*inPtr*/);

    /*
    Notice that we can directly use vanillaCashFlowPricingEngineDisposableData_.vanillaCashFlow->get_strike()
    as strike to extract vol since we have checked that

    get_basketCompositionType()==HLINS::HL_BasketCompositionType_Quant

    This is the reason why this method is called in this very derived class and not, for ex., in
    its base class (it woule be meaningless to extract a vol using a relative strike...).

    */
    HLR vanillaStrike = vanillaCashFlowPricingEngineDisposableData_.vanillaCashFlow->get_strike();

    computeNominalFixings(false/*extractAtmVol*/,
                          vanillaStrike/*strikeToExtractVol*/);



} // end buildInputKey




//------------------------------------------------------------------------------------------------------

HLR HL_AnalyticVanillaCashFlowPricingEngine::computeCashFlowPayoff() const
{

    vanillaCashFlowPricingEngineDisposableData_.vanillaCashFlow
            ->get_basketComposition()->checkBasketComposition();

    HL_SRE(vanillaCashFlowPricingEngineDisposableData_.vanillaCashFlow
           ->get_basketComposition()->get_basketCompositionType()==HLINS::HL_BasketCompositionType_Quant,
           "fwd start vanillas not supported by this pricing engine");

    HL_SRE(vanillaCashFlowPricingEngineDisposableData_.vanillaCashFlow
           ->get_basketComposition()->get_nbComponents()==1,
           "multi asset vanillas not supported by this pricing engine");


    HL_SR(variableCashFlowPricingEngineDisposableData_.nominalFixings.size()==1);


    const HL_FixingStatePtr & underlyingFixingState =
            variableCashFlowPricingEngineDisposableData_.nominalFixings[0];


    HLR underlyingQuantity =
            variableCashFlowPricingEngineDisposableData_.inputKey->get_underlyingQuantities()[0];

    HLR underlyingFwd = underlyingFixingState->get_fwdValue();


    HLR underlyingStdDev = underlyingFixingState->get_volState()->get_stdDev();


    HLR vanillaStrike = vanillaCashFlowPricingEngineDisposableData_.vanillaCashFlow->get_strike();


    HLVOL::HL_ImpliedVolModelTypeType underlyingImpliedVolModelTypeType =
            underlyingFixingState->get_volState()->get_impliedVolModelTypeType();


    HL_VanillaType vanillaType = vanillaCashFlowPricingEngineDisposableData_.vanillaCashFlow->get_vanillaType();

    HLR payoff = HLMA::hl_undiscGenericBS(underlyingFwd*underlyingQuantity,
                                          vanillaStrike,
                                          underlyingStdDev,
                                          underlyingImpliedVolModelTypeType,
                                          vanillaType);


    return payoff;

} // end computeCashFlowPayoff

//------------------------------------------------------------------------------------------------------

void HL_AnalyticVanillaCashFlowPricingEngine::instantiateCashFlowPricingEngineOutput() const
{

    analyticVanillaCashFlowPricingEngineDisposableData_.analyticVanillaCashFlowPricingEngineOutput.reset(
                new HLPE::HL_AnalyticVanillaCashFlowPricingEngineOutput);


    vanillaCashFlowPricingEngineDisposableData_.vanillaCashFlowPricingEngineOutput=
            analyticVanillaCashFlowPricingEngineDisposableData_.analyticVanillaCashFlowPricingEngineOutput;

    variableCashFlowPricingEngineDisposableData_.variableCashFlowPricingEngineOutput =
            vanillaCashFlowPricingEngineDisposableData_.vanillaCashFlowPricingEngineOutput;

    cashFlowPricingEngineDisposableData_.cashFlowPricingEngineOutput =
            vanillaCashFlowPricingEngineDisposableData_.vanillaCashFlowPricingEngineOutput;

} // end instantiateCashFlowPricingEngineOutput

//------------------------------------------------------------------------------------------------------









//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowPricingEngineInput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowPricingEngineInput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowPricingEngineInputKey
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowPricingEngineInputKey:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowPricingEngineOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowPricingEngineOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowPricingEngine
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_UnderlyingDeliveryCashFlowPricingEngine::HL_UnderlyingDeliveryCashFlowPricingEngine()
{

    classDefaultInit();



} // end HL_UnderlyingDeliveryCashFlowPricingEngine

//------------------------------------------------------------------------------------------------------

HL_UnderlyingDeliveryCashFlowPricingEngine::~HL_UnderlyingDeliveryCashFlowPricingEngine()
{
} // end ~HL_UnderlyingDeliveryCashFlowPricingEngine


//------------------------------------------------------------------------------------------------------

void HL_UnderlyingDeliveryCashFlowPricingEngine::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_UnderlyingDeliveryCashFlowPricingEngine::descriptionImpl(std::ostream & os) const
{
    HL_VariableCashFlowPricingEngine::descriptionImpl(os);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_UnderlyingDeliveryCashFlowPricingEngine::buildInputKey(const HL_MachineInputPtr & input,
                                                               HL_MachineInputKeyPtr & machineInputKey) const
{

    /*
     * Being this a concrete class to be derived no more, we expect
     * to be it to instantiate machineInputKey (of the mosty derived type).
    */
    HL_SR(!machineInputKey);



    underlyingDeliveryCashFlowPricingEngineDisposableData_.inputKey.reset(
                new HL_UnderlyingDeliveryCashFlowPricingEngineInputKey);

    machineInputKey=underlyingDeliveryCashFlowPricingEngineDisposableData_.inputKey;



    HL_VariableCashFlowPricingEngine::buildInputKey(input, machineInputKey);


    HL_DYN_SHARED_PTR_CAST_OPERATION(HL_UnderlyingDeliveryCashFlowPricingEngineInput/*OutPtrType*/,
                                     underlyingDeliveryCashFlowPricingEngineDisposableData_.input/*outPtr*/,
                                     input/*inPtr*/);


    HL_DYN_C_PTR_CAST_OPERATION(const HLINS::HL_UnderlyingDeliveryCashFlow */*OutPtrType*/,
                                     underlyingDeliveryCashFlowPricingEngineDisposableData_.underlyingDeliveryCashFlow/*outPtr*/,
                                     cashFlowPricingEngineDisposableData_.cashFlow/*inPtr*/);


    computeNominalFixings(true/*extractAtmVol*/);



} // end buildInputKey






//------------------------------------------------------------------------------------------------------

void HL_UnderlyingDeliveryCashFlowPricingEngine::instantiateCashFlowPricingOutput() const
{


    underlyingDeliveryCashFlowPricingEngineDisposableData_.underlyingDeliveryCashFlowPricingOutput.reset(new HLINS::HL_UnderlyingDeliveryCashFlowPricingOutput);

    variableCashFlowPricingEngineDisposableData_.variableCashFlowPricingOutput = underlyingDeliveryCashFlowPricingEngineDisposableData_.underlyingDeliveryCashFlowPricingOutput;

    cashFlowPricingEngineDisposableData_.cashFlowPricingOutput=underlyingDeliveryCashFlowPricingEngineDisposableData_.underlyingDeliveryCashFlowPricingOutput;


} // end instantiateCashFlowPricingOutput

//------------------------------------------------------------------------------------------------------

void HL_UnderlyingDeliveryCashFlowPricingEngine::fillCashFlowPricingOutput() const
{

    HL_VariableCashFlowPricingEngine::fillCashFlowPricingOutput();



} // end fillCashFlowPricingOutput

//------------------------------------------------------------------------------------------------------

bool HL_UnderlyingDeliveryCashFlowPricingEngine::isPayoffDeterministic() const
{

    const ptime & refTime = get_refTime();

    const ptime & nominalFixingTime =
            variableCashFlowPricingEngineDisposableData_.nominalFixingTime;

    HL_SR(nominalFixingTime!=ptime());

    bool isDeterm = (refTime>=nominalFixingTime);

    return isDeterm;


} // end isPayoffDeterministic
//------------------------------------------------------------------------------------------------------

HLR HL_UnderlyingDeliveryCashFlowPricingEngine::computeCashFlowPayoff() const
{


    const HL_BasketCompositionPtr& basketComposition=
            underlyingDeliveryCashFlowPricingEngineDisposableData_.underlyingDeliveryCashFlow
            ->get_basketComposition();



    basketComposition->checkBasketComposition();


    const std::vector<HL_FixingStatePtr> & nominalFixings =
            variableCashFlowPricingEngineDisposableData_.nominalFixings;



    HL_SR(nominalFixings.size()==basketComposition->get_nbComponents());

    VEC underlyingFixings(nominalFixings.size());

    HLS i=0;
    BOOST_FOREACH(const HL_FixingStatePtr& fixingState, nominalFixings)
    {
        HL_PNN(fixingState);

        underlyingFixings[i]=fixingState->get_fwdValue();

        ++i;
    } // end for fixingState

    const VEC & underlyingQuantities = variableCashFlowPricingEngineDisposableData_.inputKey->get_underlyingQuantities();



    HLR payoff=HLINS::computeBasketPerformance(
                basketComposition->get_basketRuleType()/*basketRuleType*/,
                underlyingFixings /* fixings*/,
                underlyingQuantities/*quantities*/
                );

    return payoff;

} // end computeCashFlowPayoff

//------------------------------------------------------------------------------------------------------

void HL_UnderlyingDeliveryCashFlowPricingEngine::instantiateCashFlowPricingEngineOutput() const
{


    underlyingDeliveryCashFlowPricingEngineDisposableData_.underlyingDeliveryCashFlowPricingEngineOutput.reset(
                new HLPE::HL_UnderlyingDeliveryCashFlowPricingEngineOutput);

    variableCashFlowPricingEngineDisposableData_.variableCashFlowPricingEngineOutput =
            underlyingDeliveryCashFlowPricingEngineDisposableData_.underlyingDeliveryCashFlowPricingEngineOutput;

    cashFlowPricingEngineDisposableData_.cashFlowPricingEngineOutput =
            underlyingDeliveryCashFlowPricingEngineDisposableData_.underlyingDeliveryCashFlowPricingEngineOutput;


} // end instantiateCashFlowPricingEngineOutput




} // end namespace HL_PricingEngines
} //end namespace HorizonLib
