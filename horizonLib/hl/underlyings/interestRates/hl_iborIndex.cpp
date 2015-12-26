/**
FILE NAME= hl_iborIndex.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131216
*/


#include <hl/underlyings/interestRates/hl_iborIndex.h>
#include <hl/mktData/hl_mktDataCollector.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLIR::HL_IborIndex);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLIR::HL_IborIndexCode);

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
// class HL_IborIndexCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_IborIndexCode::HL_IborIndexCode()
{
    classDefaultInit();

} // end HL_IborIndexCode

//------------------------------------------------------------------------------------------------------

HL_IborIndexCode::~HL_IborIndexCode()
{} // end ~HL_IborIndexCode

//------------------------------------------------------------------------------------------------------

void HL_IborIndexCode::classDefaultInit()
{} // end classDefaultInit
//------------------------------------------------------------------------------------------------------

HLSTRING HL_IborIndexCode::objTypeImpl() const
{
    return "HL_IborIndexCode";
} // end objTypeImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IborIndex
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_IborIndex::HL_IborIndex()
{

    classDefaultInit();



} // end HL_IborIndex

//------------------------------------------------------------------------------------------------------

HL_IborIndex::~HL_IborIndex()
{} // end ~HL_IborIndex

//------------------------------------------------------------------------------------------------------

void HL_IborIndex::classDefaultInit()
{} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

HLR HL_IborIndex::tau(const date & accrualStartDate, const date & accrualEndDate) const
{

    HLR yf = dcc_->yf(accrualStartDate, accrualEndDate);

    return yf;


} // end tau


//------------------------------------------------------------------------------------------------------

date HL_IborIndex::accrualEndDate(const date & accrualStartDate) const
{

    date aed= calendar_->advance(accrualStartDate,
                                 tenor_,
                                 accrualEndDateBDC_/*HL_BusinessDayConvention_Following*/,
                                 accrualEndDatePreserveLastBusinessDayOfMonth_/*send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth*/
                                 );

    return aed;


} // end accrualEndDate

//------------------------------------------------------------------------------------------------------

date HL_IborIndex::get_payDate(const date & accrualEndDate) const
{

    date pd= calendar_->adjust(accrualEndDate, payDate_bdc_);
    return pd;

} // end get_payDate


//------------------------------------------------------------------------------------------------------
void HL_IborIndex::descriptionImpl(std::ostream & os) const
{

    HL_InterestRate::descriptionImpl(os);

    hl_fillDescriptionStream(accrualEndDateBDC_);
    hl_fillDescriptionStream(accrualEndDatePreserveLastBusinessDayOfMonth_);
    hl_fillDescriptionStream(dcc_);
    hl_fillDescriptionStream(iborForwardingTermStructureCode_);
    hl_fillDescriptionStream(payDate_bdc_);

} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

HLR HL_IborIndex::iborFixingFormula(const date & fixingDate) const
{

    date accrStartDate = accrualStartDate(fixingDate);


    date accrEndDate = accrualEndDate(accrStartDate);


    HLR accrualFract = tau(accrStartDate, accrEndDate);


    HL_SRE(accrualFract>0., "accrStartDate=" << accrStartDate << ", accrEndDate=" << accrEndDate);

    HLR fwd = get_interest(accrStartDate, accrEndDate) /accrualFract;

    return fwd;


} // end iborFixingFormula

//------------------------------------------------------------------------------------------------------

HLR HL_IborIndex::get_interest(const date & accrualStartDate, const date & accrualEndDate) const
{


    HL_TermStructurePtr iborForwardingTermStructure
            = get_mktDataCollector()->get_mktData<HL_TermStructurePtr>(iborForwardingTermStructureCode_);

    HLR discountStart = iborForwardingTermStructure->df(accrualStartDate);

    HL_SRE(discountStart>0., "discountStart=" << discountStart << ", accrualEndDate=" << accrualEndDate <<
           ", iborForwardingTermStructureCode_=" << iborForwardingTermStructureCode_);


    HLR discountEnd = iborForwardingTermStructure->df(accrualEndDate);

    HL_SRE(discountEnd>0., "discountEnd=" << discountEnd << ", accrualEndDate=" << accrualEndDate <<
           ", iborForwardingTermStructureCode_=" << iborForwardingTermStructureCode_);


    HLR interest = discountEnd / discountStart -1;

    return interest;

} // end get_interest


//------------------------------------------------------------------------------------------------------

HLR HL_IborIndex::forecastQuotingMeasureExpectationImpl(const ptime & fixingTime) const
{


    /*
     *  loose time precision, at least up to current implementation... maybe recovered by
     * letting accrualStartDate(..) get a time in input instead of a date,m and so on for
     * connected stuff.
     * */

    date fixingDate = fixingTime.date();

    HLR fwd = iborFixingFormula(fixingDate);

    return fwd;


} // end forecastQuotingMeasureExpectationImpl

//------------------------------------------------------------------------------------------------------

HL_MeasurePtr HL_IborIndex::get_quotingMeasure(const ptime & fixingTime) const
{

    HL_FwdMeasurePtr quotingFwdMeasure(new HLMA::HL_FwdMeasure);


    quotingFwdMeasure->set_riskFreeDiscounting(get_impliedVolSurface()->get_riskFreeDiscounting());


    date fixingDate = fixingTime.date();


    date accrStartDate = accrualStartDate(fixingDate);

    date accrEndDate = accrualEndDate(accrStartDate);

    date payDate = get_payDate(accrEndDate);

    quotingFwdMeasure->set_payDate(payDate);


    return quotingFwdMeasure;




} // end get_quotingMeasure



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_HL_IborIndexCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



HL_IborIndexCodePtr HL_TEST_get_HL_IborIndexCode(HLS nbMonths)
{
    HL_IborIndexCodePtr iborIndexCode(new HLIR::HL_IborIndexCode);

    std::stringstream ss;

    ss << "HL_TEST_get_HL_IborIndexCode_EUR_" << nbMonths << "M";

    iborIndexCode->set_sCode(ss.str());


    HL_CcyCodePtr ccyCode = HLCCY::HL_TEST_get_HL_CcyCode();


    iborIndexCode->set_ccyCode(ccyCode);

    return iborIndexCode;


} // end HL_TEST_get_HL_IborIndexCode



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_build_HL_IborIndex
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



void HL_TEST_build_HL_IborIndex(
        const HL_MktDataCollectorPtr & mktDataCollectorPtr,
        const HL_TermStructureCodePtr & iborForwardingTermStructureCode,
        HLS nbMonths,
        HL_VolSurfaceCodePtr &volSurfaceCode,
        HL_IborIndexCodePtr &iborIndexCode
        )
{


    /*
    LAST(2015090)

    TOGLIERE LE CURVE, LE VOL, LE CORRS, ETC.. OVVERO TUTTI I DATI DI MKT
    DAGLI UNDERLYINGS COME IBORX_INDEX AD ESEMPIO.

    IN QUESTI UNDERLYING LASCIARE SOLO I CODES DEI DATI DI MKT CORRISPONDENTI DA RACCATTARE
    ALL'INTERNO DEL MKT DATA COLLECTOR.

    QUESTO DOVREBBE FACILITARE ALQUANTO IL BOOTSTRAP.

    QUINDI SE SERVE CALCOLARE IL FED FI IBOR AD UNA CERTA DATA, PRIMA SI PESCA LA CURVA
    NEL MKT DATA COLLECTOR, SENZA SALVARLA DA NESSUNA ALTRA PARTE, E POI SI FA
    IL CALCOLO USUALE.

    NOTARE CHE IN QUESTO MODO IL CONCETTO DI UNDERLYING DIVENTA QUELLO DI ANAGRAFICA + CAPACITA'
    E FORMULE DI CALCOLO.

    */
    iborIndexCode = HL_TEST_get_HL_IborIndexCode(nbMonths);

    HL_IborIndexPtr iborIndex(new HLIR::HL_IborIndex);


    iborIndex->set_HL_ObjCodePtr(iborIndexCode);


    iborIndex->set_accrualEndDateBDC(HL_BusinessDayConvention_Unadjusted);


    iborIndex->set_accrualEndDatePreserveLastBusinessDayOfMonth(false);

    HL_DccPtr iborDcc(new HLDT::HL_Dcc_Act360);


    iborIndex->set_dcc(iborDcc);



    iborIndex->set_iborForwardingTermStructureCode(iborForwardingTermStructureCode);

    iborIndex->set_payDate_bdc(HL_BusinessDayConvention_Following);


    iborIndex->set_tenor(HL_Period(nbMonths, HL_PeriodUnit_Months));


    iborIndex->set_fixingDays(2);

    HL_CalendarPtr iborFakeCalendar(new HLCAL::HL_FakeCalendar);


    iborIndex->set_calendar(iborFakeCalendar);

    volSurfaceCode =  HLVOL::HL_TEST_get_HL_VolSurfaceCode(iborIndexCode);


    iborIndex->set_impliedVolSurfaceCode(volSurfaceCode);

    const date & refDate = mktDataCollectorPtr->get_refDate();

    HLR spot = 0.02;

    std::vector<HLR> fixingValues(10, spot);

    HL_TimeRealHistoryPtr dateRealHistory
            = HLOBJ::HLTEST_get_HL_TimeRealHistory(iborIndexCode,
                                                   refDate,
                                                   "THE_FAKE_HISTORY" /*historyTag*/,
                                                   fixingValues);

    iborIndex->set_hl_TimeRealHistoryPtr(dateRealHistory);






    /*
    LAST(20150903)

    ORA FINISCI DI COSTRUIRE/RIEMPIRE impliedVolSurface (see HL_TEST_get_HL_VolSurface).

    poi costruisci la curca di forwrding dell'ibor e di discounting che ti servirà dopo per pricing
    e mettile nel mkt data collector.

    a quel punto si può procedere a costruire il forwalet su ibor, poi lo swap, poi si bootstrappa la
    curva di forwarding....
    */
    HLMD::HL_MktDataCollector::addMktData(iborIndexCode /*objCodePtr*/,
                                          iborIndex /*mktDataPtr*/,
                                          mktDataCollectorPtr,
                                          false/* allowOverwritingExistingData*/);



    //The implied vol of the underlying quoted by the mkt (notice that
    //the vol can be expressed as normal vol, log-normal vol, shifted log-normal, etc..)
    //according to its internal variable.
    //*/


} // end HL_TEST_build_HL_IborIndex




} // end namespace HL_InterestRates
} // end namespace HL_Underlyings
} // end namespace HL_MarketData
} //end namespace HorizonLib
