/**
FILE NAME= hl_objectCode.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131208
*/
#ifndef _hl_objectCode_h_
#define _hl_objectCode_h_


#include <hl/basicFiles/hl_workingIncludes.h>


namespace HorizonLib
{
namespace HL_Object
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_ObjCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131126
\brief Base class to assign a code to each instance of the class HL_Object.
FINANCIAL_EXAMPLE: The code is for ex. something like "stoxx50e", or "eur3mcurve"
*/
class HL_ObjCode : public virtual HLSER::HL_Serializable, public virtual Descriptable
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
        HL_SER(nCode_);
        HL_SER(sCode_);

    }
    //@} Serialization -----------------------------------

public:


    /**
    Constructors & destructors
    */
    //@{

    HL_ObjCode();

    virtual ~HL_ObjCode();
    //@}


    /**
    Public class interface
    */
    //@{
    HLSTRING objType() const;



    /**
    Should compare *this to hl_ObjCode and return:
    HL_Order_1_Less_2 if (*this) < hl_ObjCode
    HL_Order_1_Eq_2 if (*this) == hl_ObjCode
    HL_Order_1_Greater_2 if (*this) > hl_ObjCode

    Notice that there is no need to reimplement this function in derived object codes (so it is not virtual),
    since the fact that 2 codes of different types are indeed considered to be different
    is already taken into account by the implementations in HL_DEFINE_ALL_ORDERING.
    Hence, given this consideration, it is sufficient to compare only the numeric code (nCode_)
    and the char code (sCode_), to decide if 2 codes (of the same type) are equal or not (and more
    in particular whci comes first).
    */
    HL_Order getOrder(const HL_ObjCode & hl_ObjCode) const;

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



    virtual HLSTRING objTypeImpl() const=0;
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
    HLL nCode_;
    HLSTRING sCode_;
    //@}

}
; // end class HL_ObjCode

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_ObjCode:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_DEFINE_ALL_ORDERING(HL_ObjCode);

//------------------------------------------------------------------------------------------------------

#define HL_ObjCodePtr BSP<HLOBJ::HL_ObjCode>



} // end namespace HL_Object
} //end namespace HorizonLib


#endif // _hl_objectCode_h_
