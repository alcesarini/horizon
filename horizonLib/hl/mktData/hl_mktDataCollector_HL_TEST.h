/**
FILE NAME= hl_mktDataCollector_HL_TEST.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20150919
*/
#ifndef _hl_mktDataCollector_HL_TEST_h_
#define _hl_mktDataCollector_HL_TEST_h_

#include <hl/mktData/hl_mktDataCollector.h>


namespace HorizonLib
{
namespace HL_MarketData
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// struct HL_TEST_MktDataCollData
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

struct HL_TEST_MktDataCollData
{

    HL_MktDataCollectorPtr mktDataCollector;

    std::map<std::string, HL_TermStructureCodePtr> termStructureCodes;
    std::map<std::string, HL_IborIndexCodePtr> iborIndexCodes;
    std::map<std::string, HL_VolSurfaceCodePtr> volSurfaceCodes;
    std::map<std::string, HL_RiskFreeDiscountingPtr> riskFreeDiscountings;

}; // end struct HL_TEST_MktDataCollData

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_create_HL_MktDataCollectorPtr
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_TEST_MktDataCollData HL_TEST_create_HL_TEST_MktDataCollData();

//------------------------------------------------------------------------------------------------------

#define HL_TEST_eur_eonia_risk_free_discounting "HL_TEST_eur_eonia_risk_free_discounting"

//------------------------------------------------------------------------------------------------------


#define HL_TEST_eur_6m_forwarding_curve "HL_TEST_eur_6m_forwarding_curve"

//------------------------------------------------------------------------------------------------------

#define HL_TEST_eur_6m_forwarding_curve_VOL "HL_TEST_eur_6m_forwarding_curve_VOL"

//------------------------------------------------------------------------------------------------------

#define HL_TEST_eur_ibor_6m "HL_TEST_eur_ibor_6m"

//------------------------------------------------------------------------------------------------------

#define HL_TEST_eur_ibor_6m_VOL "HL_TEST_eur_ibor_6m_VOL"

//------------------------------------------------------------------------------------------------------

#define HL_TEST_eur_EONIA_index_1m "HL_TEST_eur_EONIA_index_1m"

//------------------------------------------------------------------------------------------------------

#define EUR_EONIA_RiskFreeDiscounting "EUR_EONIA_RiskFreeDiscounting"

//------------------------------------------------------------------------------------------------------

} // end namespace HL_MarketData
} //end namespace HorizonLib


#endif // _hl_mktDataCollector_HL_TEST_h_
