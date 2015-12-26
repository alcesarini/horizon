/**
FILE NAME= hl_scheduleAnagraphics.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140615
*/

#include <hl/instruments/anagraphics/hl_scheduleAnagraphics.h>



HL_SERIALIZATION_CLASS_EXPORT_GUID(HLAN::HL_ScheduleAnagraphics);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLAN::HL_AccrualPeriod);


namespace HorizonLib
{
namespace HL_Instruments
{
namespace HL_Anagraphics
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_ScheduleAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_ScheduleAnagraphics::HL_ScheduleAnagraphics()
{

    classDefaultInit();



} // end HL_ScheduleAnagraphics

//------------------------------------------------------------------------------------------------------

HL_ScheduleAnagraphics::~HL_ScheduleAnagraphics()
{} // end ~HL_ScheduleAnagraphics


//------------------------------------------------------------------------------------------------------

void HL_ScheduleAnagraphics::classDefaultInit()
{

    brokenRuleType_=HL_BrokenRuleType_InvalidMin;
    accrualDatesBusinessDayConvention_=HL_BusinessDayConvention_InvalidMin;
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_ScheduleAnagraphics::checkAnagraphics() const
{

    HL_Anagraphics::checkAnagraphics();

    HL_SRE(lastAccrualEndDate_>firstAccrualStartDate_, "firstAccrualStartDate_=" << firstAccrualStartDate_
           << ", lastAccrualEndDate_=" << lastAccrualEndDate_);

    HL_SR(!couponFrequency_.empty());


    HL_ENUM_CHECK(HL_BrokenRuleType, brokenRuleType_);


    HL_ENUM_CHECK(HL_BusinessDayConvention, accrualDatesBusinessDayConvention_);


} // end checkAnagraphics


//------------------------------------------------------------------------------------------------------


void HL_ScheduleAnagraphics::descriptionImpl(std::ostream & os) const
{

    HL_Anagraphics::descriptionImpl(os);
    hl_fillDescriptionStream(firstAccrualStartDate_);
    hl_fillDescriptionStream(lastAccrualEndDate_);
    hl_fillDescriptionStream(couponFrequency_);
    HL_DESCRIBE_ENUM(os, brokenRuleType_);
    HL_DESCRIBE_ENUM(os, accrualDatesBusinessDayConvention_);
    hl_fillDescriptionStream(calendar_);





} // end descriptionImpl
//------------------------------------------------------------------------------------------------------


void HL_ScheduleAnagraphics::set_scheduleLength(const HL_Period & scheduleLength,
                                                bool send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth)
{

    HL_PNN(calendar_);

    HL_SR(firstAccrualStartDate_!=date());

    HL_SRE(lastAccrualEndDate_==date(), "either set lastAccrualEndDate_ directly with "
           << "method set_lastAccrualEndDate or with method set_scheduleLength");


    lastAccrualEndDate_ = calendar_->advance(firstAccrualStartDate_,
                                             scheduleLength,
                                             accrualDatesBusinessDayConvention_,
                                             send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth);



} // end set_scheduleLength




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_ScheduleAnagraphics: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// get_HL_ScheduleAnagraphicsFromFirstAccrualStartDate
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20150824
\brief Interface to build a HL_ScheduleAnagraphicsPtr
*/
HL_ScheduleAnagraphicsPtr get_HL_ScheduleAnagraphicsFromFirstAccrualStartDate(
        const date & firstAccrualStartDate,
        const HL_Period & scheduleLength,
        bool send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth,
        const HL_Period & couponFrequency,
        HL_BrokenRuleType brokenRuleType,
        HL_BusinessDayConvention accrualDatesBusinessDayConvention,
        const HL_CalendarPtr& calendar
        )
{

    HL_ScheduleAnagraphicsPtr scheduleAnagraphics(new HL_ScheduleAnagraphics);

    scheduleAnagraphics->set_firstAccrualStartDate(firstAccrualStartDate);
    scheduleAnagraphics->set_couponFrequency(couponFrequency);
    scheduleAnagraphics->set_brokenRuleType(brokenRuleType);
    scheduleAnagraphics->set_accrualDatesBusinessDayConvention(accrualDatesBusinessDayConvention);
    scheduleAnagraphics->set_calendar(calendar);

    scheduleAnagraphics->set_scheduleLength(scheduleLength,
                                           send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth);



    return scheduleAnagraphics;

} // end get_HL_ScheduleAnagraphicsFromFirstAccrualStartDate


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// get_HL_ScheduleAnagraphicsFromSpotDate
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

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
        )
{

    HL_Period nbStartDateLagDaysPeriod(nbStartDateLagDays, HL_PeriodUnit_Days);

    date firstAccrualStartDate = calendar->advance(spotDate/* d*/,
                                         nbStartDateLagDaysPeriod,
                                         startDateLagBusinessDayConvention,
                                         false/* send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth*/);


    return get_HL_ScheduleAnagraphicsFromFirstAccrualStartDate(
                firstAccrualStartDate,
                scheduleLength,
                send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth,
                couponFrequency,
                brokenRuleType,
                accrualDatesBusinessDayConvention,
                calendar
                );


} // end get_HL_ScheduleAnagraphicsFromSpotDate


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_AccrualPeriod
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_AccrualPeriod::HL_AccrualPeriod()
{

    classDefaultInit();



} // end HL_AccrualPeriod

//------------------------------------------------------------------------------------------------------

HL_AccrualPeriod::~HL_AccrualPeriod()
{} // end ~HL_AccrualPeriod


//------------------------------------------------------------------------------------------------------

void HL_AccrualPeriod::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_AccrualPeriod::checkAccrualPeriod() const
{

    HL_SRE(accrualStartDate_<accrualEndDate_, "accrualStartDate_=" << accrualStartDate_
           << ", accrualEndDate_=" << accrualEndDate_);



} // end checkAccrualPeriod



//------------------------------------------------------------------------------------------------------


void HL_AccrualPeriod::descriptionImpl(std::ostream & os) const
{

    HL_CLASS_DESCRIPTION_HEAD(HL_AccrualPeriod);

    hl_fillDescriptionStream(accrualStartDate_);
    hl_fillDescriptionStream(accrualEndDate_);



} // end descriptionImpl

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_AccrualPeriod: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------










//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Schedule
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_Schedule::HL_Schedule()
{

    classDefaultInit();



} // end HL_Schedule

//------------------------------------------------------------------------------------------------------

HL_Schedule::~HL_Schedule()
{} // end ~HL_Schedule


//------------------------------------------------------------------------------------------------------

void HL_Schedule::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_Schedule::checkSchedule() const
{

    HLS i=0;

    BOOST_FOREACH(const HL_AccrualPeriodPtr & accrualPeriod, accrualPeriods_)
    {
        accrualPeriod->checkAccrualPeriod();

        HL_SRE(accrualPeriod->get_accrualStartDate()>=accrualPeriods_[i-1]->get_accrualEndDate(),
                "accrualPeriod->get_accrualStartDate()=" << accrualPeriod->get_accrualStartDate()
                                                        << "accrualPeriods_[i-1]->get_accrualEndDate()=" << accrualPeriods_[i-1]->get_accrualEndDate()
                                                        << ", i=" << i);


        ++i;

    } // end for accrualPeriod




} // end checkSchedule




//------------------------------------------------------------------------------------------------------


void HL_Schedule::descriptionImpl(std::ostream & os) const
{

    HL_CLASS_DESCRIPTION_HEAD(HL_Schedule);

    hl_fillDescriptionStream(accrualPeriods_);



} // end descriptionImpl

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Schedule: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



void buildScheduleForward(const HL_ScheduleAnagraphicsPtr & scheduleAnagraphicsPtr,
                          std::vector<HL_AccrualPeriodPtr> & accrualPeriods)
{


    const date & dStart= scheduleAnagraphicsPtr->get_firstAccrualStartDate();
    const date & dEnd = scheduleAnagraphicsPtr->get_lastAccrualEndDate();
    const HL_Period & step = scheduleAnagraphicsPtr->get_couponFrequency();
    const HL_BusinessDayConvention & accrualDatesBusinessDayConvention =
            scheduleAnagraphicsPtr->get_accrualDatesBusinessDayConvention();

    const HL_CalendarPtr& calendar = scheduleAnagraphicsPtr->get_calendar();

    date d = dStart;


    HLI i=1;
    while(d<dEnd)
    {

        HL_AccrualPeriodPtr accrualPeriod(new HL_AccrualPeriod);

        accrualPeriod->set_accrualStartDate(d);

        d = dStart + i*step;

        d = calendar->adjust(d, accrualDatesBusinessDayConvention);

        d = std::min(d, dEnd);

        accrualPeriod->set_accrualEndDate(d);

        accrualPeriods.push_back(accrualPeriod);

        i++;

    } // end while d




} // end buildScheduleForward

//------------------------------------------------------------------------------------------------------



void buildScheduleBackward(const HL_ScheduleAnagraphicsPtr & scheduleAnagraphicsPtr,
                           std::vector<HL_AccrualPeriodPtr> & accrualPeriods)
{


    const date & dStart= scheduleAnagraphicsPtr->get_lastAccrualEndDate();
    const date & dEnd = scheduleAnagraphicsPtr->get_firstAccrualStartDate();
    HL_Period backwardStep = -scheduleAnagraphicsPtr->get_couponFrequency();
    const HL_BusinessDayConvention & accrualDatesBusinessDayConvention =
            scheduleAnagraphicsPtr->get_accrualDatesBusinessDayConvention();

    const HL_CalendarPtr& calendar = scheduleAnagraphicsPtr->get_calendar();

    date d = dStart;

    std::vector<HL_AccrualPeriodPtr> accrualPeriodsBackward;

    HLI i=1;
    while(d>dEnd)
    {

        HL_AccrualPeriodPtr accrualPeriod(new HL_AccrualPeriod);

        accrualPeriod->set_accrualEndDate(d);

        d = dStart + i*backwardStep;

        d = calendar->adjust(d, accrualDatesBusinessDayConvention);

        d = std::max(d, dEnd);

        accrualPeriod->set_accrualStartDate(d);

        accrualPeriodsBackward.push_back(accrualPeriod);

        i++;

    } // end while d


    accrualPeriods.resize(accrualPeriodsBackward.size());


    std::copy(accrualPeriodsBackward.rbegin(), accrualPeriodsBackward.rend(), accrualPeriods.begin());

} // end buildScheduleBackward

//------------------------------------------------------------------------------------------------------


HL_SchedulePtr buildSchedule(const HL_ScheduleAnagraphicsPtr & scheduleAnagraphicsPtr)
{
    HL_PNN(scheduleAnagraphicsPtr);


    scheduleAnagraphicsPtr->checkAnagraphics();

    HL_SchedulePtr schedulePtr(new HL_Schedule);

    std::vector<HL_AccrualPeriodPtr> & accrualPeriods = schedulePtr->accrualPeriods_;

    switch(scheduleAnagraphicsPtr->get_brokenRuleType())
    {

    case HL_BrokenRuleType_BrokenAtStart:
        buildScheduleForward(scheduleAnagraphicsPtr, accrualPeriods);
        break;
    case HL_BrokenRuleType_BrokenAtEnd:
        buildScheduleBackward(scheduleAnagraphicsPtr, accrualPeriods);
        break;
    default:
        HL_FAIL("not managed scheduleAnagraphicsPtr->get_brokenRuleType()=" << scheduleAnagraphicsPtr->get_brokenRuleType());

    } // end switch scheduleAnagraphicsPtr->get_brokenRuleType()

    return schedulePtr;

} // end buildSchedule


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
        )
{

    HL_CalendarPtr fakeCalendar(new HLCAL::HL_FakeCalendar);

    HL_ScheduleAnagraphicsPtr scheduleAnagraphicsPtr=get_HL_ScheduleAnagraphicsFromSpotDate(
                spotDate,
                2 /*nbStartDateLagDays*/,
                HL_BusinessDayConvention_Following /*startDateLagBusinessDayConvention*/,
                 scheduleLength,
                false /*send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth*/,
                couponFrequency,
                HL_BrokenRuleType_BrokenAtStart /*brokenRuleType*/,
                HL_BusinessDayConvention_ModifiedFollowing /*accrualDatesBusinessDayConvention*/,
                fakeCalendar
                );


    return scheduleAnagraphicsPtr;

} // end HL_TEST_get_HL_ScheduleAnagraphicsFromSpotDate




} // end namespace HL_Anagraphics
} // end namespace HL_Instruments
} //end namespace HorizonLib
