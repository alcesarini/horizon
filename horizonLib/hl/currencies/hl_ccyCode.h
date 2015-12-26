/**
FILE NAME= hl_ccyCode.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131210
*/
#ifndef _hl_ccyCode_h_
#define _hl_ccyCode_h_


#include <hl/object/hl_objectCode.h>

namespace HorizonLib
{
namespace HL_Currencies
{




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CcyCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131210
\brief The ccy code
*/

class HL_CcyCode : public virtual HLOBJ::HL_ObjCode
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
        HL_SERIALIZE_BASE_CLASS(HLOBJ::HL_ObjCode);

    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_CcyCode();

    virtual ~HL_CcyCode();
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
; // end class HL_CcyCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CcyCode defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_DEFINE_ALL_ORDERING(HLCCY::HL_CcyCode);

//------------------------------------------------------------------------------------------------------


#define HL_CcyCodePtr BSP<HLCCY::HL_CcyCode>

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_HL_CcyCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CcyCodePtr HL_TEST_get_HL_CcyCode();


} // end namespace HL_Currencies
} //end namespace HorizonLib




#endif // _hl_ccyCode_h_
