/**
FILE NAME=hl_convAdjMeasureChange.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140726
*/
#include <hl/math/probMeasures/hl_convAdjMeasureChange.h>
#include <hl/underlyings/interestRates/hl_iborIndex.h>
#include <hl/mktData/hl_mktData.h>
#include <hl/mktData/hl_mktDataCollector.h>

namespace HorizonLib
{
namespace HL_Math
{




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_ConvexityAdjuster
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_ConvexityAdjuster::HL_ConvexityAdjuster()
{
    classDefaultInit();

} // end HL_ConvexityAdjuster

//------------------------------------------------------------------------------------------------------

HL_ConvexityAdjuster::~HL_ConvexityAdjuster()
{} // end ~HL_ConvexityAdjuster

//------------------------------------------------------------------------------------------------------

void HL_ConvexityAdjuster::classDefaultInit()
{} // end classDefaultInit



//------------------------------------------------------------------------------------------------------

HLR HL_ConvexityAdjuster::getConvexityAdjustedExpectation(
        const ptime & underlyingFixingTime,
        const HLUND::HL_Underlying & underlying,
        const HL_FwdMeasurePtr & arrivalFwdMeasure,
        const HL_MktDataCollectorPtr & mktDataCollectorPtr) const
{


    HL_PNN(arrivalFwdMeasure);



    const ptime & refTime = underlying.get_refTime();

    HL_SR(underlyingFixingTime>=refTime);

    HL_ExpectationPtr quotingMeasureExpectation = underlying.quotingMeasureExpectation(underlyingFixingTime);

    /*
     * We require this cast since we only know how to change expectations between T_i and T_j fwd measures.
    */
    HL_DYN_SHARED_PTR_CAST(HL_FwdMeasure, quotingMeasure, quotingMeasureExpectation->get_measure());


    HL_SR((*(quotingMeasure->get_riskFreeDiscounting()))==(*(arrivalFwdMeasure->get_riskFreeDiscounting())));


    const HL_IborIndexCodePtr & iborIndexCode
            =quotingMeasure->get_riskFreeDiscounting()->get_riskFreeDiscountingCurveIborIndexCode();

    HL_IborIndexPtr riskFreeDiscountingCurveIborIndex
            =mktDataCollectorPtr->get_mktData<HL_IborIndexPtr>(iborIndexCode);

    HL_SR(riskFreeDiscountingCurveIborIndex->get_refTime()==refTime);

    HL_CovarianceTermStructurePtr covarianceTermStructure=
            HLINTERACTIONS::HL_DerivedCovarianceTermStructure::getDerivedCovarianceTermStructure(
                underlying.hl_ObjCodePtr(),
                iborIndexCode,
                mktDataCollectorPtr
                );


    const date & startPayDate = quotingMeasure->get_payDate();

    const date & arrivalPayDate = arrivalFwdMeasure->get_payDate();


    HLVOL::HL_ImpliedVolModelTypeType riskFreeDisIborImpliedVolModelTypeType =
            riskFreeDiscountingCurveIborIndex->get_impliedVolSurface()->get_impliedVolModelTypeType();

    HLR driftChange=0.;

    date runningAccrualStartDate = startPayDate;


    while(runningAccrualStartDate<arrivalPayDate)
    {

        date runningAccrualEndDate =riskFreeDiscountingCurveIborIndex->accrualEndDate(runningAccrualStartDate);

        runningAccrualEndDate = std::min(runningAccrualEndDate, arrivalPayDate);

        HLR interest = riskFreeDiscountingCurveIborIndex->get_interest(runningAccrualStartDate, runningAccrualEndDate);


        HLR compound = 1 + interest;

        HL_SR(compound>0.); // sanity check


        date runningIborIndexFixingDate = riskFreeDiscountingCurveIborIndex->fixingDate(runningAccrualStartDate);



        /*
         * Notice that the cov has been built with the input "underlying" as first underlying
         * and iborIndexCode as second,
         * so we have to ask for get_interaction with such precise order.
         *
         * firstFwdMaturity = underlyingFixingTime, we mean that we are considering
         * S(underlyingFixingTime) = Fwd(underlyingFixingTime, underlyingFixingTime) as the underlying we are computing the
         * change of the drift (and not its fwd).
        */
        HLR cov = covarianceTermStructure->get_interaction(underlyingFixingTime,
                                                           underlyingFixingTime /*firstFwdMaturity*/,
                                                           ptime(runningIborIndexFixingDate)/*secondFwdMaturityDate*/);

        HLR driftChangeTerm =  cov / compound;

        if(riskFreeDisIborImpliedVolModelTypeType==HLVOL::HL_ImpliedVolModelTypeType_LogNormal)
        {

            driftChangeTerm*=interest;

        }
        else if(riskFreeDisIborImpliedVolModelTypeType==HLVOL::HL_ImpliedVolModelTypeType_Normal)
        {
            HLR tau = riskFreeDiscountingCurveIborIndex->tau(runningAccrualStartDate, runningAccrualEndDate);

            driftChangeTerm*=tau;

        }
        else
        {
            HL_FAIL("invalid riskFreeDisIborImpliedVolModelTypeType=" << getEnumString(riskFreeDisIborImpliedVolModelTypeType));

        }

        driftChange+=driftChangeTerm;

        runningAccrualStartDate =runningAccrualEndDate;


    } // end while

    /*
     * Change sign to driftChange according to drift change math.
    */
    if(arrivalPayDate>=startPayDate)
        driftChange *= -1;


    HLVOL::HL_ImpliedVolModelTypeType underlyingImpliedVolModelTypeType =
            underlying.get_impliedVolSurface()->get_impliedVolModelTypeType();

    HLR convexityAdjustedExpectation = quotingMeasureExpectation->get_value();

    switch(underlyingImpliedVolModelTypeType)
    {
    case HLVOL::HL_ImpliedVolModelTypeType_LogNormal:
    {
        HLR multiplicativeCorrectionFactor = std::exp(driftChange);
        convexityAdjustedExpectation*=multiplicativeCorrectionFactor;
    }
        break;
    case HLVOL::HL_ImpliedVolModelTypeType_ShiftedLogNormal:
        HL_FAIL("case underlyingImpliedVolModelTypeType=HL_ImpliedVolModelTypeType_ShiftedLogNormal not managed yet");
        break;
    case HLVOL::HL_ImpliedVolModelTypeType_Normal:
        convexityAdjustedExpectation+=driftChange;
        break;
    default:
        HL_FAIL("invalid underlyingImpliedVolModelTypeType=" << getEnumString(underlyingImpliedVolModelTypeType));
    } // end switch underlyingImpliedVolModelTypeType



    return convexityAdjustedExpectation;

} // end getConvexityAdjustedExpectation






//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MeasureChange
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_MeasureChange::HL_MeasureChange()
{
    classDefaultInit();

} // end HL_MeasureChange

//------------------------------------------------------------------------------------------------------

HL_MeasureChange::~HL_MeasureChange()
{} // end ~HL_MeasureChange

//------------------------------------------------------------------------------------------------------

void HL_MeasureChange::classDefaultInit()
{} // end classDefaultInit



//------------------------------------------------------------------------------------------------------

HLR HL_MeasureChange::getAdjustedExpectation(
        const ptime & underlyingFixingTime,
        const HLUND::HL_Underlying & underlying,
        const HL_FwdMeasurePtr & arrivalFwdMeasure,
        const HL_MktDataCollectorPtr & mktDataCollectorPtr) const
{

    HL_PNN(arrivalFwdMeasure);


    const date & refDate = underlying.get_refDate();

    const ptime & refTime = underlying.get_refTime();

    HL_SR(underlyingFixingTime>=refTime);

    HL_ExpectationPtr quotingMeasureExpectation = underlying.quotingMeasureExpectation(underlyingFixingTime);

    /*
     * We require this cast since we only know how to change expectations between T_i and T_j fwd measures.
    */
    HL_DYN_SHARED_PTR_CAST(HL_FwdMeasure, quotingMeasure, quotingMeasureExpectation->get_measure());


    /*
    First determine the part of the convexity adjustment due to the change of the payDate only and not
    of the ccy-change (i.e. the quanto adjustment).
    */
    HL_FwdMeasurePtr sameCcyArrivalFwdMeasure(new HLMA::HL_FwdMeasure);

    sameCcyArrivalFwdMeasure->set_riskFreeDiscounting(quotingMeasure->get_riskFreeDiscounting());

    sameCcyArrivalFwdMeasure->set_payDate(arrivalFwdMeasure->get_payDate());


    HLR adjustedExpectation =  HL_ConvexityAdjuster().getConvexityAdjustedExpectation(underlyingFixingTime,
                                                                                      underlying,
                                                                                      sameCcyArrivalFwdMeasure,
                                                                                      mktDataCollectorPtr);


    const HL_CcyCodePtr & arrivalFwdMeasure_ccyCode = arrivalFwdMeasure->get_riskFreeDiscounting()->get_ccyCode();


    const HL_CcyCodePtr & quotingMeasure_ccyCode = quotingMeasure->get_riskFreeDiscounting()->get_ccyCode();


    if(arrivalFwdMeasure_ccyCode!=quotingMeasure_ccyCode)
    {
        /*
         * Noe add the quanto-adjustment starting from the already computed adjustedExpectation.
        */

         HL_FAIL("quanto adjustment-->arrivalFwdMeasure_ccyCode!=quotingMeasure_ccyCode not managed yet");
    }


    return adjustedExpectation;

} // end getAdjustedExpectation




} // end namespace HL_Math
} //end namespace HorizonLib
