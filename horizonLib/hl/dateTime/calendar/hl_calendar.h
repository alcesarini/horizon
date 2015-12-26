/**
FILE NAME= _hl_calendar.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131216
*/
#ifndef _hl_calendar_h_
#define _hl_calendar_h_

#include <hl/object/hl_object.h>
#include <hl/dateTime/hl_period.h>

namespace HorizonLib
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_BusinessDayConvention
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
To adjust non-business dates
*/
enum HL_BusinessDayConvention
{
    HL_BusinessDayConvention_InvalidMin=0,
    /**
    ISDA
    Choose the first business day after
    the given holiday
    */
    HL_BusinessDayConvention_Following,
    /**
    ISDA
    Choose the first business day after
    the given holiday unless it belongs
    to a different month, in which case
    choose the first business day before
    the holiday.
    */
    HL_BusinessDayConvention_ModifiedFollowing,
    /**
    ISDA
    Choose the first business day before the given holiday.
    */
    HL_BusinessDayConvention_Preceding,
    /**
    NON ISDA
    Choose the first business day before
    the given holiday unless it belongs
    to a different month, in which case
    choose the first business day after
    the holiday.
    */
    HL_BusinessDayConvention_ModifiedPreceding,
    /**
    Do not adjust.
    */
    HL_BusinessDayConvention_Unadjusted,
    HL_BusinessDayConvention_InvalidMax
}; // end enum HL_BusinessDayConvention

//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
        HL_BusinessDayConvention,
        "HL_BusinessDayConvention_InvalidMin",
        "HL_BusinessDayConvention_Following",
        "HL_BusinessDayConvention_ModifiedFollowing",
        "HL_BusinessDayConvention_Preceding",
        "HL_BusinessDayConvention_ModifiedPreceding",
        "HL_BusinessDayConvention_Unadjusted",
        "HL_BusinessDayConvention_InvalidMax"
        );

namespace HL_DateTime
{
namespace HL_Calendars
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CalendarCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131210
\brief The ins code
*/

class HL_CalendarCode : public virtual HLOBJ::HL_ObjCode
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

    HL_CalendarCode();

    virtual ~HL_CalendarCode();
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
; // end class HL_CalendarCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CalendarCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_CalendarCodePtr BSP<HLINS::HL_CalendarCode>





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Calendar
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131216
\brief Basic financial instrument.
*/
class HL_Calendar : public virtual HLOBJ::HL_Obj
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

        HL_SERIALIZE_BASE_CLASS(HLOBJ::HL_Obj);


    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_Calendar();

    virtual ~HL_Calendar();
    //@}


    /**
    Public class interface
    */
    //@{

    bool isHoliday(const date & d) const;

    bool isBusiness(const date & d) const
    {
        return !isHoliday(d);
    }

    bool isLastBusinessDayOfMonth(const date & d) const;



    date advance(const date & d,
                 const HL_Period& hl_Period,
                 HL_BusinessDayConvention hl_BusinessDayConvention,
                 bool send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth=false) const;

    date adjust(const date & d, HL_BusinessDayConvention hl_bdc) const;

    date lastBusinessDayOfMonth(const date & d) const;
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
    virtual bool isHolidayImpl(const date & d) const=0;

    bool isValidDate(const date & d) const;
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
; // end class HL_Calendar


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CalendarCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_CalendarPtr BSP<HLCAL::HL_Calendar>






//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FakeCalendar
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131216
\brief Basic financial instrument.
*/
class HL_FakeCalendar : public virtual HL_Calendar
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

        HL_SERIALIZE_BASE_CLASS(HL_Calendar);


    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_FakeCalendar();

    virtual ~HL_FakeCalendar();
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

    bool isHolidayImpl(const date & d) const;

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
; // end class HL_FakeCalendar


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FakeCalendarCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_FakeCalendarPtr BSP<HLCAL::HL_FakeCalendar>



} // end namespace HL_Calendars
} // end namespace HL_DateTime
} //end namespace HorizonLib


#endif // _hl_calendar_h_
