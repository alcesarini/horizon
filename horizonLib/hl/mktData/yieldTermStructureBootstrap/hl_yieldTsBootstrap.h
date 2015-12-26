/**
FILE NAME= hl_yieldTsBootstrap.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20141207
*/
#ifndef _hl_yieldTsBootstrap_h_
#define _hl_yieldTsBootstrap_h_

#include <hl/object/hl_object.h>
#include <hl/math/probMeasures/hl_probMeasure.h>
#include <hl/instruments/anagraphics/hl_anagraphics.h>
#include <hl/instruments/hl_baseIns.h>
#include <hl/pricingEngines/hl_pricingEngineFactory.h>
#include <hl/patterns/hl_calibAction.h>
#include <hl/mktData/mktQuotes/hl_mktQuote.h>

namespace HorizonLib
{
namespace HL_MarketData
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IRCurveData
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20150425
\brief Class to collect data to bootstrap an IR curve, but only data relative to the mkt instruments
to be used in order to bootstrap the curve.
*/
class HL_IRCurveData : public virtual HLSER::HL_Serializable, public virtual Descriptable
{

    /**
    -----------------------------------------------------
    Serialization
    */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS;

    template<class Archive>
    void serialize(Archive &ar, const HLS version)
    {

        HL_SER_BASE;

        HL_SER(irCurveCode_);
        HL_SER(riskFreeDiscounting_);
        HL_SER(mktQuotes_);
        HL_SER(discountFactorInterpVariableType_);
        HL_SER(discountFactorInterpType_);
        HL_SER(pricingEngineChoices_);



    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_IRCurveData();

    virtual ~HL_IRCurveData();
    //@}


    /**
    Public class interface
    */
    //@{

    virtual void checkIRCurveData() const;



    HL_CLASS_VAR_ACCESS_METHODS(HL_TermStructureCodePtr, irCurveCode);
    HL_CLASS_VAR_ACCESS_METHODS(HL_RiskFreeDiscountingPtr, riskFreeDiscounting);
    HL_CLASS_VAR_ACCESS_METHODS(std::vector<HL_MktQuotePtr>, mktQuotes);
    HL_CLASS_VAR_ACCESS_METHODS(HLTS::HL_DiscountFactorInterpVariableType, discountFactorInterpVariableType);
    HL_CLASS_VAR_ACCESS_METHODS(HLINTP::HL_InterpolatorType, discountFactorInterpType);
    HL_CLASS_VAR_ACCESS_METHODS(HL_PricingEngineChoicesPtr, pricingEngineChoices);


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
    void descriptionImpl(std::ostream & os) const;
    //@}

protected:


    /**
    Class variables
    */
    //@{


    /**
    This is the code of the curve represented by this class, i.e. the one
    to build based on the data contained by this class.
    */
    HL_TermStructureCodePtr irCurveCode_;


    /**
    This is to specify the risk free discounting under which the interest rate
    curve should be determined.
    */
    HL_RiskFreeDiscountingPtr riskFreeDiscounting_;



    /**
    This is the complete set of data from which the IR curve should be determined.
    */
    std::vector<HL_MktQuotePtr> mktQuotes_;



    HLTS::HL_DiscountFactorInterpVariableType discountFactorInterpVariableType_;

    HLINTP::HL_InterpolatorType discountFactorInterpType_;


    /**
    This is necessary since in order to bootstrap a curve one needs to price instruments
    and hence a choice for the engines.
    */
    HL_PricingEngineChoicesPtr pricingEngineChoices_;
    //@}

}
; // end class HL_IRCurveData


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IRCurveData: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_IRCurveDataPtr BSP<HLMD::HL_IRCurveData>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IRCurveBootstrap
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20150426
\brief Class to implement the bootstrap of an IR curve.

The class will bootstrap the curve having code irCurveData_->irCurveCode_ and
store it into the mktDataCollector_ given in input.
This hence means that the mktDataCollector_ will be changed by this class work.
*/
class HL_IRCurveBootstrap :  public virtual Descriptable
{



public:
    /**
    Constructors & destructors
    */
    //@{

    HL_IRCurveBootstrap();

    virtual ~HL_IRCurveBootstrap();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(HL_IRCurveDataPtr, irCurveData);

    HL_CLASS_VAR_ACCESS_METHODS(HL_MktDataCollectorPtr, mktDataCollector);

    HL_CLASS_VAR_ACCESS_METHODS_O(VEC, effectiveNodeTimes);

    HL_CLASS_VAR_ACCESS_METHODS_O(HL_InterpTermStructurePtr, bootstrappingInterpTermStructure);

    HL_CLASS_VAR_ACCESS_METHODS_O(std::vector<HL_InstrumentPtr>, instruments);


    void performBootstrap();

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


    /**
    This method erases the curve having code irCurveData_->irCurveCode_
    in the mktDataCollector_ (if already present) and substitutes it with
    a newly created one (with the same termstructure irCurveData_->irCurveCode_)
    having just two conventional dates (toady and today+100y).
    This curve will be used to perfom a preliminar pricing of the bootstrapping instruments,
    in order to understand from which dates they really depend on.
    After getting such dates, the actual bootstrapping curve will be built and after
    the calibration (i.e. bootstrapping procedure) it will possibly be wrapped
    intgo a curve with nicer functional properties (e.g. inside a spline).
    This final wrapped curve will be the one inside the mktDataCollector_ after the
    bootstrap will be completed.
    */
    void buildFakeIrCurveInMktDataCollector();


    HL_InterpTermStructurePtr buildInterpTermStructure(
            const HL_TermStructureCodePtr& irCurveCode,
            const VEC & nodeTimes) const;

    void buildInstruments();

    void buildEffectiveIrCurveInMktDataCollector();

    /**
    Such methos prices all instruments_ and, by making use of a suitable HL_MktDataTrackerPtr,
    it collects all the maturity nodes of the ir curve we are about to build.
    This method also checks that instruments_ give rise to acending an maturity structure
    in the sense just explained.
    */
    void collectMaturityNodeInformation(VEC & nodeTimes);


    std::string mktDataTrackerString() const;

    HL_ActionPtr build_calibAction() const;

    HL_CalibActionPtr buildNodeCalibAction(HLS nodeIdx) const;

    HL_RootFinderDataPtr buildRootFinderData(HLS nodeIdx) const;

    //@}


    /**
    Implementations of base class methods
    */
    //@{
    void descriptionImpl(std::ostream & os) const;
    //@}

protected:


    /**
    Class variables
    */
    //@{

    /**
    This is the mkt data of the curve represented by this class, i.e. the one
    to build based on the data contained by this class.
    */
    HL_IRCurveDataPtr irCurveData_;


    /**
    Check out the class comment
     */
    HL_MktDataCollectorPtr mktDataCollector_;

    //@}



    /**
    Service class variables
    */
    //@{

    /**
    The time nodes of the curve to bootstrap.
    */
    VEC effectiveNodeTimes_;
    /**
    The curve that the bootstrapping procedure builds.
    */
    HL_InterpTermStructurePtr bootstrappingInterpTermStructure_;


    /**
    Vector of instruments built in 1-1 correspondence to irCurveData_->anagraphics_
    */
    std::vector<HL_InstrumentPtr> instruments_;


    //@}

}
; // end class HL_IRCurveBootstrap


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IRCurveBootstrap: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_IRCurveBootstrapPtr BSP<HLMD::HL_IRCurveBootstrap>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IRCurveBootstrapModifier
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20150622
 \brief This class is a base class representing an interface to be used in order to modify an object.

 Such class should be always used to modify an object, i.e. for example a model while calibrating.
 Derived classes will specialize the interaction with the object.

 */
class HL_IRCurveBootstrapModifier : public virtual HL_Modifier
{

    /**
     -----------------------------------------------------
     Serialization
     */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS
    ;

    template<class Archive>
    void
    serialize(Archive &ar, const HLS version)
    {
        HL_SERIALIZE_BASE_CLASS(HL_Modifier);;

    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_IRCurveBootstrapModifier();

    virtual ~HL_IRCurveBootstrapModifier();
    //@}

    /**
     Public class interface
     */
    //@{


    HL_CLASS_VAR_ACCESS_METHODS_O(HL_InterpTermStructurePtr, bootstrappingInterpTermStructure);
    HL_CLASS_VAR_ACCESS_METHODS_O(HLS, nodeIdx);

    void set_data(const HL_InterpTermStructurePtr& bootstrappingInterpTermStructure, HLS nodeIdx);

    /**
    This is the gate to modify the object this class exists for.

    It should be (e-b)=1 and *b =discount.
    */
    void modify(const VEC::const_iterator & b, const VEC::const_iterator & e) const;

    /**
    The expected size (i.e. e-b) of the range to be passed to method modify(..).
    */
    HLS vecSize() const
    {
        /*
        i.e. a discount factor value.
        */
        return 1;
    }


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
    void descriptionImpl(std::ostream & os) const;
    //@}

protected:

    /**
     Class variables
     */
    //@{

    HL_InterpTermStructurePtr bootstrappingInterpTermStructure_;

    /**
    The nodeIdx of bootstrappingInterpTermStructure_ to act on.
    */
    HLS nodeIdx_;
    //@}

}
; // end class HL_IRCurveBootstrapModifier

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IRCurveBootstrapModifier: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_IRCurveBootstrapModifierPtr BSP<HLMD::HL_IRCurveBootstrapModifier>







//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IRBootstrapNodeTargetFunction
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20131227
 \brief Specialization of HL_RealFunction_n_1 to be used by classes HL_CalibAction.
 */
class HL_IRBootstrapNodeTargetFunction : public virtual HL_TargetFunction
{

    /**
     -----------------------------------------------------
     Serialization
     */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS
    ;

    template<class Archive>
    void
    serialize(Archive &ar, const HLS version)
    {
        HL_SERIALIZE_BASE_CLASS(HL_TargetFunction);


    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_IRBootstrapNodeTargetFunction();

    virtual ~HL_IRBootstrapNodeTargetFunction();
    //@}

    /**
     Public class interface
     */
    //@{




    HL_TargetFunctionType get_targetFunctionType() const
    {
        return HL_TargetFunctionType_Solve;
    }



    HL_CLASS_VAR_ACCESS_METHODS(HL_InstrumentPtr, instrument);
    HL_CLASS_VAR_ACCESS_METHODS(HLR, instrumentTargetValue);

    HLR operator()(HLR x) const;

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


    HLR computeTargetValue(const VEC::const_iterator & b, const VEC::const_iterator & e) const;

    //@}

    /**
     Implementations of base class methods
     */
    //@{
    void descriptionImpl(std::ostream & os) const;
    //@}

protected:

    /**
     Class variables
     */
    //@{

    HL_InstrumentPtr instrument_;

    HLR instrumentTargetValue_;

     mutable VEC service_x_vec_;
    //@}

}
; // end class HL_IRBootstrapNodeTargetFunction

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IRBootstrapNodeTargetFunction: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_IRBootstrapNodeTargetFunctionPtr BSP<HLMD::HL_IRBootstrapNodeTargetFunction>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_HL_IRCurveBootstrap
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


void HL_TEST_HL_IRCurveBootstrap();





} // end namespace HL_MarketData
} //end namespace HorizonLib


#endif // _hl_yieldTsBootstrap_h_
