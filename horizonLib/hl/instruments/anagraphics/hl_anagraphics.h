/**
FILE NAME= hl_anagraphics.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140614
*/
#ifndef _hl_anagraphics_h_
#define _hl_anagraphics_h_


#include <hl/basicFiles/hl_workingIncludes.h>


namespace HorizonLib
{
namespace HL_Instruments
{
namespace HL_Anagraphics
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_AnagraphicsType
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
\brief The HL library period units.
*/
enum HL_AnagraphicsType
{
    HL_AnagraphicsType_InvalidMin=0,
    HL_AnagraphicsType_HL_ScheduleAnagraphics,
    HL_AnagraphicsType_FixedLegAnagraphics,
    HL_AnagraphicsType_UnderlyingDeliveryLegAnagraphics,
    HL_AnagraphicsType_SwapAnagraphics,
    HL_AnagraphicsType_InvalidMax
}; // end enum HL_AnagraphicsType

//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
        HL_AnagraphicsType,
        "HL_AnagraphicsType_InvalidMin",
        "HL_AnagraphicsType_HL_ScheduleAnagraphics",
        "HL_AnagraphicsType_FixedLegAnagraphics",
        "HL_AnagraphicsType_UnderlyingDeliveryLegAnagraphics",
        "HL_AnagraphicsType_SwapAnagraphics",
        "HL_AnagraphicsType_InvalidMax"
        );




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Anagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140614
\brief Base class to contain some anagraphics.
*/
class HL_Anagraphics : public virtual HLSER::HL_Serializable, public virtual Descriptable
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




    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_Anagraphics();

    virtual ~HL_Anagraphics();
    //@}


    /**
    Public class interface
    */
    //@{




    /**
    Unique tag for the mkt quote type.
    */
    virtual HL_AnagraphicsType anagraphicsType() const=0;

    HLSTRING anagraphicsTypeString() const
    {
        return getEnumString(anagraphicsType());
    }


    virtual void checkAnagraphics() const{}

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

    //@}

}
; // end class HL_Anagraphics


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Anagraphics: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_AnagraphicsPtr BSP<HLAN::HL_Anagraphics>





} // end namespace HL_Anagraphics
} // end namespace HL_Instruments
} //end namespace HorizonLib


#endif // _hl_anagraphics_h_
