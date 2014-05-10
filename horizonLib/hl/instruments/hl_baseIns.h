/**
FILE NAME= baseIns.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131109
*/
#ifndef _hl_baseIns_h_
#define _hl_baseIns_h_


#include <hl/object/hl_object.h>




namespace HorizonLib
{
namespace HL_Instruments
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InstrumentCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131210
\brief The ins code
*/

class HL_InstrumentCode : public virtual HLOBJ::HL_FinObjCode
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

    HL_InstrumentCode();

    virtual ~HL_InstrumentCode();
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
; // end class HL_InstrumentCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InstrumentCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_InstrumentCodePtr BSP<HLINS::HL_InstrumentCode>

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Instrument
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131110
\brief Basic financial instrument.
*/
class HL_Instrument : public virtual HLOBJ::HL_FinObj
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


    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_Instrument();

    virtual ~HL_Instrument();
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
    void descriptionImpl(std::ostream & os) const;
    //@}

protected:


    /**
    Class variables
    */
    //@{

    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_Instrument


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InstrumentCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_InstrumentPtr BSP<HLINS::HL_Instrument>


} // end namespace HL_Instruments
} //end namespace HorizonLib


#endif // _hl_baseIns_h_
