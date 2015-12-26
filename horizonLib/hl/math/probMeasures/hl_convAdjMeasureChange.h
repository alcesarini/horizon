/**
FILE NAME=hl_convAdjMeasureChange.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140726
*/
#ifndef _hl_convAdjMeasureChange_h_
#define _hl_convAdjMeasureChange_h_


#include <hl/math/probMeasures/hl_probMeasure.h>
#include <hl/mktData/correlations/hl_correlationTermStructure.h>




namespace HorizonLib
{
namespace HL_Math
{







//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_ConvexityAdjuster
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140802
\brief To compute the drift adjustment due to change of fwd-measures in the same ccy.

\doc_tag 20140823-CONVADJ

Given:

- a fixing date underlyingFixingDate=t>=refDate, where refDate=0

- an input underlying S (say "underlying" from now on)

- an arrivalFwdMeasure that has to be in the same ccy and that has to have an equivalent instance
of the class HL_FwdMeasure::riskFreeDiscounting_ w.r.t. the quoting measure of the input "underlying" S.

- the covariance term structure between $S$ and the ibor index
of HL_FwdMeasure::riskFreeDiscounting_->get_riskFreeDiscountingCurveIborIndexCode(),

the class is able to return, through method getConvexityAdjustedExpectation(..):

E_0^(arrivalFwdMeasure)[S(t)]

starting from

E_0^(quotingMeasure)[S(t)] = underlying->quotingMeasureExpectation(t)

In other words, this class computes the convexity adjusted drift expectation.

*/

class HL_ConvexityAdjuster
{

public:


    /**
    Constructors & destructors
    */
    //@{

    HL_ConvexityAdjuster();

    virtual ~HL_ConvexityAdjuster();
    //@}


    /**
    Public class interface
    */
    //@{



    HLR getConvexityAdjustedExpectation(const date & underlyingFixingDate,
                                        const HLUND::HL_Underlying & underlying,
                                        const HL_FwdMeasurePtr & arrivalFwdMeasure,
                                        const HL_MktDataCollectorPtr & mktDataCollectorPtr) const
    {

        return getConvexityAdjustedExpectation(ptime(underlyingFixingDate),
                                               underlying,
                                               arrivalFwdMeasure,
                                               mktDataCollectorPtr);

    }

    /**
     * underlying is S as introduced in the class comment.
     *
    */
    HLR getConvexityAdjustedExpectation(const ptime & underlyingFixingTime,
                                        const HLUND::HL_Underlying & underlying,
                                        const HL_FwdMeasurePtr & arrivalFwdMeasure,
                                        const HL_MktDataCollectorPtr & mktDataCollectorPtr) const;

    //@}


protected:

    /**
    Additional implementations
    */
    //@{
    /**
    Default initialization of the class vars.
    */
    void classDefaultInit();
    //@}


    /**
    Implementations of base class methods
    */
    //@{
    //@}


protected:


    /**
    Class variables
    */
    //@{


    //@}

}
; // end class HL_ConvexityAdjuster






//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_ConvexityAdjuster: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_ConvexityAdjusterPtr BSP<HLMA::HL_ConvexityAdjuster>






//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MeasureChange
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140902
\brief To compute the drift adjustment due to change of fwd-measures possibly in different ccys.

\doc_tag 20140823-CONVADJ
\doc_tag A. Cesarini 20140902-CCYCONVADJ

Given:

- a fixing date underlyingFixingDate=t>=refDate, where refDate=0

- an input underlying S (say "underlying" from now on)

- an arrivalFwdMeasure possibly in a different ccy w.r.t. the quoting measure of the input "underlying" S.

- the covariance term structure between $S$ and the ibor index
of S->get_impliedVolSurface()->riskFreeDiscounting_->get_riskFreeDiscountingCurveIborIndexCode(),

- the covariance between $S$ and the fwd-exchange rate between the $S$-ccy and the ccy of arrivalFwdMeasure

the class is able to return, through method getAdjustedExpectation(..):

E_0^(arrivalFwdMeasure)[S(t)]

starting from

E_0^(quotingMeasure)[S(t)] = underlying->quotingMeasureExpectation(t)


*/

class HL_MeasureChange
{

public:


    /**
    Constructors & destructors
    */
    //@{

    HL_MeasureChange();

    virtual ~HL_MeasureChange();
    //@}


    /**
    Public class interface
    */
    //@{



    HLR getAdjustedExpectation(const date & underlyingFixingDate,
                               const HLUND::HL_Underlying & underlying,
                               const HL_FwdMeasurePtr & arrivalFwdMeasure,
                               const HL_MktDataCollectorPtr & mktDataCollectorPtr) const
    {

        return getAdjustedExpectation(ptime(underlyingFixingDate),
                                      underlying,
                                      arrivalFwdMeasure,
                                      mktDataCollectorPtr);

    }

    /**
     * underlying is S as introduced in the class comment.
     *
    */
    HLR getAdjustedExpectation(const ptime & underlyingFixingTime,
                               const HLUND::HL_Underlying & underlying,
                               const HL_FwdMeasurePtr & arrivalFwdMeasure,
                               const HL_MktDataCollectorPtr & mktDataCollectorPtr) const;

    //@}


protected:

    /**
    Additional implementations
    */
    //@{
    /**
    Default initialization of the class vars.
    */
    void classDefaultInit();
    //@}


    /**
    Implementations of base class methods
    */
    //@{
    //@}


protected:


    /**
    Class variables
    */
    //@{


    //@}

}
; // end class HL_MeasureChange


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MeasureChange: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_MeasureChangePtr BSP<HLMA::HL_MeasureChange>




} // end namespace HL_Math
} //end namespace HorizonLib


#endif // _hl_convAdjMeasureChange_h_
