/**
FILE NAME= hl_termStructure.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131213
*/
#ifndef _hl_termStructure_h_
#define _hl_termStructure_h_

#include <hl/mktData/hl_mktData.h>
#include <hl/math/interpolation/hl_interpolator.h>


namespace HorizonLib
{
namespace HL_MarketData
{
namespace HL_TermStructures
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TermStructureCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131213
\brief The term structure code
*/

class HL_TermStructureCode : public virtual HL_MktDataCode
{
public:


    /**
    Constructors & destructors
    */
    //@{

    HL_TermStructureCode();

    virtual ~HL_TermStructureCode();
    //@}


    /**
    Public class interface
    */
    //@{

    //@}


protected:

    /**
    Implementations of base class methods
    */
    //@{
    HLSTRING objTypeImpl() const;
    //@}


    /**
    Additional implementations
    */
    //@{
    /**
    Default initialization of the class vars.
    */
    void classDefaultInit();
    //@}

protected:


    /**
    Class variables
    */
    //@{

    //@}

}
; // end class HL_TermStructureCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TermStructureCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_TermStructureCodePtr BSP<HLTS::HL_TermStructureCode>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TermStructure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131213
\brief Base class for all term structures.
*/
class HL_TermStructure : public virtual HL_MktData
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

        HL_SERIALIZE_BASE_CLASS(HL_MktData);

    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_TermStructure();

    virtual ~HL_TermStructure();
    //@}


    /**
    Public class interface
    */
    //@{




    /**
    Discount factor at t
    */
    HLR df(const ptime &t) const;

    HLR df(const date &d) const
    {
        return df(ptime(d));
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


    /**
     * The method that should be implemented by derived classes.
     * */
    virtual HLR dfImpl(HLR t) const;


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

    //@}

}
; // end class HL_TermStructure


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TermStructure: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_TermStructurePtr BSP<HLTS::HL_TermStructure>

//------------------------------------------------------------------------------------------------------

HL_TermStructurePtr get_TermStructurePtr(const HL_MktDataCollectorPtr & mktDataCollectorPtr, const HL_ObjCodePtr & objCodePtr);



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_DiscountFactorInterpVariableType
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
\brief Specifies how to interpolate discount factor. Let t_1<t_2 be 2 times where one knows
the values of the discount factors (D_1 and D_2 respectively). The question is then hot to interpolate the discount for t_1<t<t_2.
Notice that this enum does not say what interpolator one should use, but rather what to interpolate.
The comments belowe should clarify further...
*/
enum HL_DiscountFactorInterpVariableType
{
    HL_DiscountFactorInterpVariableType_InvalidMin=0,
    /**
     * Interpolate directly on D_1 and D_2
     * */
    HL_DiscountFactorInterpVariableType_Discount,
    /**
     * Interpolate directly on ln(D_1) and ln(D_2)
     * */
    HL_DiscountFactorInterpVariableType_RateTime,
    /**
     * Interpolate directly on ln(D_1)/t_1 and ln(D_2)/t_2
     * */
    HL_DiscountFactorInterpVariableType_Rate,
    HL_DiscountFactorInterpVariableType_InvalidMax
}; // end enum HL_DiscountFactorInterpVariableType

//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
    HL_DiscountFactorInterpVariableType,
    "HL_DiscountFactorInterpVariableType_InvalidMin",
    "HL_DiscountFactorInterpVariableType_Discount",
    "HL_DiscountFactorInterpVariableType_RateTime",
    "HL_DiscountFactorInterpVariableType_Rate",
    "HL_DiscountFactorInterpVariableType_InvalidMax"
);


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterpTermStructure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140305
\brief Base class for all term structures that interpolate the discount between a set of bullet points.
*/
class HL_InterpTermStructure : public virtual HL_TermStructure
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

        HL_SERIALIZE_BASE_CLASS(HL_TermStructure);

    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_InterpTermStructure();

    virtual ~HL_InterpTermStructure();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(HL_DiscountFactorInterpVariableType, discountFactorInterpVariableType);
    HL_CLASS_VAR_ACCESS_METHODS(HLINTP::HL_InterpolatorType, discountFactorInterpype);

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

    /**
     * The method that should be implemented by derived classes.
     * */
    virtual HLR dfImpl(HLR t) const;

    //@}

protected:


    /**
    Class variables
    */
    //@{

    /**
     * See comment to HL_DiscountFactorInterpVariableType
     * */
    HL_DiscountFactorInterpVariableType discountFactorInterpVariableType_;

    /**
     * Together with discountFactorInterpVariableType_ completely specifies how to interpolate discount factors
     * in between input nodes.
     * */
    HLINTP::HL_InterpolatorType discountFactorInterpype_;

    /**
     * Holds the points to be interpolated
     * */
    HL_InterpolatorPtr interpolatorPtr_;

    //@}

}
; // end class HL_InterpTermStructure


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterpTermStructure: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_InterpTermStructurePtr BSP<HLTS::HL_InterpTermStructure>




} // end namespace HL_TermStructures
} // end namespace HL_MarketData
} //end namespace HorizonLib


#endif // _hl_termStructure_h_
