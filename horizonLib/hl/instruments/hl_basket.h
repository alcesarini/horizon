/**
FILE NAME= hl_basket.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140523
*/
#ifndef _hl_basket_h_
#define _hl_basket_h_


#include <hl/object/hl_object.h>
#include <hl/underlyings/hl_underlying.h>
#include <hl/instruments/hl_basketWeights.h>


namespace HorizonLib
{
namespace HL_Instruments
{





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_BasketCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140521
\brief The code of a cashflow
*/

class HL_BasketCode : public virtual HLOBJ::HL_FinObjCode
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

        HL_SERIALIZE_BASE_CLASS(HLOBJ::HL_FinObjCode);

    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_BasketCode();

    virtual ~HL_BasketCode();
    //@}


    /**
    Public class interface
    */
    //@{

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
    HLSTRING objTypeImpl() const;
    //@}

protected:


    /**
    Class variables
    */
    //@{

    //@}

}
; // end class HL_BasketCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_BasketCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_BasketCodePtr BSP<HLINS::HL_BasketCode>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Basket
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140523
\brief To hold a set of underlying codes.
*/
class HL_Basket : public virtual HLOBJ::HL_FinObj
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

        HL_SERIALIZE_BASE_CLASS(HLOBJ::HL_FinObj);

        HL_SER(basketCodePtr_);
        HL_SER(underlyingCodes_);
        HL_SER(underlyingHistoryTags_);



    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_Basket();

    virtual ~HL_Basket();
    //@}


    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(std::vector<HL_UnderlyingCodePtr>, underlyingCodes);

    HL_CLASS_VAR_ACCESS_METHODS(std::vector<HLSTRING>, underlyingHistoryTags);



    HL_Order getOrder(const HL_Basket & hl_Basket) const;

    void checkBasket() const;


    HLS nbComponents() const
    {
        return underlyingCodes_.size();
    }

    const HL_UnderlyingCodePtr & get_underlyingCode(HLS undIdx) const
    {
        HL_SR(undIdx<underlyingCodes_.size());
        return underlyingCodes_[undIdx];
    }

    const HLSTRING & get_underlyingHistoryTag(HLS undIdx) const
    {
        HL_SR(undIdx<underlyingHistoryTags_.size());
        return underlyingHistoryTags_[undIdx];
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


    HL_BasketCodePtr basketCodePtr_;

    /**
    Set of underlyings (we keep just the
    underlying codes here, since the codes are anagraphics....).
    */
    std::vector<HL_UnderlyingCodePtr> underlyingCodes_;



    /**
    We assume that each underlying of the task could make fixing on a different tag.
    */
    std::vector<HLSTRING> underlyingHistoryTags_;

    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_Basket


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Basket: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_DEFINE_ALL_ORDERING(HL_Basket);

//------------------------------------------------------------------------------------------------------


#define HL_BasketPtr BSP<HLINS::HL_Basket>








} // end namespace HL_Instruments
} //end namespace HorizonLib


#endif // _hl_basket_h_
