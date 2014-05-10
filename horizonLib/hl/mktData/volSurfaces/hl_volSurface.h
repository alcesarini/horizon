/**
FILE NAME= hl_volSurface.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131227
*/
#ifndef _hl_volSurface_h_
#define _hl_volSurface_h_

#include <hl/mktData/hl_mktData.h>


namespace HorizonLib
{
namespace HL_MarketData
{
namespace HL_VolSurfaces
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VolSurfaceCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131213
\brief The vol surface code
*/

class HL_VolSurfaceCode : public virtual HL_MktDataCode
{
public:


    /**
    Constructors & destructors
    */
    //@{

    HL_VolSurfaceCode();

    virtual ~HL_VolSurfaceCode();
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
; // end class HL_VolSurfaceCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VolSurfaceCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_VolSurfaceCodePtr BSP<HLVOL::HL_VolSurfaceCode>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VolSurface
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131213
\brief Base class for all vol surfaces.
*/
class HL_VolSurface : public virtual HL_MktData
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

    HL_VolSurface();

    virtual ~HL_VolSurface();
    //@}


    /**
    Public class interface
    */
    //@{




    /**
    Implied vol in time interval [get_refTime(), t] for a vanilla option having strike equal to k.
    */
    HLR vol(const ptime &t, HLR k) const;

    HLR vol(const date &d, HLR k) const
    {
        return vol(ptime(d), k);
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

    //@}

}
; // end class HL_VolSurface


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VolSurface: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_VolSurfacePtr BSP<HLVOL::HL_VolSurface>

//------------------------------------------------------------------------------------------------------

HL_VolSurfacePtr get_VolSurfacePtr(const HL_MktDataCollectorPtr & mktDataCollectorPtr, const HL_ObjCodePtr & objCodePtr);




} // end namespace HL_VolSurfaces
} // end namespace HL_MarketData
} //end namespace HorizonLib


#endif // _hl_volSurface_h_
