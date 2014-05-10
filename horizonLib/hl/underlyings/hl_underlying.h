/**
FILE NAME= hl_underlying.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131214
*/
#ifndef _hl_underlying_h_
#define _hl_underlying_h_


#include <hl/mktData/hl_mktData.h>
#include <hl/dateTime/calendar/hl_calendar.h>
#include <hl/object/hl_history.h>


namespace HorizonLib
{
namespace HL_MarketData
{
namespace HL_Underlyings
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_MeasureType
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
\brief The HL library period units.
*/
enum HL_MeasureType
{
    HL_MeasureType_InvalidMin=0,
    HL_MeasureType_FwdMeasure,
    HL_MeasureType_SwapMeasure,
    HL_MeasureType_InvalidMax
}; // end enum HL_MeasureType

//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
    HL_MeasureType,
    "HL_MeasureType_InvalidMin",
    "HL_MeasureType_FwdMeasure",
    "HL_MeasureType_SwapMeasure",
    "HL_MeasureType_InvalidMax"
);


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Measure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131226
\brief Base class to represent pricing measures.
*/

class HL_Measure : public virtual HLSER::HL_Serializable, public virtual Descriptable
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

    HL_Measure();

    virtual ~HL_Measure();
    //@}


    /**
    Public class interface
    */
    //@{
    virtual HL_MeasureType measureType() const=0;
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
; // end class HL_Measure


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Measure: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_MeasurePtr BSP<HLUND::HL_Measure>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FwdMeasure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131226
\brief Class used to specify the fwd measure to compute expectations.
*/

class HL_FwdMeasure : public virtual HL_Measure
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

        HL_SERIALIZE_BASE_CLASS(HL_Measure);

        HL_SER(payDate_);
        HL_SER(hl_CcyCode_);

    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_FwdMeasure();

    virtual ~HL_FwdMeasure();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(date/*ClassVariableType*/, payDate/*classVariableName_no_underscore*/);

    HL_CLASS_VAR_ACCESS_METHODS(HL_CcyCodePtr/*ClassVariableType*/, hl_CcyCode/*classVariableName_no_underscore*/);

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


    HL_MeasureType measureType() const
    {

        return HL_MeasureType_FwdMeasure;
    }

    //@}


protected:


    /**
    Class variables
    */
    //@{

    /**
    The numeraire associated to HL_FwdMeasure is the zero-coupon bond
    deliverying 1 unit of hl_CcyCode_-currency at date payDate_.
    */
    //@{
    date payDate_;

    HL_CcyCodePtr hl_CcyCode_;
    //@}
    //@}

}
; // end class HL_FwdMeasure

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FwdMeasure: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_FwdMeasurePtr BSP<HLUND::HL_FwdMeasure>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131210
\brief The ins code
*/

class HL_UnderlyingCode : public virtual HLMD::HL_MktDataCode
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

        HL_SERIALIZE_BASE_CLASS(HLMD::HL_MktDataCode);

    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_UnderlyingCode();

    virtual ~HL_UnderlyingCode();
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
; // end class HL_UnderlyingCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_UnderlyingCodePtr BSP<HLINS::HL_UnderlyingCode>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Underlying
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131216
\brief Basic financial instrument.
*/
class HL_Underlying : public virtual HLMD::HL_MktData
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

        HL_SERIALIZE_BASE_CLASS(HLMD::HL_MktData);
        HL_SER(calendar_);
        HL_SER(hl_DateRealHistoryPtr_);
        HL_SER(historyTag_);

    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_Underlying();

    virtual ~HL_Underlying();
    //@}


    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(HL_CalendarPtr/*ClassVariableType*/, calendar/*classVariableName_no_underscore*/);

    HL_CLASS_VAR_ACCESS_METHODS(HL_DateRealHistoryPtr/*ClassVariableType*/, hl_DateRealHistoryPtr/*classVariableName_no_underscore*/);

    HL_CLASS_VAR_ACCESS_METHODS(HLSTRING/*ClassVariableType*/, historyTag/*classVariableName_no_underscore*/);


    HLR expectation(const date & fixingDate, const HL_MeasurePtr & hl_MeasurePtr=HL_MeasurePtr()) const;

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

    virtual HLR forecastedExpectation(const date & fixingDate, const HL_MeasurePtr & hl_MeasurePtr) const=0;
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
    HL_CalendarPtr calendar_;

    HL_DateRealHistoryPtr hl_DateRealHistoryPtr_;

    /**
    The tag of the history that will be used for past fixings
    */
    HLSTRING historyTag_;
    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_Underlying


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_UnderlyingPtr BSP<HLINS::HL_Underlying>


} // end namespace HL_Underlyings
} // end namespace HL_MarketData
} //end namespace HorizonLib


#endif // _hl_underlying_h_
