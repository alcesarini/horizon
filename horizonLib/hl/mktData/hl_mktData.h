/**
FILE NAME= hl_mktData.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131214
*/
#ifndef _hl_mktData_h_
#define _hl_mktData_h_

#include <hl/object/hl_object.h>




namespace HorizonLib
{
namespace HL_MarketData
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktDataCollector: fwd declaration
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


class HL_MktDataCollector;

//------------------------------------------------------------------------------------------------------

#define HL_MktDataCollectorPtr BSP<HLMD::HL_MktDataCollector>

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktDataCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131213
\brief The term structure code
*/

class HL_MktDataCode : public virtual HLOBJ::HL_FinObjCode
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

    HL_MktDataCode();

    virtual ~HL_MktDataCode();
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
; // end class HL_MktDataCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktDataCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_MktDataCodePtr BSP<HLTS::HL_MktDataCode>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktData
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131213
\brief Base class for all term structures.
*/
class HL_MktData : public virtual HLOBJ::HL_FinObj
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

    HL_MktData();

    virtual ~HL_MktData();
    //@}


    /**
    Public class interface
    */
    //@{


    void set_mktDataCollectorWeakPtr(const HL_MktDataCollectorPtr & mktDataCollectorPtr);

    HL_MktDataCollectorPtr get_mktDataCollector() const;


    const ptime &get_refTime() const;

    date get_refDate() const;


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
    /**
    The HL_MktDataCollector HL_MktData is hosted in.
    We need to use a weak_ptr to avoid dead-locking.
    */
    BWP<HL_MktDataCollector> mktDataCollectorWeakPtr_;
    //@}

}
; // end class HL_MktData


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktData: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_MktDataPtr BSP<HLMD::HL_MktData>


} // end namespace HL_MarketData
} //end namespace HorizonLib


#endif // _hl_mktData_h_
