/**
FILE NAME=hl_probMeasure.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140726
*/
#ifndef _hl_probMeasure_h_
#define _hl_probMeasure_h_

#include <hl/mktData/termStructures/hl_termStructure.h>






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
// class HL_IborIndexCode (fwd declaration)
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


class HL_IborIndexCode;


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IborIndexCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_IborIndexCodePtr BSP<HLIR::HL_IborIndexCode>


} // end namespace HL_InterestRates
} // end namespace HL_Underlyings
} // end namespace HL_MarketData
} //end namespace HorizonLib


namespace HorizonLib
{
namespace HL_Math
{




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RiskFreeDiscounting
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140726
\brief This class specifies a system of data to discount cashflows without credit risk.

The idea is that one could have in principle more ways to risk-free discount cashflows, i.e.
this is a sort of pricing data detail for a pricing model.
In simple setups, one will have just one instance of this class.
*/

class HL_RiskFreeDiscounting : public virtual HLSER::HL_Serializable, public virtual Descriptable
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
        HL_SER(riskFreeDiscountingTermStructureCode_);
        HL_SER(riskFreeDiscountingCurveIborIndexCode_);

    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_RiskFreeDiscounting();

    virtual ~HL_RiskFreeDiscounting();
    //@}


    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(HL_TermStructureCodePtr, riskFreeDiscountingTermStructureCode);

    HL_CLASS_VAR_ACCESS_METHODS(HL_IborIndexCodePtr, riskFreeDiscountingCurveIborIndexCode);


    const HL_CcyCodePtr & get_ccyCode() const
    {

        return riskFreeDiscountingTermStructureCode_->get_ccyCode();
    }

    HL_Order getOrder(const HL_RiskFreeDiscounting & riskFreeDiscounting) const;

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
       This is the code of the TS that is supposed to be used in order to discount cashflows in
       a risk free way.
    */
    HL_TermStructureCodePtr riskFreeDiscountingTermStructureCode_;



    /**
     * This ibor represents the dynamics of the interest rate curve corresponding to
     * riskFreeDiscountingTermStructureCode_ and, as such, could be used in order to compute, e.g.,
     * convexity adjustments.
    */
    HL_IborIndexCodePtr riskFreeDiscountingCurveIborIndexCode_;


    //@}

}
; // end class HL_RiskFreeDiscounting


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RiskFreeDiscounting: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_DEFINE_ALL_ORDERING(HL_RiskFreeDiscounting);

//------------------------------------------------------------------------------------------------------


#define HL_RiskFreeDiscountingPtr BSP<HLMA::HL_RiskFreeDiscounting>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_MeasureType
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
\brief The HL library period units.
*/
enum HL_MeasureType
{
    HL_MeasureType_InvalidMin=0,
    HL_MeasureType_FwdMeasure,
    HL_MeasureType_SwapMeasure,
    HL_MeasureType_InvalidMax
}; // end enum HL_MeasureType

//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
        HL_MeasureType,
        "HL_MeasureType_InvalidMin",
        "HL_MeasureType_FwdMeasure",
        "HL_MeasureType_SwapMeasure",
        "HL_MeasureType_InvalidMax"
        );


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Measure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_MeasurePtr BSP<HLMA::HL_Measure>

//------------------------------------------------------------------------------------------------------


/**
\author A. Cesarini
\date 20131226
\brief Base class to represent pricing measures.
*/

class HL_Measure : public virtual HLSER::HL_Serializable, public virtual Descriptable
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
        HL_SER(riskFreeDiscounting_);


    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_Measure();

    virtual ~HL_Measure();
    //@}


    /**
    Public class interface
    */
    //@{


    HL_CLASS_VAR_ACCESS_METHODS(HL_RiskFreeDiscountingPtr, riskFreeDiscounting);


    virtual HL_MeasureType measureType() const=0;


    virtual bool operator==(const HL_MeasurePtr & extMeasure) const;

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


    HL_RiskFreeDiscountingPtr riskFreeDiscounting_;

    //@}

}
; // end class HL_Measure


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Measure: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FwdMeasure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131226
\brief Class used to specify the fwd measure to compute expectations.
*/

class HL_FwdMeasure : public virtual HL_Measure
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

        HL_SERIALIZE_BASE_CLASS(HL_Measure);

        HL_SER(payDate_);
    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_FwdMeasure();

    virtual ~HL_FwdMeasure();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(date/*ClassVariableType*/, payDate/*classVariableName_no_underscore*/);



    virtual bool operator==(const HL_MeasurePtr & extMeasure) const;

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


    HL_MeasureType measureType() const
    {

        return HL_MeasureType_FwdMeasure;
    }

    //@}


protected:


    /**
    Class variables
    */
    //@{

    /**
    The numeraire associated to HL_FwdMeasure is the zero-coupon bond
    deliverying 1 unit of hl_CcyCode_-currency at date payDate_.
    */
    //@{
    date payDate_;



    //@}
    //@}

}
; // end class HL_FwdMeasure

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FwdMeasure: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_FwdMeasurePtr BSP<HLMA::HL_FwdMeasure>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Expectation
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140825
\brief This class stores an expecation of some quantity, also specifying the measure under which it has
been computed, that is a mandatory info to know in order know the meaning of the daqta itself.
*/
class HL_Expectation : public virtual HLSER::HL_Serializable, public virtual Descriptable
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
        HL_SER(value_);
        HL_SER(measure_);

    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_Expectation();

    virtual ~HL_Expectation();
    //@}


    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(HLR, value);

    HL_CLASS_VAR_ACCESS_METHODS(HL_MeasurePtr, measure);



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


    HLR value_;

    /**
     * See class comment.
    */
    HL_MeasurePtr measure_;

    //@}

}
; // end class HL_Expectation


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Expectation: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_ExpectationPtr BSP<HLMA::HL_Expectation>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_ccyCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CcyCodePtr HL_TEST_get_ccyCode();


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_irCurveCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_TermStructureCodePtr HL_TEST_get_irCurveCode(const std::string & curveName);



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_HL_IborIndexCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//HL_IborIndexCodePtr HL_TEST_get_HL_IborIndexCode(const std::string & iborIndexName);



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_riskFreeDiscounting
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_RiskFreeDiscountingPtr HL_TEST_get_riskFreeDiscounting(
        const HL_TermStructureCodePtr & riskFreeDiscountingTermStructureCode,
        const HL_IborIndexCodePtr & riskFreeDiscountingCurveIborIndexCode);




} // end namespace HL_Math
} //end namespace HorizonLib


#endif // _hl_probMeasure_h_
