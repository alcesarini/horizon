/**
FILE NAME= hl_scheduleAnagraphics.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140615
*/
#ifndef _hl_scheduleAnagraphics_h_
#define _hl_scheduleAnagraphics_h_

#include <hl/instruments/anagraphics/hl_anagraphics.h>

namespace HorizonLib
{
namespace HL_Instruments
{
namespace HL_Anagraphics
{








//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_BrokenRuleType
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
\brief Establish how to compute a basket.
*/
enum HL_BrokenRuleType
{
    HL_BrokenRuleType_InvalidMin=0,
    /**
      The broken coupon (if any) is placed at start of the span of the coupons
    */
    HL_BrokenRuleType_BrokenAtStart,
    /**
     The broken coupon (if any) is placed at end of the span of the coupons
    */
    HL_BrokenRuleType_BrokenAtEnd,
    HL_BrokenRuleType_InvalidMax
}; // end enum HL_BrokenRuleType

//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
        HL_BrokenRuleType,
        "HL_BrokenRuleType_InvalidMin",
        "HL_BrokenRuleType_BrokenAtStart",
        "HL_BrokenRuleType_BrokenAtEnd",
        "HL_BrokenRuleType_InvalidMax"
        );


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_ScheduleAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140615
\brief To build a schedule of coupons.
*/
class HL_ScheduleAnagraphics : public virtual HL_Anagraphics
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

        HL_SERIALIZE_BASE_CLASS(HL_Anagraphics);

        HL_SER(firstAccrualStartDate_);
        HL_SER(lastAccrualEndDate_);
        HL_SER(couponFrequency_);
        HL_SER(brokenRuleType_);
        HL_SER(accrualDatesBusinessDayConvention_);
        HL_SER(calendar_);


    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_ScheduleAnagraphics();

    virtual ~HL_ScheduleAnagraphics();
    //@}


    /**
    Public class interface
    */
    //@{




    HL_CLASS_VAR_ACCESS_METHODS(date, firstAccrualStartDate);
    HL_CLASS_VAR_ACCESS_METHODS(date, lastAccrualEndDate);
    HL_CLASS_VAR_ACCESS_METHODS(HL_Period, couponFrequency);
    HL_CLASS_VAR_ACCESS_METHODS(HL_BrokenRuleType, brokenRuleType);
    HL_CLASS_VAR_ACCESS_METHODS(HL_BusinessDayConvention, accrualDatesBusinessDayConvention);
    HL_CLASS_VAR_ACCESS_METHODS(HL_CalendarPtr, calendar);

    /**
    An alternative way to set lastAccrualEndDate_ as a shift from firstAccrualStartDate_
    */
    void set_scheduleLength(const HL_Period & scheduleLength,
                            bool send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth);



    HL_AnagraphicsType anagraphicsType() const
    {
        return HL_AnagraphicsType_HL_ScheduleAnagraphics;
    }

    void checkAnagraphics() const;

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


    /**
    The span of coupons represented by this class will cover
    the period specified by 2 dates: lastAccrualEndDate_>=firstAccrualStartDate_.
    These dates are meant to be already adjusted if needed.

    firstAccrualStartDate_ is always fixed, lastAccrualEndDate_can be specified also
    as a relative shift from firstAccrualStartDate_ (check method set_scheduleLength).
    */
    date firstAccrualStartDate_, lastAccrualEndDate_;

    /**
    The span will cover [firstAccrualStartDate_, lastAccrualEndDate_] with period
    of this length.
    */
    HL_Period couponFrequency_;


    HL_BrokenRuleType brokenRuleType_;


    HL_BusinessDayConvention accrualDatesBusinessDayConvention_;

    HL_CalendarPtr calendar_;


    //@}

}
; // end class HL_ScheduleAnagraphics


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_ScheduleAnagraphics: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_ScheduleAnagraphicsPtr BSP<HLAN::HL_ScheduleAnagraphics>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// get_HL_ScheduleAnagraphicsFromFirstAccrualStartDate
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20150824
\brief Interface to build a HL_ScheduleAnagraphicsPtr (see cpp)
*/
HL_ScheduleAnagraphicsPtr get_HL_ScheduleAnagraphicsFromFirstAccrualStartDate(
        const date & firstAccrualStartDate,
        const HL_Period & scheduleLength,
        bool send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth,
        const HL_Period & couponFrequency,
        HL_BrokenRuleType brokenRuleType,
        HL_BusinessDayConvention accrualDatesBusinessDayConvention,
        const HL_CalendarPtr& calendar
        );



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// get_HL_ScheduleAnagraphicsFromSpotDate
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20150824
\brief Interface to build a HL_ScheduleAnagraphicsPtr (see cpp)
*/
HL_ScheduleAnagraphicsPtr get_HL_ScheduleAnagraphicsFromSpotDate(
        const date & spotDate,
        HLS nbStartDateLagDays,
        HL_BusinessDayConvention startDateLagBusinessDayConvention,
        const HL_Period & scheduleLength,
        bool send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth,
        const HL_Period & couponFrequency,
        HL_BrokenRuleType brokenRuleType,
        HL_BusinessDayConvention accrualDatesBusinessDayConvention,
        const HL_CalendarPtr& calendar
        );



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_AccrualPeriod
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140615
\brief An accrual period.
*/
class HL_AccrualPeriod : public virtual HLSER::HL_Serializable, public virtual Descriptable
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
        HL_SER(accrualStartDate_);
        HL_SER(accrualEndDate_);


    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_AccrualPeriod();

    virtual ~HL_AccrualPeriod();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(date, accrualStartDate);
    HL_CLASS_VAR_ACCESS_METHODS(date, accrualEndDate);


    void checkAccrualPeriod() const;


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


    date accrualStartDate_, accrualEndDate_;



    //@}

}
; // end class HL_AccrualPeriod


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_AccrualPeriod: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_AccrualPeriodPtr BSP<HLAN::HL_AccrualPeriod>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Schedule
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_SchedulePtr BSP<HLAN::HL_Schedule>

//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140615
\brief A schedule of coupons (only accrualStart and accrualEnd dates, not pay dates).
*/
class HL_Schedule : public virtual HLSER::HL_Serializable, public virtual Descriptable
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

        HL_SER(accrualPeriods_);


    }
    //@} Serialization -----------------------------------

    friend HL_SchedulePtr buildSchedule(const HL_ScheduleAnagraphicsPtr & scheduleAnagraphicsPtr);
public:
    /**
    Constructors & destructors
    */
    //@{

    HL_Schedule();

    virtual ~HL_Schedule();
    //@}


    /**
    Public class interface
    */
    //@{




    HL_CLASS_VAR_ACCESS_METHODS(std::vector<HL_AccrualPeriodPtr>, accrualPeriods);




    void checkSchedule() const;

    HLS nbCoupons() const
    {

        return accrualPeriods_.size();
    }


    const HL_AccrualPeriodPtr & accrualPeriod(HLS couponIdx) const
    {

        HL_SR(couponIdx<accrualPeriods_.size());
        return accrualPeriods_[couponIdx];
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



    std::vector<HL_AccrualPeriodPtr> accrualPeriods_;


    //@}

}
; // end class HL_Schedule


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Schedule: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




/**
 * \author A. Cesarini
 * \date 20140615
 * \brief Function to build a schedule from a scheduleAnagraphicsPtr
*/
HL_SchedulePtr buildSchedule(const HL_ScheduleAnagraphicsPtr & scheduleAnagraphicsPtr);


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_HL_ScheduleAnagraphicsFromSpotDate
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20150824
\brief Test utility to build some HL_ScheduleAnagraphicsPtr
*/
HL_ScheduleAnagraphicsPtr HL_TEST_get_HL_ScheduleAnagraphicsFromSpotDate(
        const date & spotDate,
        const HL_Period & scheduleLength,
        const HL_Period & couponFrequency
        );


} // end namespace HL_Anagraphics
} // end namespace HL_Instruments
} //end namespace HorizonLib


#endif // _hl_scheduleAnagraphics_h_
