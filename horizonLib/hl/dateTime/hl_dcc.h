/**
FILE NAME= hl_dcc.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131223
*/
#ifndef _hl_dcc_h_
#define _hl_dcc_h_

#include <hl/basicFiles/hl_workingIncludes.h>

namespace HorizonLib
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_DccType
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
\brief The HL library period units.
*/
enum HL_DccType
{
    HL_DccType_InvalidMin=0,
    HL_DccType_Act360,
    HL_DccType_Act365,
    HL_DccType_InvalidMax
}; // end enum HL_DccType

//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
    HL_DccType,
    "HL_DccType_InvalidMin",
    "HL_DccType_Act360",
    "HL_DccType_Act365",
    "HL_DccType_InvalidMax"
);

namespace HL_DateTime
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Dcc
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131223
\brief The HL dcc
*/
class HL_Dcc : public virtual HLSER::HL_Serializable
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

        HL_SER(hl_DccType_);
    }
    //@} Serialization -----------------------------------

    friend std::ostream& operator<<(std::ostream& os, const HL_Dcc& hl_Dcc);


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_Dcc();


    virtual ~HL_Dcc();
    //@}


    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(HL_DccType, hl_DccType);

    virtual HLR yf(const date & dStart, const date & dEnd) const=0;
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

    HLL nbDaysInBetween(const date & dStart, const date & dEnd) const;

    //@}


    /**
    Implementations of base class methods
    */
    //@{

    //@}


protected:


    /**
    Class variables
    */
    //@{
    /**
    The period will be nbUnits_x hl_DccType()
    */
    HL_DccType hl_DccType_;
    //@}



}
; // end class HL_Dcc

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Dcc:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


std::ostream& operator<<(std::ostream& os, const HL_Dcc& hl_Dcc);

//------------------------------------------------------------------------------------------------------

#define HL_DccPtr BSP<HLDT::HL_Dcc>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Dcc_Act360
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131223
\brief HL Act360 dcc
*/
class HL_Dcc_Act360 : public virtual HL_Dcc
{

    /**
    -----------------------------------------------------
    Serialization
    */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS;

    template<class Archive>
    void serialize(Archive &ar, const HLS version)
    {}
    //@} Serialization -----------------------------------



public:


    /**
    Constructors & destructors
    */
    //@{

    HL_Dcc_Act360();


    virtual ~HL_Dcc_Act360();
    //@}


    /**
    Public class interface
    */
    //@{

    HLR yf(const date & dStart, const date & dEnd) const;
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

    //@}


protected:


    /**
    Class variables
    */
    //@{
    /**
    The period will be nbUnits_x hl_DccType()
    */

    //@}



}
; // end class HL_Dcc_Act360

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Dcc_Act365
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131223
\brief HL Act365 dcc
*/
class HL_Dcc_Act365 : public virtual HL_Dcc
{

    /**
    -----------------------------------------------------
    Serialization
    */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS;

    template<class Archive>
    void serialize(Archive &ar, const HLS version)
    {}
    //@} Serialization -----------------------------------



public:


    /**
    Constructors & destructors
    */
    //@{

    HL_Dcc_Act365();


    virtual ~HL_Dcc_Act365();
    //@}


    /**
    Public class interface
    */
    //@{

    HLR yf(const date & dStart, const date & dEnd) const;
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

    //@}


protected:


    /**
    Class variables
    */
    //@{
    /**
    The period will be nbUnits_x hl_DccType()
    */

    //@}



}
; // end class HL_Dcc_Act365




} // end namespace HL_DateTime

using HL_DateTime::HL_Dcc;


} //end namespace HorizonLib


#endif // _hl_dcc_h_
