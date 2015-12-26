/**
FILE NAME= hl_yieldTsBootstrap.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20141207
*/
#include <hl/mktData/yieldTermStructureBootstrap/hl_yieldTsBootstrap.h>
#include <hl/instruments/anagraphics/hl_mktInsFactory.h>
#include <hl/underlyings/interestRates/hl_iborIndex.h>
#include <hl/mktData/hl_mktDataCollector_HL_TEST.h>
#include <hl/instruments/anagraphics/hl_mktInsAnagraphics.h>

namespace HorizonLib
{
namespace HL_MarketData
{




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IRCurveData
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_IRCurveData::HL_IRCurveData()
{

    classDefaultInit();


    /**
    ora che hai un'anagrafica tra le variabili di questa classe dovresti,
    costruisci tutti gli strumenti tramite le classi HL_SwapInsFactory
    (controllando che siano delle anagrafiche di swaps o comunque di altri
    oggetti gestibili (tipo futures, che però ad oggi non esistono ancora).

    A questo punto, raccatta tutte le date che sono rilevanti per il pricing di
    tale insieme di instruments appena costruiti dall'insieme di anagrafiche.

    Con tali date costruisci una curva avente solo tali date come nodi e
    vai a prezzare tutti gli strumenti a mò di bootstrap, fino a completa
    determinazione della curva.

    Nel fare questo, dovresti prima controllare che gli strumenti forniti abbiano
    un ordine crescente di date.

    Da notare che le date di cui sopra, saranno quelle di forwarding per
    gli strumenti da bootstrappare e non quelle per scontare i flussi a meno che
    non sia vero che la discounting curve data coincida con il codice
    della curva da bootsrappare: irCurveCode_==riskFreeDiscounting_


    ORA CHE HAI COSTRUITO GLI STRUMENTI, PREZZALI E USANDO IL MKT DATA DESCRIPTOR
    CERCA DI CAPIRE QUALI CURVE (TS CODES) E QUALI NODI USANO PER ESSERE PREZZATI.

    CON QUESTE INFO, POTRAI RIUSCIRE A COSTRUIRE LA GIUSTA CURVA DA BOOTSTRAPPARE.



    devi ora mettere una curva fake nel mkt data collector, finalizzata solo
    a prezzare gli instrumets una prima volta.
    qeusto serve a raccogliere, tramite il mkt data tracker, l'insieme dei
    nodi di date da cui gli strumenti dipendono.
    dopo questo puoi costruire una curva interpolata lineare con tutte le date
    di cui ho appena parlato.
    fatto questo si procede col bootstrap e poi, finito tutto, si wrappa
    codesta curva per nodi dentro una natural monotonic cubic spline (ad esempio)
    e si ha una roba totalmente coerente col bootstrap, ma con migliori
    proprietà di regolarità funzionale!!!!!!!!!
    */



} // end HL_IRCurveData

//------------------------------------------------------------------------------------------------------

HL_IRCurveData::~HL_IRCurveData()
{} // end ~HL_IRCurveData


//------------------------------------------------------------------------------------------------------

void HL_IRCurveData::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_IRCurveData::descriptionImpl(std::ostream & os) const
{
    os << "HL_IRCurveData:\n";

    Descriptable::descriptionImpl(os);

    hl_fillDescriptionStream(irCurveCode_);
    hl_fillDescriptionStream(riskFreeDiscounting_);
    hl_fillDescriptionStream(mktQuotes_);
    HL_DESCRIBE_ENUM(os, discountFactorInterpVariableType_);
    HL_DESCRIBE_ENUM(os, discountFactorInterpType_);
    hl_fillDescriptionStream(pricingEngineChoices_);



} // end descriptionImpl

//------------------------------------------------------------------------------------------------------


void HL_IRCurveData::checkIRCurveData() const
{

    HL_PNN(irCurveCode_);

    HL_PNN(riskFreeDiscounting_);

    BOOST_FOREACH(const HL_MktQuotePtr & mktQuote, mktQuotes_)
    {
        HL_PNN(mktQuote);


        mktQuote->checkMktQuote();

    } // end for mktQuote


    HL_ENUM_CHECK(HLTS::HL_DiscountFactorInterpVariableType/*EnumTypeName*/,
                  discountFactorInterpVariableType_/*enumValue*/);

    HL_ENUM_CHECK(HLINTP::HL_InterpolatorType/*EnumTypeName*/,
                  discountFactorInterpType_/*enumValue*/);


    HL_PNN(pricingEngineChoices_);

} // end checkIRCurveData


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IRCurveData: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IRCurveBootstrap
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_IRCurveBootstrap::HL_IRCurveBootstrap()
{

    classDefaultInit();



} // end HL_IRCurveBootstrap

//------------------------------------------------------------------------------------------------------

HL_IRCurveBootstrap::~HL_IRCurveBootstrap()
{} // end ~HL_IRCurveBootstrap


//------------------------------------------------------------------------------------------------------

void HL_IRCurveBootstrap::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_IRCurveBootstrap::descriptionImpl(std::ostream & os) const
{
    os << "HL_IRCurveBootstrap:\n";

    Descriptable::descriptionImpl(os);

    hl_fillDescriptionStream(irCurveData_);



} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_IRCurveBootstrap::performBootstrap()
{

    HL_PNN(mktDataCollector_);

    HL_PNN(irCurveData_);

    irCurveData_->checkIRCurveData();

    buildFakeIrCurveInMktDataCollector();

    buildInstruments();

    buildEffectiveIrCurveInMktDataCollector();


    HL_ActionPtr calibAction = build_calibAction();

    calibAction->go();


} // end performBootstrap

//------------------------------------------------------------------------------------------------------


void HL_IRCurveBootstrap::buildFakeIrCurveInMktDataCollector()
{

    VEC fakeNodeTimes(2);

    fakeNodeTimes[0]=0;/*refTime*/
    fakeNodeTimes[1]=200.;/*ultraLongPeriod*/


    HL_InterpTermStructurePtr discontingInterpTermStructure=
            buildInterpTermStructure(
                irCurveData_->get_riskFreeDiscounting()->get_riskFreeDiscountingTermStructureCode(),
                fakeNodeTimes);


    HL_InterpTermStructurePtr interpTermStructure=
            buildInterpTermStructure(irCurveData_->get_irCurveCode(), fakeNodeTimes);



} // end buildFakeIrCurveInMktDataCollector

//------------------------------------------------------------------------------------------------------


void HL_IRCurveBootstrap::buildEffectiveIrCurveInMktDataCollector()
{

    effectiveNodeTimes_.clear();
    collectMaturityNodeInformation(effectiveNodeTimes_);

    bootstrappingInterpTermStructure_ = buildInterpTermStructure(irCurveData_->get_irCurveCode(),
                                                                 effectiveNodeTimes_);

} // end buildEffectiveIrCurveInMktDataCollector



//------------------------------------------------------------------------------------------------------

HL_InterpTermStructurePtr HL_IRCurveBootstrap::buildInterpTermStructure(
        const HL_TermStructureCodePtr& irCurveCode,
        const VEC & nodeTimes) const
{


    HL_InterpTermStructurePtr interpTermStructure(new HLTS::HL_InterpTermStructure);

    HLMD::HL_MktDataCollector::addMktData(
                irCurveCode /* objCodePtr*/,
                interpTermStructure/* mktDataPtr*/,
                mktDataCollector_,
                true/* allowOverwritingExistingData*/
                );


    interpTermStructure->set_HL_ObjCodePtr(irCurveCode);

    interpTermStructure->set_discountFactorInterpVariableType(
                irCurveData_->get_discountFactorInterpVariableType());

    interpTermStructure->set_discountFactorInterpType(
                irCurveData_->get_discountFactorInterpType());

    interpTermStructure->setNodeTimes(nodeTimes);

    /*
    We now set default 0 rates
    */

    for(HLS nodeIdx=0;nodeIdx<nodeTimes.size();nodeIdx++)
    {

        interpTermStructure->setNodeDiscount(nodeIdx, 1./*nodeDiscount*/);



    } // end for nodeIdx


    return interpTermStructure;


} // end buildInterpTermStructure

//------------------------------------------------------------------------------------------------------

void HL_IRCurveBootstrap::buildInstruments()
{
    instruments_.clear();

    instruments_.resize(irCurveData_->get_mktQuotes().size());

    HL_PricingEngineDataPtr pricingEngineData(new HLPE::HL_PricingEngineData);

    pricingEngineData->set_mktDataCollector(mktDataCollector_);

    pricingEngineData->set_riskFreeDiscounting(irCurveData_->get_riskFreeDiscounting());

    pricingEngineData->set_pricingEngineChoices(irCurveData_->get_pricingEngineChoices());

    HLS i=0;

    BOOST_FOREACH(const HL_MktQuotePtr & mktQuote, irCurveData_->get_mktQuotes())
    {

        const HL_AnagraphicsPtr & anagraphics =mktQuote->get_anagraphicsPtr();

        HL_InstrumentPtr instrument_i = HLAN::buildIns(anagraphics);

        HLPE::setPricingEngineIntoIns(instrument_i, pricingEngineData);

        instruments_[i++] = instrument_i;

    } // end for mktQuote

} // end buildInstruments

//------------------------------------------------------------------------------------------------------

void HL_IRCurveBootstrap::collectMaturityNodeInformation(VEC & nodeTimes)
{

    HL_MktDataTrackerContainerPtr mktDataTrackerContainer
            = mktDataCollector_->get_mktDataTrackerContainerPtr();

    HL_PNN(mktDataTrackerContainer);

    const HL_TermStructureCodePtr & irCurveCode = irCurveData_->get_irCurveCode();

    nodeTimes.resize(1+instruments_.size());

    nodeTimes[0]=0.; // 0 to set refTime


    HLS i=0;
    BOOST_FOREACH(const HL_InstrumentPtr & instrument, instruments_)
    {


        std::stringstream ss;
        ss << mktDataTrackerString();
        ss << "_ins_" << i;

        std::string mktDataTrackerKey_i = ss.str();

        mktDataTrackerContainer->addMktDataTracker(mktDataTrackerKey_i);


        HL_InstrumentOutputPtr instrumentOutput_i = instrument->get_instrumentOutput();

        HL_MktDataTrackerPtr mktDataTracker_i = mktDataTrackerContainer->popMktDataTracker(mktDataTrackerKey_i);


        const HLMD::HL_TermStructure_Tracker_Data & termStructure_Tracker_Data
                =  *(mktDataTracker_i->get_termStructure_Tracker_Data());

        bool isIrCurveCodePresent = termStructure_Tracker_Data.is_X_present(irCurveCode/*x*/);

        HL_SRE(isIrCurveCodePresent, "i-th bootstrapping instrument does not depend on irCurveCode " << irCurveCode
               << ", ins(i)=" << instrument);

        const HLMD::HL_Bi_Real_Data & bi_Real_Data = termStructure_Tracker_Data.get_Y(irCurveCode/*x*/);

        HL_SR(!bi_Real_Data.empty());


        const HLMD::HL_RealData & endTimeRealData = bi_Real_Data.get_xy().rbegin()->first;

        HLR currentEndTime = endTimeRealData.get_x();

        if(i>0){

            HLR previousEndTime = nodeTimes[i];


            HL_SRE(currentEndTime>previousEndTime,
                   "i-th bootstrapping instrument does not end after (i-1)-th bootstrapping instrument, i=" << i
                   << ", end(i)=" << currentEndTime << ", end(i-1)=" << previousEndTime
                   << ", ins(i)=" << instrument << ", ins(i-1)=" << instruments_[i-1]);

        } // end if(i>0)

        nodeTimes[i+1] = currentEndTime;

        i++;

    } // end for on instruments_

} // end collectMaturityNodeInformation

//------------------------------------------------------------------------------------------------------

std::string HL_IRCurveBootstrap::mktDataTrackerString() const
{
    return "HL_IRCurveBootstrap_mktDataTrackerString";

} // end mktDataTrackerString

//------------------------------------------------------------------------------------------------------

HL_ActionPtr HL_IRCurveBootstrap::build_calibAction() const
{

    std::vector<HL_ActionPtr> calibActions(instruments_.size());


    HLS nodeIdx = 1;

    BOOST_FOREACH(const HL_InstrumentPtr & instrument, instruments_)
    {


        calibActions[nodeIdx-1] = buildNodeCalibAction(nodeIdx);


        nodeIdx++;

    } // end for on instruments_



    HL_ActionSequencePtr calibActionSequence(new HL::HL_ActionSequence);

    calibActionSequence->set_actions(calibActions);

    return calibActionSequence;

} // end build_calibAction

//------------------------------------------------------------------------------------------------------

HL_CalibActionPtr HL_IRCurveBootstrap::buildNodeCalibAction(HLS nodeIdx) const
{

    HL_IRCurveBootstrapModifierPtr irCurveBootstrapModifier (new HL_IRCurveBootstrapModifier);


    irCurveBootstrapModifier->set_data(bootstrappingInterpTermStructure_, nodeIdx);


    HLS mktQuoteIdx =nodeIdx-1;

    const HL_MktQuotePtr & mktQuote = irCurveData_->get_mktQuotes().at(mktQuoteIdx);

    const HL_InstrumentPtr & instrument = instruments_.at(mktQuoteIdx);

    HLR instrumentTargetValue = mktQuote->get_value();

    HL_IRBootstrapNodeTargetFunctionPtr irBootstrapNodeTargetFunction(new HL_IRBootstrapNodeTargetFunction);

    irBootstrapNodeTargetFunction->set_modifier(irCurveBootstrapModifier);

    irBootstrapNodeTargetFunction->set_instrument(instrument);

    irBootstrapNodeTargetFunction->set_instrumentTargetValue(instrumentTargetValue);


    HL_CalibActionSolvePtr nodeCalibActionSolve(new HL_CalibActionSolve);


    nodeCalibActionSolve->set_targetFunction(irBootstrapNodeTargetFunction);

    HL_RootFinderDataPtr rootFinderData = buildRootFinderData(nodeIdx);

    nodeCalibActionSolve->set_rootFinderData(rootFinderData);


    HL_RootFinderPtr rootFinder(new HLMA::HL_RootFinderToms748);

    nodeCalibActionSolve->set_rootFinder(rootFinder);


    return nodeCalibActionSolve;


} // end buildNodeCalibAction

//------------------------------------------------------------------------------------------------------

HL_RootFinderDataPtr HL_IRCurveBootstrap::buildRootFinderData(HLS nodeIdx) const
{

    HLR currentNodeTime = effectiveNodeTimes_[nodeIdx];

    /**
    No more than 100% of interest rate (positive or negative) could be bootstrapped in the node.
    */
    HLR maxRate = 1.;

    HL_RootFinderDataPtr rootFinderData(new HLMA::HL_RootFinderData);

    HLR df_a = std::exp(-maxRate*currentNodeTime);

    rootFinderData->set_init_a(df_a);

    HLR df_b = 1/df_a;

    rootFinderData->set_init_b(df_b);

    rootFinderData->set_maxFunctionInvocations(1000 /*maxFunctionInvocations*/);

    /*
    Corresponds to about 10^-10.
    */
    rootFinderData->set_digitTolerance(31 /*digitTolerance*/);

    return rootFinderData;


} // end buildNodeCalibAction

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IRCurveBootstrap: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IRCurveBootstrapModifier
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_IRCurveBootstrapModifier::HL_IRCurveBootstrapModifier()
{

    classDefaultInit();



} // end HL_IRCurveBootstrapModifier

//------------------------------------------------------------------------------------------------------

HL_IRCurveBootstrapModifier::~HL_IRCurveBootstrapModifier()
{
} // end ~HL_IRCurveBootstrapModifier


//------------------------------------------------------------------------------------------------------

void HL_IRCurveBootstrapModifier::classDefaultInit()
{

    nodeIdx_=HL_NULL_INTEGER;


} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_IRCurveBootstrapModifier::descriptionImpl(std::ostream & os) const
{

    os << "HL_IRCurveBootstrapModifier:\n";

    HL_Modifier::descriptionImpl(os);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_IRCurveBootstrapModifier::set_data(const HL_InterpTermStructurePtr& bootstrappingInterpTermStructure, HLS nodeIdx)
{
    bootstrappingInterpTermStructure_=bootstrappingInterpTermStructure;

    nodeIdx_=nodeIdx;

    HL_SR(nodeIdx_<bootstrappingInterpTermStructure_->get_nbNodes());

} // end set_data


//------------------------------------------------------------------------------------------------------

void HL_IRCurveBootstrapModifier::modify(const VEC::const_iterator & b, const VEC::const_iterator & e) const
{

    HLR df = *b;

    bootstrappingInterpTermStructure_->setNodeDiscount(nodeIdx_, df);

} // end modify

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IRCurveBootstrapModifier: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IRBootstrapNodeTargetFunction
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_IRBootstrapNodeTargetFunction::HL_IRBootstrapNodeTargetFunction()
{

    classDefaultInit();



} // end HL_IRBootstrapNodeTargetFunction

//------------------------------------------------------------------------------------------------------

HL_IRBootstrapNodeTargetFunction::~HL_IRBootstrapNodeTargetFunction()
{
} // end ~HL_IRBootstrapNodeTargetFunction


//------------------------------------------------------------------------------------------------------

void HL_IRBootstrapNodeTargetFunction::classDefaultInit()
{

    domainDim_=1;

    instrumentTargetValue_=HL_NAN;

    service_x_vec_= VEC(1, 0);

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_IRBootstrapNodeTargetFunction::descriptionImpl(std::ostream & os) const
{

    os << "HL_IRBootstrapNodeTargetFunction:\n";

    HL_TargetFunction::descriptionImpl(os);


} // end descriptionImpl


//------------------------------------------------------------------------------------------------------

HLR HL_IRBootstrapNodeTargetFunction::operator()(HLR x) const
{
    service_x_vec_[0]=x;

    HLR diff = value_n_1(service_x_vec_.begin(), service_x_vec_.end());

    return diff;
} // end operator


//------------------------------------------------------------------------------------------------------

HLR HL_IRBootstrapNodeTargetFunction::computeTargetValue(const VEC::const_iterator & b, const VEC::const_iterator & e) const
{
    /*
    LAST(20150802)
    implementa questo metodo calcolando la differenza tra prezzo di mercato dello strumento
    di bootstrap nodeIdx-esimo e il prezzo di modello dopo che sia stato usato il modifier
    sulla curva...

    poi il bootstrap sembrerebbe fatto e non resta che interfacciarlo a python...
    */

    HLR instrumentValue = instrument_->get_dirtyPrice();

    HLR delta = instrumentValue-instrumentTargetValue_;

    return delta;

} // end computeTargetValue


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IRBootstrapNodeTargetFunction: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_build_swap_mktQuotes
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


std::vector<HL_MktQuotePtr> HL_TEST_build_swap_mktQuotes(const date & refDate)
{
    std::vector<HL_MktQuotePtr> swapMktQuotes;

    HLS nbYears = 50;

    HL_Period fixedCouponFrequency(1, HL_PeriodUnit_Years);

    HLR fixedRate = 0.04;

    HL_Period floatCouponFrequency(6, HL_PeriodUnit_Months);




    /*
    The ibor index code is reconstructed inside, in the same way it has been constructed when
    pre-building the mktDataCollector. This ensurs that the ibor index will be found.
    */
    HLS iborNbMonths = 6;

    for(HLS y=1;y<=nbYears;y++)
    {

        HL_Period scheduleLength(y, HL_PeriodUnit_Years);

        HL_SwapAnagraphicsPtr swapAnagraphicsPtr = HLAN::HL_TEST_HL_get_SwapAnagraphics(refDate /*spotDate*/,
                                                                                        scheduleLength,
                                                                                        fixedCouponFrequency,
                                                                                        fixedRate,
                                                                                        floatCouponFrequency,
                                                                                        iborNbMonths);

        HL_MktQuotePtr mktQuote(new HLMQS::HL_MktQuote);

        mktQuote->set_anagraphicsPtr(swapAnagraphicsPtr);

        mktQuote->set_value(0. /*at par swap*/);

        mktQuote->set_quotationTime(ptime(refDate));

        swapMktQuotes.push_back(mktQuote);


    } // end for y


    return swapMktQuotes;
} // end HL_TEST_build_swap_mktQuotes


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_build_mktQuotes
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


std::vector<HL_MktQuotePtr> HL_TEST_build_mktQuotes(const date & refDate)
{
    std::vector<HL_MktQuotePtr> mktQuotes = HL_TEST_build_swap_mktQuotes(refDate);




    return mktQuotes;

} // end HL_TEST_build_mktQuotes



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_HL_IRCurveData
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_PricingEngineChoicesPtr HL_TEST_build_pricingEngineChoices()
{

    HL_PricingEngineChoicesPtr pricingEngineChoices(new HLPE::HL_PricingEngineChoices);

    pricingEngineChoices->setAssociation(HLINS::HL_CashFlowType_Fixed /*cashFlowType*/,
                                         HLPE::HL_CashFlowPricingEngineType_FixedCashFlow /*cashFlowPricingEngineType*/);

    pricingEngineChoices->setAssociation(HLINS::HL_CashFlowType_UnderlyingDelivery /*cashFlowType*/,
                                         HLPE::HL_CashFlowPricingEngineType_UnderlyingDelivery /*cashFlowPricingEngineType*/);



    return pricingEngineChoices;

} // end HL_TEST_build_pricingEngineChoices


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_HL_IRCurveData
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_IRCurveDataPtr HL_TEST_get_HL_IRCurveData(HL_TEST_MktDataCollData& mktDataCollData)
{

    mktDataCollData= HLMD::HL_TEST_create_HL_TEST_MktDataCollData();

    HL_IRCurveDataPtr irCurveData(new HLMD::HL_IRCurveData);

    irCurveData->set_irCurveCode(mktDataCollData.termStructureCodes[HL_TEST_eur_6m_forwarding_curve]);


    irCurveData->set_riskFreeDiscounting(mktDataCollData.riskFreeDiscountings[EUR_EONIA_RiskFreeDiscounting]);


    irCurveData->set_mktQuotes( HL_TEST_build_mktQuotes(mktDataCollData.mktDataCollector->get_refDate()));


    irCurveData->set_discountFactorInterpVariableType(
                HLTS::HL_DiscountFactorInterpVariableType_Rate);


    irCurveData->set_discountFactorInterpType(HLINTP::HL_InterpolatorType_n_D_Linear);

    irCurveData->set_pricingEngineChoices(HL_TEST_build_pricingEngineChoices());



    return irCurveData;

} // end HL_TEST_get_HL_IRCurveData



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_HL_IRCurveBootstrap
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


void HL_TEST_HL_IRCurveBootstrap()
{

    HL_TEST_MktDataCollData mktDataCollData;

    HL_IRCurveDataPtr irCurveData = HL_TEST_get_HL_IRCurveData(mktDataCollData);


    HL_IRCurveBootstrapPtr irCurveBootstrap(new HLMD::HL_IRCurveBootstrap);


    irCurveBootstrap->set_irCurveData(irCurveData);


    irCurveBootstrap->set_mktDataCollector(mktDataCollData.mktDataCollector);

    irCurveBootstrap->performBootstrap();


    HL_InterpTermStructurePtr bootstrappingInterpTermStructure=
            irCurveBootstrap->get_bootstrappingInterpTermStructure();





    HL_GET_LOGGER(false/*addTimer*/);


    HL_LOG(HLLOG::HL_severity_level_notification, "xxxxxxxxxxxxxxxxxxxxxxx");
    HL_LOG(HLLOG::HL_severity_level_notification, "BOOTSTRAP");

    for(HLS i=1;i<=60;i++)
    {

        HLR t_i = i;

        HLR df_i = bootstrappingInterpTermStructure->df(t_i);

        HLR rate_i = -std::log(df_i)/t_i;


        HL_LOG(HLLOG::HL_severity_level_notification, "t_i=" << t_i
               << ", df_i=" << df_i << ", rate_i=" << rate_i);

    } // end for i

    HL_LOG(HLLOG::HL_severity_level_notification, "---------------------");


    const VEC & effectiveNodeTimes = irCurveBootstrap->get_effectiveNodeTimes();

    const std::vector<HL_InstrumentPtr> & instruments=irCurveBootstrap->get_instruments();

    HL_SR(effectiveNodeTimes.size()==instruments.size()+1);

    HLS i=1;
    BOOST_FOREACH(const HL_InstrumentPtr & ins_i, instruments)
    {

        HLR t_i = effectiveNodeTimes[i];

       // ins_i->purgeAllComputations();

        HLR insValue_i = ins_i->get_dirtyPrice();

        HLR insValue_i_2nd = ins_i->get_dirtyPrice();

        HL_REQ_EQUAL_FLOATS(insValue_i, insValue_i_2nd);

        HL_LOG(HLLOG::HL_severity_level_notification,
               "i= "<< i
               << ", t_i="
               << t_i
               << ", insValue_i=" << insValue_i);




        i++;

    } // end for ins_i


    HL_LOG(HLLOG::HL_severity_level_notification, "xxxxxxxxxxxxxxxxxxxxxxx");


} // end HL_TEST_HL_IRCurveBootstrap





} // end namespace HL_MarketData
} //end namespace HorizonLib




