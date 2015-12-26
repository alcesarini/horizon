/**
FILE NAME= hl_basketComposition.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140523
*/
#ifndef _hl_basketComposition_h_
#define _hl_basketComposition_h_


#include <hl/basicFiles/hl_workingIncludes.h>



namespace HorizonLib
{
namespace HL_Instruments
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_BasketRuleType
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
\brief Establish how to compute a basket.
*/
enum HL_BasketRuleType
{
    HL_BasketRuleType_InvalidMin=0,
    /**
    \sum w_i * S_i, so S's and w's must be in the same number
    */
    HL_BasketRuleType_PlainSum,
    /**
    \sum w_i * S_j(i) where the sum is extended to the worst performing S's.
    In this case the w's can be less than the S's
    */
    HL_BasketRuleType_SumWorsts,
    /**
    Similar to HL_BasketRuleType_SumWorsts but the sum is extended to the best performing S's.
    */
    HL_BasketRuleType_SumBests,
    HL_BasketRuleType_InvalidMax
}; // end enum HL_BasketRuleType

//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
        HL_BasketRuleType,
        "HL_BasketRuleType_InvalidMin",
        "HL_BasketRuleType_PlainSum",
        "HL_BasketRuleType_SumWorsts",
        "HL_BasketRuleType_SumBests",
        "HL_BasketRuleType_InvalidMax"
        );




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_BasketCompositionType
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
\brief Establish type of the basket.
*/
enum HL_BasketCompositionType
{
    HL_BasketCompositionType_InvalidMin=0,
    HL_BasketCompositionType_FwdStart,
    HL_BasketCompositionType_Quant,
    HL_BasketCompositionType_InvalidMax
}; // end enum HL_BasketCompositionType

//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
        HL_BasketCompositionType,
        "HL_BasketCompositionType_InvalidMin",
        "HL_BasketCompositionType_FwdStart",
        "HL_BasketCompositionType_Quant",
        "HL_BasketCompositionType_InvalidMax"
        );


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_BasketComposition
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140523
\brief To define how to compute a basket fixing from a set of basket underlyings.
*/
class HL_BasketComposition :  public virtual HLSER::HL_Serializable, public virtual Descriptable
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
        HL_SER(nbComponents_);
        HL_SER(issueTime_);
        HL_SER(basketRuleType_);


    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_BasketComposition();

    virtual ~HL_BasketComposition();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS_O(HLS, nbComponents);

    HL_CLASS_VAR_ACCESS_METHODS(ptime, issueTime);

    HL_CLASS_VAR_ACCESS_METHODS(HL_BasketRuleType, basketRuleType);



    virtual void checkBasketComposition() const;

    virtual HL_BasketCompositionType get_basketCompositionType() const=0;
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


    HLS nbComponents_;
    /**
      The issue date must be set
    */
    ptime issueTime_;

    HL_BasketRuleType basketRuleType_;

    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_BasketComposition


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_BasketComposition: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



#define HL_BasketCompositionPtr BSP<HLINS::HL_BasketComposition>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FwdStartBasketComposition
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141106
\brief To be used when refTime<issueTime_ or at least until one cannot compute the exact asset quantities,
i.e. when one can transform HL_FwdStartBasketComposition into HL_QuantBasketComposition.

*/
class HL_FwdStartBasketComposition :  public virtual HL_BasketComposition
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


        HL_SERIALIZE_BASE_CLASS(HL_BasketComposition);
        HL_SER(issueTimeWeights_);


    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_FwdStartBasketComposition();

    virtual ~HL_FwdStartBasketComposition();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS_O(VEC, issueTimeWeights);


    void set_issueTimeWeights(const VEC & issueTimeWeights);

    virtual void checkBasketComposition() const;



    HL_BasketCompositionType get_basketCompositionType() const
    {

        return HL_BasketCompositionType_FwdStart;
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


    /** Should add uo to 1 */
    VEC issueTimeWeights_;


    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_FwdStartBasketComposition


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FwdStartBasketComposition: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



#define HL_FwdStartBasketCompositionPtr BSP<HLINS::HL_FwdStartBasketComposition>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_QuantBasketComposition
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141106
\brief To be used when refTime>=issueTime_ or at least when one can compute the exact asset quantities,
i.e. when one can transform HL_FwdStartBasketComposition into HL_QuantBasketComposition, or maybe
when one does not even pass through a HL_FwdStartBasketComposition, but one directly has from
the contract a HL_QuantBasketComposition (i.e. one has a basket express directly through quantities).
*/
class HL_QuantBasketComposition :  public virtual HL_BasketComposition
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


        HL_SERIALIZE_BASE_CLASS(HL_BasketComposition);
        HL_SER(issueTimeQuantities_);



    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_QuantBasketComposition();

    virtual ~HL_QuantBasketComposition();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS_O(VEC, issueTimeQuantities);


    void set_issueTimeQuantities(const VEC & issueTimeQuantities);

    virtual void checkBasketComposition() const;


    HL_BasketCompositionType get_basketCompositionType() const
    {

        return HL_BasketCompositionType_Quant;
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


    /** Should add up to 1 */
    VEC issueTimeQuantities_;


    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_QuantBasketComposition


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_QuantBasketComposition: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



#define HL_QuantBasketCompositionPtr BSP<HLINS::HL_QuantBasketComposition>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// computeBasketPerformance
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141224
\brief
*/
template<class CIT>
inline HLR computeBasketPerformancePlainSum(
        CIT fixingsBegin,
        CIT fixingsEnd,
        CIT quantitiesBegin
        )
{

    HLR res=0;

    while(fixingsBegin!=fixingsEnd)
    {
        res += (fixingsBegin++)*(quantitiesBegin++);

    } // end while fixingsBegin

    return res;


} // end computeBasketPerformance



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// computeBasketPerformance
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141224
\brief Notice that quantities can be shorter than the nb of
fixings available starting from fixingsBegin. This is especially the case when one wants to
sum for ex. the first 3 best or worst performances.
*/
template<class T>
inline HLR computeBasketPerformance(
        HL_BasketRuleType basketRuleType,
        T & fixings,
        const T & quantities
        )
{

    HLR res;

    switch(basketRuleType)
    {
    case HL_BasketRuleType_PlainSum:
        res = std::inner_product(quantities.begin() /*first1*/,
                                 quantities.end() /*last1*/,
                                 fixings.begin() /*first2*/,
                                 0./*init*/,
                                 std::plus<HLR>() /*binary_op1*/,
                                 std::multiplies<HLR>() /*binary_op2*/
                                 );
        break;
    case HL_BasketRuleType_SumWorsts:
        std::sort(fixings.begin(), fixings.end());
        res = std::inner_product(quantities.begin() /*first1*/,
                                 quantities.end() /*last1*/,
                                 fixings.begin()  /*first2*/,
                                 0./*init*/,
                                 std::plus<HLR>() /*binary_op1*/,
                                 std::multiplies<HLR>() /*binary_op2*/
                                 );
        break;
    case HL_BasketRuleType_SumBests:
        std::sort(fixings.begin(), fixings.end());
        res = std::inner_product(quantities.begin() /*first1*/,
                                 quantities.end() /*last1*/,
                                 fixings.rbegin()  /*first2*/,
                                 0./*init*/,
                                 std::plus<HLR>() /*binary_op1*/,
                                 std::multiplies<HLR>() /*binary_op2*/
                                 );
        break;
    default:
        HL_FAIL("invalid basketRuleType " << getEnumString(basketRuleType));
    }




    return res;

} // end computeBasketPerformance


} // end namespace HL_Instruments
} //end namespace HorizonLib


#endif // _hl_basketComposition_h_
