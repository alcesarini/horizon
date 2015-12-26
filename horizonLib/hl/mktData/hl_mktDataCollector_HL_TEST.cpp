/**
FILE NAME= hl_mktDataCollector_HL_TEST.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20150919
*/
#include <hl/mktData/hl_mktDataCollector_HL_TEST.h>
#include <hl/underlyings/interestRates/hl_iborIndex.h>
#include <hl/math/probMeasures/hl_probMeasure.h>
#include <hl/mktData/volSurfaces/hl_volSurface.h>
#include <hl/mktData/correlations/hl_correlationTermStructure.h>

namespace HorizonLib
{
namespace HL_MarketData
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_create_HL_MktDataCollectorPtr
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

void HL_TEST_built_termStructureCodes(
        std::map<std::string, HL_TermStructureCodePtr> &termStructureCodes)
{
    termStructureCodes.clear();


    termStructureCodes[HL_TEST_eur_eonia_risk_free_discounting]
            =HLMA::HL_TEST_get_irCurveCode(HL_TEST_eur_eonia_risk_free_discounting);




    termStructureCodes[HL_TEST_eur_6m_forwarding_curve]
            =HLMA::HL_TEST_get_irCurveCode(HL_TEST_eur_6m_forwarding_curve);



} // end HL_TEST_built_termStructureCodes



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_build_iborIndexs
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

void HL_TEST_build_iborIndexs(std::map<std::string, HL_IborIndexCodePtr> &iborIndexCodes,
                              const HL_MktDataCollectorPtr & mktDataCollector,
                              std::map<std::string, HL_VolSurfaceCodePtr> & volSurfaceCodes,
                              std::map<std::string, HL_TermStructureCodePtr> &termStructureCodes
                              )
{
    iborIndexCodes.clear();

    HLS nbMonths=1;

    HLIR::HL_TEST_build_HL_IborIndex(
                mktDataCollector,
                termStructureCodes[HL_TEST_eur_eonia_risk_free_discounting],
                nbMonths,
                volSurfaceCodes[HL_TEST_eur_6m_forwarding_curve_VOL],
                iborIndexCodes[HL_TEST_eur_EONIA_index_1m]
                );


    nbMonths=6;

    HLIR::HL_TEST_build_HL_IborIndex(
                mktDataCollector,
                termStructureCodes[HL_TEST_eur_6m_forwarding_curve],
                nbMonths,
                volSurfaceCodes[HL_TEST_eur_ibor_6m_VOL],
                iborIndexCodes[HL_TEST_eur_ibor_6m]);




    HLINTERACTIONS::HL_TEST_build_HL_InterpInteractionTermStructurePtr(
                iborIndexCodes[HL_TEST_eur_ibor_6m] /*objCodePtr1*/,
                iborIndexCodes[HL_TEST_eur_EONIA_index_1m]  /*objCodePtr2*/,
                mktDataCollector
                );

} // end HL_TEST_build_iborIndexs



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_build_riskFreeDiscountings
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


void HL_TEST_build_riskFreeDiscountings(
        std::map<std::string, HL_RiskFreeDiscountingPtr> & riskFreeDiscountings,
        std::map<std::string, HL_IborIndexCodePtr> & iborIndexCodes,
        std::map<std::string, HL_TermStructureCodePtr> &termStructureCodes)
{

    riskFreeDiscountings.clear();

    riskFreeDiscountings[EUR_EONIA_RiskFreeDiscounting] =
            HLMA::HL_TEST_get_riskFreeDiscounting(
                /*riskFreeDiscountingTermStructureCode*/
                termStructureCodes[HL_TEST_eur_eonia_risk_free_discounting],
                /* riskFreeDiscountingCurveIborIndexCode*/
                iborIndexCodes[HL_TEST_eur_EONIA_index_1m]
                );


} // end HL_TEST_build_riskFreeDiscountings


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_build_volSurfaces
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

void HL_TEST_build_volSurfaces(
        const HL_MktDataCollectorPtr & mktDataCollector,
        std::map<std::string, HL_RiskFreeDiscountingPtr> & riskFreeDiscountings,
        std::map<std::string, HL_VolSurfaceCodePtr> & volSurfaceCodes)
{

    std::map<std::string, HL_VolSurfaceCodePtr>::const_iterator cIt = volSurfaceCodes.begin();

    while(cIt!=volSurfaceCodes.end())
    {
        const HL_VolSurfaceCodePtr & volSurfaceCode = cIt->second;

        HL_VolSurfacePtr impliedVolSurface =
                HLVOL::HL_TEST_get_HL_VolSurface(volSurfaceCode,
                                                 riskFreeDiscountings[EUR_EONIA_RiskFreeDiscounting],
                                                 0.0022/* flatVolValue*/);

        HLMD::HL_MktDataCollector::addMktData(volSurfaceCode /*objCodePtr*/,
                                              impliedVolSurface /*mktDataPtr*/,
                                              mktDataCollector,
                                              false/* allowOverwritingExistingData*/);

        cIt++;
    } // end while cIt



} // end HL_TEST_build_volSurfaces


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_create_HL_TEST_MktDataCollData
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_TEST_MktDataCollData HL_TEST_create_HL_TEST_MktDataCollData()
{
    HL_TEST_MktDataCollData mktDataCollData;

    mktDataCollData.mktDataCollector.reset(new HLMD::HL_MktDataCollector);

    date refDate(2015, Sep, 29);

    mktDataCollData.mktDataCollector->set_refTime(ptime(refDate));

    HL_TEST_built_termStructureCodes(mktDataCollData.termStructureCodes);

    HL_TEST_build_iborIndexs(mktDataCollData.iborIndexCodes,
                             mktDataCollData.mktDataCollector,
                             mktDataCollData.volSurfaceCodes,
                             mktDataCollData.termStructureCodes);

    HL_TEST_build_riskFreeDiscountings(
                mktDataCollData.riskFreeDiscountings,
                mktDataCollData.iborIndexCodes,
                mktDataCollData.termStructureCodes);

    HL_TEST_build_volSurfaces(
                mktDataCollData.mktDataCollector,
                mktDataCollData.riskFreeDiscountings,
                mktDataCollData.volSurfaceCodes);





    return mktDataCollData;

} // end HL_TEST_create_HL_TEST_MktDataCollData


} // end namespace HL_MarketData
} //end namespace HorizonLib
