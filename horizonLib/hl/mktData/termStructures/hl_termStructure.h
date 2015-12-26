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
    /**HL_IRCurveBootstrap
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


    void set_HL_ObjCodePtr(const HL_ObjCodePtr & hl_ObjCodePtr);



    /**
    Discount factor at t
    */
    HLR df(const ptime &t) const;

    HLR df(const date &d) const
    {
        return df(ptime(d));
    }

    /**
     * The method that should be implemented by derived classes.
     * */
    virtual HLR df(HLR t) const;

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
    Transform a ptime into a yf from refDate
    */
    HLR get_yf(const ptime &t) const;




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

    HL_TermStructureCodePtr termStructureCode_;

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
the values of the discount factors (D_1 and D_2 respectively).
The question is then how to interpolate the discount for t_1<t<t_2.
Notice that this enum does not say what interpolator one should use, but rather what to interpolate.
The comments below should clarify further...
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
        HL_SER(discountFactorInterpVariableType_);
        HL_SER(discountFactorInterpType_);
        HL_SER(interpolatorPtr_);
        //HL_SER(nodeDates_);
        HL_SER(nodeTimes_);
        HL_SER(nbNodes_);






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
    HL_CLASS_VAR_ACCESS_METHODS(HLINTP::HL_InterpolatorType, discountFactorInterpType);
    //HL_CLASS_VAR_ACCESS_METHODS_O(std::vector<date>, nodeDates);
    HL_CLASS_VAR_ACCESS_METHODS_O(VEC, nodeTimes);
    HL_CLASS_VAR_ACCESS_METHODS_O(HLS, nbNodes);

    /**
    This method specifies the node dates of the interpolation.
    */
    void setNodeDates(const std::vector<date> & nodeDates);

    void setNodeTimes(const VEC & nodeTimes);

    /**
    nodeDiscount should be a discount factor.
    */
    void setNodeDiscount(HLS nodeIdx, HLR nodeDiscount);



    /**
    To be used to get from a node discount the actual variable the class interpolates on according to
    discountFactorInterpVariableType_
    */
    HLR getInterpolationVariable(HLR nodeDiscount, HLS nodeIdx);


    /**
     * The method that should be implemented by derived classes.
     * */
    virtual HLR df(HLR t) const;

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
    nodeValue should be the variable that the class interpolates (for ex.
    the discount or the log-discount or the log-discount over time etc..
    */
    void setNodeValue(HLS nodeIdx, HLR nodeValue);

    /**
    Retuns the node value, for ex.
    the discount or the log-discount or the log-discount over time etc..,
    according to discountFactorInterpVariableType_.
    */
    HLR getNodeValue(HLS nodeIdx) const;

    //@}


    /**
    Implementations of base class methods
    */
    //@{
    void descriptionImpl(std::ostream & os) const;





    HLR getDiscountFactorFromInterpolationVariable(HLR interpVariable, HLR t) const;

    void setInterpolator();


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
    HLINTP::HL_InterpolatorType discountFactorInterpType_;

    /**
     * Holds the points to be interpolated
     * */
    HL_InterpolatorPtr interpolatorPtr_;

    /**
    The dates with which the interpolatorPtr_ is built.
    */
    //std::vector<date> nodeDates_;
    VEC nodeTimes_;
    HLS nbNodes_;

    mutable VEC tVec_;
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
