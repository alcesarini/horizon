/**
FILE NAME=hl_probMeasure.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140726
*/
#include <hl/math/probMeasures/hl_probMeasure.h>
#include <hl/underlyings/interestRates/hl_iborIndex.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLMA::HL_RiskFreeDiscounting);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLMA::HL_FwdMeasure);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLMA::HL_Expectation);

namespace HorizonLib
{
namespace HL_Math
{




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RiskFreeDiscounting
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_RiskFreeDiscounting::HL_RiskFreeDiscounting()
{
    classDefaultInit();

} // end HL_RiskFreeDiscounting

//------------------------------------------------------------------------------------------------------

HL_RiskFreeDiscounting::~HL_RiskFreeDiscounting()
{} // end ~HL_RiskFreeDiscounting

//------------------------------------------------------------------------------------------------------

void HL_RiskFreeDiscounting::classDefaultInit()
{} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_RiskFreeDiscounting::descriptionImpl(std::ostream & os) const
{

    Descriptable::descriptionImpl(os);
    os << "HL_RiskFreeDiscounting:\n";
    hl_fillDescriptionStream(riskFreeDiscountingTermStructureCode_);
    hl_fillDescriptionStream(riskFreeDiscountingCurveIborIndexCode_);





} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

HL_Order HL_RiskFreeDiscounting::getOrder(const HL_RiskFreeDiscounting & riskFreeDiscounting) const
{

    HL_PLAIN_ORDER_COMPARE(riskFreeDiscountingTermStructureCode_, riskFreeDiscounting.riskFreeDiscountingTermStructureCode_);

    HL_PLAIN_ORDER_COMPARE(riskFreeDiscountingCurveIborIndexCode_, riskFreeDiscounting.riskFreeDiscountingCurveIborIndexCode_);

    return HL_Order_1_Eq_2;


} // end getOrder


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Measure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_Measure::HL_Measure()
{
    classDefaultInit();

} // end HL_Measure

//------------------------------------------------------------------------------------------------------

HL_Measure::~HL_Measure()
{} // end ~HL_Measure

//------------------------------------------------------------------------------------------------------

void HL_Measure::classDefaultInit()
{} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_Measure::descriptionImpl(std::ostream & os) const
{

    Descriptable::descriptionImpl(os);


    hl_fillDescriptionStream(riskFreeDiscounting_);

} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

bool HL_Measure::operator==(const HL_MeasurePtr & extMeasure) const
{

    HL_PNN(extMeasure);

    if(measureType()!=extMeasure->measureType())
        return false;


    if(get_riskFreeDiscounting()!=extMeasure->get_riskFreeDiscounting())
        return false;


    return true;


} // end operator==


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FwdMeasure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_FwdMeasure::HL_FwdMeasure()
{
    classDefaultInit();

} // end HL_FwdMeasure

//------------------------------------------------------------------------------------------------------

HL_FwdMeasure::~HL_FwdMeasure()
{} // end ~HL_FwdMeasure

//------------------------------------------------------------------------------------------------------

void HL_FwdMeasure::classDefaultInit()
{} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_FwdMeasure::descriptionImpl(std::ostream & os) const
{

    HL_Measure::descriptionImpl(os);
    os << "HL_FwdMeasure:\n";
    hl_fillDescriptionStream(payDate_);

} // end descriptionImpl


//------------------------------------------------------------------------------------------------------

bool HL_FwdMeasure::operator==(const HL_MeasurePtr & extMeasure) const
{

    if(!HL_Measure::operator==(extMeasure))
        return false;


    HL_DYN_SHARED_PTR_CAST(HL_FwdMeasure, castedExtMeasure, extMeasure);



    if(get_payDate()!=castedExtMeasure->get_payDate())
        return false;

    return true;


} // end operator==


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Expectation
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_Expectation::HL_Expectation()
{
    classDefaultInit();

} // end HL_Expectation

//------------------------------------------------------------------------------------------------------

HL_Expectation::~HL_Expectation()
{} // end ~HL_Expectation

//------------------------------------------------------------------------------------------------------

void HL_Expectation::classDefaultInit()
{} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_Expectation::descriptionImpl(std::ostream & os) const
{

    Descriptable::descriptionImpl(os);
    os << "HL_Expectation:\n";
    hl_fillDescriptionStream(value_);
    hl_fillDescriptionStream(measure_);





} // end descriptionImpl

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_ccyCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CcyCodePtr HL_TEST_get_ccyCode()
{

    return HLCCY::HL_TEST_get_HL_CcyCode();


} // end HL_TEST_get_ccyCode




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_irCurveCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_TermStructureCodePtr HL_TEST_get_irCurveCode(const std::string & curveName)
{
    HL_TermStructureCodePtr irCurveCode(new HLTS::HL_TermStructureCode);

    irCurveCode->set_sCode(curveName);

    irCurveCode->set_ccyCode(HL_TEST_get_ccyCode());

    return irCurveCode;

} // end HL_TEST_get_irCurveCode


////------------------------------------------------------------------------------------------------------
////------------------------------------------------------------------------------------------------------
//// HL_TEST_get_HL_IborIndexCode
////------------------------------------------------------------------------------------------------------
////------------------------------------------------------------------------------------------------------


//HL_IborIndexCodePtr HL_TEST_get_HL_IborIndexCode(const std::string & iborIndexName)
//{
//    HL_IborIndexCodePtr iborIndexCode(new HLIR::HL_IborIndexCode);


//    iborIndexCode->set_ccyCode(HL_TEST_get_ccyCode());

//    iborIndexCode->set_sCode(iborIndexName);


//    return iborIndexCode;

//} // end HL_TEST_get_HL_IborIndexCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_riskFreeDiscounting
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_RiskFreeDiscountingPtr HL_TEST_get_riskFreeDiscounting(
        const HL_TermStructureCodePtr & riskFreeDiscountingTermStructureCode,
        const HL_IborIndexCodePtr & riskFreeDiscountingCurveIborIndexCode
        )
{
    HL_RiskFreeDiscountingPtr riskFreeDiscounting(new HLMA::HL_RiskFreeDiscounting);


    riskFreeDiscounting->set_riskFreeDiscountingTermStructureCode(
                riskFreeDiscountingTermStructureCode);

    riskFreeDiscounting->set_riskFreeDiscountingCurveIborIndexCode(
                riskFreeDiscountingCurveIborIndexCode);

    return riskFreeDiscounting;

}// end HL_TEST_get_riskFreeDiscounting


} // end namespace HL_Math
} //end namespace HorizonLib
